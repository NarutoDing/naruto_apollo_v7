import * as THREE from 'three';
import STORE from 'store';
import { MAP_WS } from 'store/websocket';
import _ from 'lodash';

import {
  drawSegmentsFromPoints,
  drawDashedLineFromPoints,
  drawShapeFromPoints,
  changeMaterial,
} from 'utils/draw';
import {
  pointOnVectorRight,
  directionVectorCrossProduct,
  getIntersectionPoint,
  directionSameWithVector,
  getBehindPointIndexDistanceApart,
  getInFrontOfPointIndexDistanceApart,
  getPointDistance,
  determineTheRelationBetweenLanes,
  getLaneArrayFirstAndLastPoint,
  determinLaneDirection,
  isLaneCompleteInRectangle,
  getLaneFirstAndLastPoint,
  getLaneLastPoint,
  IsPointInRectangle,
  getLaneFirstPoint,
} from 'utils/misc';

import Text3D, { TEXT_ALIGN } from 'renderer/text3d';
import TrafficSigns from 'renderer/traffic_controls/traffic_signs';
import TrafficSignals from 'renderer/traffic_controls/traffic_signals';

import stopSignMaterial from 'assets/models/stop_sign.mtl';
import stopSignObject from 'assets/models/stop_sign.obj';
import yieldSignMaterial from 'assets/models/yield_sign.mtl';
import yieldSignObject from 'assets/models/yield_sign.obj';

const STOP_SIGN_SCALE = 0.01;
const YIELD_SIGN_SCALE = 1.5;

const colorMapping = {
  YELLOW: 0XDAA520,
  WHITE: 0xCCCCCC,
  CORAL: 0xFF7F50,
  RED: 0xFF6666,
  GREEN: 0x006400,
  BLUE: 0x30A5FF,
  PURE_WHITE: 0xFFFFFF,
  DEFAULT: 0xC0C0C0,
};

// parallel=1 0-1 2-3
const order1 = [
  [0, 1, 2, 3],
  [1, 0, 3, 2],
  [2, 3, 0, 1],
  [3, 2, 1, 0],
];
// parallel=2 0-3 1-2
const order2 = [
  [0, 3, 2, 1],
  [1, 2, 3, 0],
  [2, 1, 0, 3],
  [3, 0, 1, 2],
];
export default class Map {
  constructor() {
    this.textRender = new Text3D();
    this.hash = -1;
    this.data = {};
    this.initialized = false;
    this.elementKindsDrawn = '';

    this.trafficSignals = new TrafficSignals();
    this.stopSigns = new TrafficSigns(
      stopSignMaterial, stopSignObject, STOP_SIGN_SCALE,
    );
    this.yieldSigns = new TrafficSigns(
      yieldSignMaterial, yieldSignObject, YIELD_SIGN_SCALE,
    );

    this.zOffsetFactor = 1;
  }

  // The result will be the all the elements in current but not in data.
  diffMapElements(elementIds, data) {
    const result = {};
    let empty = true;

    for (const kind in elementIds) {
      if (!this.shouldDrawObjectOfThisElementKind(kind)) {
        continue;
      }

      result[kind] = [];
      const newIds = elementIds[kind];
      const oldData = data[kind];
      for (let i = 0; i < newIds.length; ++i) {
        const found = oldData ? oldData.find((old) => old.id.id === newIds[i]) : false;

        if (!found) {
          empty = false;
          result[kind].push(newIds[i]);
        }
      }
    }

    return empty ? {} : result;
  }

  addLaneMesh(laneType, points) {
    switch (laneType) {
      case 'DOTTED_YELLOW':
        return drawDashedLineFromPoints(
          points, colorMapping.YELLOW, 4, 3, 3, this.zOffsetFactor, 1, false,
        );
      case 'DOTTED_WHITE':
        return drawDashedLineFromPoints(
          points, colorMapping.WHITE, 2, 0.5, 0.25, this.zOffsetFactor, 0.4, false,
        );
      case 'SOLID_YELLOW':
        return drawSegmentsFromPoints(
          points, colorMapping.YELLOW, 3, this.zOffsetFactor, false,
        );
      case 'SOLID_WHITE':
        return drawSegmentsFromPoints(
          points, colorMapping.WHITE, 3, this.zOffsetFactor, false,
        );
      case 'DOUBLE_YELLOW':
        const left = drawSegmentsFromPoints(
          points, colorMapping.YELLOW, 2, this.zOffsetFactor, false,
        );
        const right = drawSegmentsFromPoints(
          points.map((point) => new THREE.Vector3(point.x + 0.3, point.y + 0.3, point.z)),
          colorMapping.YELLOW, 3, this.zOffsetFactor, false,
        );
        left.add(right);
        return left;
      case 'CURB':
        return drawSegmentsFromPoints(
          points, colorMapping.CORAL, 3, this.zOffsetFactor, false,
        );
      default:
        return drawSegmentsFromPoints(
          points, colorMapping.DEFAULT, 3, this.zOffsetFactor, false,
        );
    }
  }

  addLane(lane, coordinates, scene) {
    const drewObjects = [];

    const centralLine = lane.centralCurve.segment;
    centralLine.forEach((segment) => {
      const points = coordinates.applyOffsetToArray(segment.lineSegment.point);
      const centerLine = drawSegmentsFromPoints(
        points, colorMapping.GREEN, 1, this.zOffsetFactor, false);
      centerLine.name = `CentralLine-${lane.id.id}`;
      scene.add(centerLine);
      drewObjects.push(centerLine);
    });

    const rightLaneType = lane.rightBoundary.boundaryType[0].types[0];
    // TODO: this is a temp. fix for repeated boundary types.
    lane.rightBoundary.curve.segment.forEach((segment, index) => {
      const points = coordinates.applyOffsetToArray(segment.lineSegment.point);
      const boundary = this.addLaneMesh(rightLaneType, points);
      boundary.name = `RightBoundary-${lane.id.id}`;
      scene.add(boundary);
      drewObjects.push(boundary);
    });

    const leftLaneType = lane.leftBoundary.boundaryType[0].types[0];
    lane.leftBoundary.curve.segment.forEach((segment, index) => {
      const points = coordinates.applyOffsetToArray(segment.lineSegment.point);
      const boundary = this.addLaneMesh(leftLaneType, points);
      boundary.name = `LeftBoundary-${lane.id.id}`;
      scene.add(boundary);
      drewObjects.push(boundary);
    });

    return drewObjects;
  }

  addLaneId(lane, coordinates, scene) {
    const centralLine = lane.centralCurve.segment;
    let position = _.get(centralLine, '[0].startPosition');
    if (position) {
      position.z = 0.04;
      position = coordinates.applyOffset(position);
    }

    const rotation = { x: 0.0, y: 0.0, z: 0.0 };
    const points = _.get(centralLine, '[0].lineSegment.point', []);
    if (points.length >= 2) {
      const p1 = points[0];
      const p2 = points[1];
      rotation.z = Math.atan2(p2.y - p1.y, p2.x - p1.x);
    }

    const text = this.textRender.drawText(
      lane.id.id, scene, colorMapping.WHITE, TEXT_ALIGN.LEFT,
    );
    if (text) {
      const textPosition = position || _.get(points, '[0]');
      if (textPosition) {
        text.position.set(textPosition.x, textPosition.y, textPosition.z);
        text.rotation.set(rotation.x, rotation.y, rotation.z);
      }
      text.visible = false;
      scene.add(text);
    }

    return text;
  }

  addRoad(road, coordinates, scene) {
    const drewObjects = [];

    road.section.forEach((section) => {
      section.boundary.outerPolygon.edge.forEach((edge) => {
        edge.curve.segment.forEach((segment, index) => {
          const points = coordinates.applyOffsetToArray(segment.lineSegment.point);
          const boundary = this.addLaneMesh('CURB', points);
          boundary.name = `Road-${road.id.id}`;
          scene.add(boundary);
          drewObjects.push(boundary);
        });
      });
    });

    return drewObjects;
  }

  addBorder(borderPolygon, color, coordinates, scene) {
    const drewObjects = [];

    const border = coordinates.applyOffsetToArray(borderPolygon.polygon.point);
    border.push(border[0]);

    const mesh = drawSegmentsFromPoints(
      border, color, 2, this.zOffsetFactor, true, false, 1.0,
    );
    scene.add(mesh);
    drewObjects.push(mesh);

    return drewObjects;
  }

  addParkingSpaceId(parkingSpace, coordinates, scene) {
    const text = this.textRender.drawText(parkingSpace.id.id, scene, colorMapping.WHITE);
    const points = _.get(parkingSpace, 'polygon.point');
    if (points && points.length >= 3 && text) {
      const point1 = points[0];
      const point2 = points[1];
      const point3 = points[2];
      let textPosition = {
        x: (point1.x + point3.x) / 2,
        y: (point1.y + point3.y) / 2,
        z: 0.04,
      };
      textPosition = coordinates.applyOffset(textPosition);
      const textRotationZ = Math.atan2(point2.y - point1.y, point2.x - point1.x);

      text.position.set(textPosition.x, textPosition.y, textPosition.z);
      text.rotation.set(0, 0, textRotationZ);
      text.visible = true;
      scene.add(text);
    }
    return text;
  }

  addZone(zone, color, coordinates, scene) {
    const drewObjects = [];

    const border = coordinates.applyOffsetToArray(zone.polygon.point);
    border.push(border[0]);

    const zoneMaterial = new THREE.MeshBasicMaterial({
      color,
      transparent: true,
      opacity: 0.15,
    });

    const zoneShape = drawShapeFromPoints(
      border, zoneMaterial, false, this.zOffsetFactor * 3, false,
    );
    scene.add(zoneShape);
    drewObjects.push(zoneShape);

    const mesh = drawSegmentsFromPoints(
      border, color, 2, this.zOffsetFactor, true, false, 1.0,
    );
    scene.add(mesh);
    drewObjects.push(mesh);

    return drewObjects;
  }

  addCurve(lines, color, coordinates, scene) {
    const drewObjects = [];
    lines.forEach((line) => {
      line.segment.forEach((segment) => {
        const points = coordinates.applyOffsetToArray(segment.lineSegment.point);
        const mesh = drawSegmentsFromPoints(
          points, color, 5, this.zOffsetFactor * 2, false,
        );
        scene.add(mesh);
        drewObjects.push(mesh);
      });
    });
    return drewObjects;
  }

  addStopLine(stopLine, coordinates, scene) {
    const drewObjects = this.addCurve(
      stopLine, colorMapping.PURE_WHITE, coordinates, scene,
    );
    return drewObjects;
  }

  removeDrewText(textMesh, scene) {
    if (textMesh) {
      textMesh.children.forEach((c) => c.visible = false);
      scene.remove(textMesh);
    }
  }

  removeDrewObjects(drewObjects, scene) {
    if (drewObjects) {
      drewObjects.forEach((object) => {
        scene.remove(object);
        if (object.geometry) {
          object.geometry.dispose();
        }
        if (object.material) {
          object.material.dispose();
        }
      });
    }
  }

  removeAllElements(scene) {
    this.removeExpiredElements([], scene);
    this.trafficSignals.removeAll(scene);
    this.stopSigns.removeAll(scene);
    this.yieldSigns.removeAll(scene);
  }

  removeExpiredElements(elementIds, scene) {
    const newData = {};
    for (const kind in this.data) {
      const drawThisKind = this.shouldDrawObjectOfThisElementKind(kind);
      newData[kind] = [];
      const oldDataOfThisKind = this.data[kind];
      const currentIds = elementIds[kind];
      oldDataOfThisKind.forEach((oldData) => {
        if (drawThisKind && currentIds && currentIds.includes(oldData.id.id)) {
          newData[kind].push(oldData);
        } else {
          this.removeDrewObjects(oldData.drewObjects, scene);
          this.removeDrewText(oldData.text, scene);
        }
      });
    }
    this.data = newData;
  }

  // I do not want to do premature optimization either. Should the
  // performance become an issue, all the diff should be done at the server
  // side. This also means that the server should maintain a state of
  // (possibly) visible elements, presummably in the global store.
  appendMapData(newData, coordinates, scene) {
    const parkingSpaceCalcInfo = [];
    const deadEndJunction = [];
    let deadJunctionInfos = [];
    for (const kind in newData) {
      if (!newData[kind]) {
        continue;
      }

      if (!this.data[kind]) {
        this.data[kind] = [];
      }

      for (let i = 0; i < newData[kind].length; ++i) {
        switch (kind) {
          case 'lane':
            const lane = newData[kind][i];
            this.data[kind].push(Object.assign(newData[kind][i], {
              drewObjects: this.addLane(lane, coordinates, scene),
              text: this.addLaneId(lane, coordinates, scene),
            }));
            break;
          case 'clearArea':
            this.data[kind].push(Object.assign(newData[kind][i], {
              drewObjects: this.addZone(
                newData[kind][i], colorMapping.YELLOW, coordinates, scene,
              ),
            }));
            break;
          case 'crosswalk':
            this.data[kind].push(Object.assign(newData[kind][i], {
              drewObjects: this.addZone(
                newData[kind][i], colorMapping.PURE_WHITE, coordinates, scene,
              ),
            }));
            break;
          case 'junction':
            if (newData[kind][i].type === 'DEAD_END') {
              deadEndJunction.push(newData[kind][i]);
            }
            this.data[kind].push(Object.assign(newData[kind][i], {
              drewObjects: this.addBorder(
                newData[kind][i], colorMapping.BLUE, coordinates, scene,
              ),
            }));
            break;
          case 'pncJunction':
            this.data[kind].push(Object.assign(newData[kind][i], {
              drewObjects: this.addZone(
                newData[kind][i], colorMapping.BLUE, coordinates, scene,
              ),
            }));
            break;
          case 'signal':
            this.data[kind].push(Object.assign(newData[kind][i], {
              drewObjects: this.addStopLine(
                newData[kind][i].stopLine, coordinates, scene,
              ),
            }));
            this.trafficSignals.add([newData[kind][i]], coordinates, scene);
            break;
          case 'stopSign':
            this.data[kind].push(Object.assign(newData[kind][i], {
              drewObjects: this.addStopLine(
                newData[kind][i].stopLine, coordinates, scene,
              ),
            }));
            this.stopSigns.add([newData[kind][i]], coordinates, scene);
            break;
          case 'yield':
            this.data[kind].push(Object.assign(newData[kind][i], {
              drewObjects: this.addStopLine(
                newData[kind][i].stopLine, coordinates, scene,
              ),
            }));
            this.yieldSigns.add([newData[kind][i]], coordinates, scene);
            break;
          case 'road':
            const road = newData[kind][i];
            this.data[kind].push(Object.assign(newData[kind][i], {
              drewObjects: this.addRoad(road, coordinates, scene),
            }));
            break;
          case 'parkingSpace':
            this.data[kind].push(Object.assign(newData[kind][i], {
              drewObjects: this.addBorder(
                newData[kind][i], colorMapping.YELLOW, coordinates, scene,
              ),
              text: this.addParkingSpaceId(newData[kind][i], coordinates, scene),
            }));
            parkingSpaceCalcInfo.push(this.calcParkingSpaceExtraInfo(newData[kind][i],
              coordinates));
            break;
          case 'speedBump':
            this.data[kind].push(Object.assign(newData[kind][i], {
              drewObjects: this.addCurve(
                newData[kind][i].position, colorMapping.RED, coordinates, scene,
              ),
            }));
            break;
          default:
            this.data[kind].push(newData[kind][i]);
            break;
        }
      }
    }
    if (!_.isEmpty(deadEndJunction)) {
      deadJunctionInfos =
        this.getDeadEndJunctionInfo(deadEndJunction, coordinates);
    }
    return [parkingSpaceCalcInfo, deadJunctionInfos];
  }

  shouldDrawObjectOfThisElementKind(kind) {
    // Ex: mapping 'lane' to 'showMapLane' option
    const optionName = `showMap${kind[0].toUpperCase()}${kind.slice(1)}`;

    // NOTE: return true if the option is not found
    return STORE.options[optionName] !== false;
  }

  shouldDrawTextOfThisElementKind(kind) {
    // showMapLaneId option controls both laneId and parkingSpaceId
    return STORE.options.showMapLaneId && ['parkingSpace', 'lane'].includes(kind);
  }

  updateText() {
    for (const kind in this.data) {
      const isVisible = this.shouldDrawTextOfThisElementKind(kind);
      this.data[kind].forEach((element) => {
        if (element.text) {
          element.text.visible = isVisible;
        }
      });
    }
  }

  updateIndex(hash, elementIds, scene) {
    if (STORE.hmi.inNavigationMode) {
      MAP_WS.requestRelativeMapData();
    } else {
      this.updateText();

      let newElementKindsDrawn = '';
      for (const kind of Object.keys(elementIds).sort()) {
        if (this.shouldDrawObjectOfThisElementKind(kind)) {
          newElementKindsDrawn += kind;
        }
      }

      if (hash !== this.hash || this.elementKindsDrawn !== newElementKindsDrawn) {
        this.hash = hash;
        this.elementKindsDrawn = newElementKindsDrawn;
        const diff = this.diffMapElements(elementIds, this.data);
        if (!_.isEmpty(diff) || !this.initialized) {
          MAP_WS.requestMapData(diff);
          this.initialized = true;
        }

        this.removeExpiredElements(elementIds, scene);

        if (!this.shouldDrawObjectOfThisElementKind('signal')) {
          this.trafficSignals.removeAll(scene);
        } else {
          this.trafficSignals.removeExpired(elementIds.signal, scene);
        }

        if (!this.shouldDrawObjectOfThisElementKind('stopSign')) {
          this.stopSigns.removeAll(scene);
        } else {
          this.stopSigns.removeExpired(elementIds.stopSign, scene);
        }

        if (!this.shouldDrawObjectOfThisElementKind('yield')) {
          this.yieldSigns.removeAll(scene);
        } else {
          this.yieldSigns.removeExpired(elementIds.yield, scene);
        }
      }
    }
    // Do not set zOffset in camera view, since zOffset will affect the accuracy of matching
    // between hdmap and camera image
    this.zOffsetFactor = STORE.options.showCameraView ? 0 : 1;
  }

  update(world) {
    this.trafficSignals.updateTrafficLightStatus(world.perceivedSignal);
  }

  changeSelectedParkingSpaceColor(index, color = 0xff0000) {
    this.data.parkingSpace[index].drewObjects.forEach(mesh => {
      changeMaterial(mesh, color);
    });
  }

  // find parking space based which lane
  getLaneBasedOverlapId(overlapId, coordinates) {
    // Default based one lane if overlapId.length>=2 only choose the first
    if (_.isEmpty(overlapId)) {
      return null;
    }
    const laneIndex = _.findIndex(this.data.lane, item => {
      return _.findIndex(item.overlapId, { 'id': overlapId[0].id }) !== -1;
    });
    if (laneIndex === -1) {
      return null;
    }
    const lane = this.data.lane[laneIndex];
    const points = this.getPointsFromLane(lane, coordinates);
    return {
      centerLine: points,
      length: _.get(lane, 'length'),
      successorId: _.get(lane, 'successorId'), // array
      predecessorId: _.get(lane, 'predecessorId'), // array
    };
  }

  // get all offset points from the lane's segements
  getPointsFromLane(lane, coordinates, offset = true) {
    const centralLine = _.get(lane, 'centralCurve.segment');
    if (_.isEmpty(centralLine)) {
      return null;
    }
    let arrs = [];
    if (centralLine.length !== 1) {
      for (const segment of centralLine) {
        arrs.push(_.get(segment, 'lineSegment.point'));
      }
      arrs = _.uniq(_.flattenDeep(arrs));
    }
    let points = _.isEmpty(arrs) ? _.get(centralLine[0], 'lineSegment.point') : arrs;
    if (offset) {
      points = coordinates.applyOffsetToArray(points);
    }
    return points;
  }
  // id: lane id
  // totalLength: the distance from start point to the lane's end point
  // backward: direction,find forward or reverse.
  getRoutingPointAlongLane(id, totalLength, coordinates, threshold, backward = true) {
    while (totalLength < threshold) {
      const res = this.findFixedDistancePointOnLane(threshold - totalLength, id,
        coordinates, backward);
      if (_.isEmpty(res)) {
        return null;
      }
      else if (res.x) {
        return [res, _.get(id, '0.id')];
      }
      else {
        totalLength += res.length;
        id = res.nextId;
      }
    }
  }

  findFixedDistancePointOnLane(distance, laneId, coordinates, backward = true) {
    const laneIndex = _.findIndex(this.data.lane, item => {
      return _.isEqual(item.id, laneId[0]);
    });
    if (laneIndex === -1) {
      return null;
    }
    const lane = this.data.lane[laneIndex];
    let totalLength = distance;
    if (lane.length >= totalLength) {
      const centerLine = _.get(lane, 'centralCurve.segment');
      if (_.isEmpty(centerLine)) {
        return null;
      }
      let index = backward ? 0 : centerLine.length - 1;
      let result = null;
      if (backward) {
        while (index <= centerLine.length - 1) {
          if (totalLength > centerLine[index].length) {
            totalLength -= centerLine[index].length;
            index++;
          } else {
            result = this.findFixedDistancePointOnSegment(totalLength,
              centerLine[index], coordinates, backward);
            break;
          }
        }
      } else {
        while (index >= 0) {
          if (totalLength > centerLine[index].length) {
            totalLength -= centerLine[index].length;
            index--;
          } else {
            result = this.findFixedDistancePointOnSegment(totalLength,
              centerLine[index], coordinates, backward);
            break;
          }
        }
      }
      return result;
    } else {
      return {
        length: lane.length,
        nextId: backward ? lane.successorId : lane.predecessorId,
      };
    }
  }
  // onSegment
  findFixedDistancePointOnSegment(distance, segmentPoints, coordinates, backward = true) {
    let points = _.get(segmentPoints, 'lineSegment.point');
    if (_.isEmpty(points) || points.length < 2) {
      return null;
    }
    points = coordinates.applyOffsetToArray(points);
    const startPoint = backward ? points[0] : points[points.length - 1];
    let index = backward ? 1 : points.length - 2;
    if (backward) {
      while (index <= points.length - 1) {
        if (getPointDistance(startPoint, points[index]) >= distance) {
          break;
        }
        index++;
      }
    } else {
      while (index >= 0) {
        if (getPointDistance(startPoint, points[index]) >= distance) {
          break;
        }
        index--;
      }
    }
    return points[index];
  }

  // To get the first point along lane in certain direction
  // where the distance from the starting point not less than
  // the threshold
  // successor: the direction
  // points: the points on lane
  // if laneVector = null，means start point 0 or end point based direction
  getRoutingPoint(successor, startPoint, threshold,
    points, laneVector, coordinates, id) {
    if (successor) {
      const distance = getPointDistance(startPoint, points[points.length - 1]);
      if (distance >= threshold) {
        const index = getInFrontOfPointIndexDistanceApart(threshold,
          points, startPoint, laneVector);
        if (index === -1) {
          return null;
        }
        return [points[index], _.get(id, '0.id')];
      } else {
        if (_.isEmpty(id)) {
          return null;
        }
        return this.getRoutingPointAlongLane(id, distance, coordinates, threshold);
      }
    }
    else {
      const distance = getPointDistance(startPoint, points[0]);
      if (distance >= threshold) {
        const index = getBehindPointIndexDistanceApart(threshold,
          points, startPoint, laneVector);
        if (index === -1) {
          return null;
        }
        return [points[index], _.get(id, '0.id')];
      } else {
        return this.getRoutingPointAlongLane(id,
          distance, coordinates, threshold, false);
      }
    }
  }

  calcParkingSpaceExtraInfo(parkingSpace, coordinates) {
    const border = coordinates.applyOffsetToArray(parkingSpace.polygon.point);
    const basedLane = this.getLaneBasedOverlapId(parkingSpace.overlapId, coordinates);
    let routingPoint = null;
    if (_.isEmpty(basedLane)) {
      return null;
    }
    const centerLine = basedLane.centerLine;
    let result = [];
    const laneCenterLineEndPoint = centerLine[centerLine.length - 1];
    let intersectionPoint = null;
    const laneVector = {
      x: laneCenterLineEndPoint.x - centerLine[0].x,
      y: laneCenterLineEndPoint.y - centerLine[0].y,
    };
    const vector01 = {
      x: border[1].x - border[0].x,
      y: border[1].y - border[0].y,
    };
    const vector12 = {
      x: border[1].x - border[2].x,
      y: border[1].y - border[2].y,
    };
    const parallel = directionVectorCrossProduct(laneVector, vector01, true)
      > directionVectorCrossProduct(laneVector, vector12, true) ? 2 : 1;
    let orderIndex = -1;
    if (parallel === 1) {
      const mid01 = {
        x: (border[0].x + border[1].x) / 2,
        y: (border[0].y + border[1].y) / 2,
      };
      const mid23 = {
        x: (border[2].x + border[3].x) / 2,
        y: (border[2].y + border[3].y) / 2,
      };
      intersectionPoint = getIntersectionPoint(mid01, centerLine[0], laneCenterLineEndPoint);
      if (intersectionPoint.x === mid01.x || intersectionPoint.x === mid23.x
        || mid01.x === mid23.x) {
        // equal x situation
        if (intersectionPoint.y < mid01.y) {
          if (mid01.y < mid23.y) {
            // 01->23
            orderIndex = pointOnVectorRight(border[3], mid01, mid23) ? 3 : 2;
          } else {
            // 23->01
            orderIndex = pointOnVectorRight(border[0], mid23, mid01) ? 0 : 1;
          }
        } else {
          if (mid01.y < mid23.y) {
            // 23->01
            orderIndex = pointOnVectorRight(border[0], mid23, mid01) ? 0 : 1;
          } else {
            // 01->23
            orderIndex = pointOnVectorRight(border[3], mid01, mid23) ? 3 : 2;
          }
        }
      } else {
        if (intersectionPoint.x < mid01.x) {
          if (mid01.x < mid23.x) {
            orderIndex = pointOnVectorRight(border[3], mid01, mid23) ? 3 : 2;
          } else {
            // 32 -> 01
            orderIndex = pointOnVectorRight(border[0], mid23, mid01) ? 0 : 1;
          }
        } else {
          if (mid01.x < mid23.x) {
            // 32->01
            orderIndex = pointOnVectorRight(border[0], mid23, mid01) ? 0 : 1;
          } else {
            // 01->32
            orderIndex = pointOnVectorRight(border[3], mid01, mid23) ? 3 : 2;
          }
        }
      }
      result = order1[orderIndex];
    } else {
      const mid12 = {
        x: (border[2].x + border[1].x) / 2,
        y: (border[2].y + border[1].y) / 2,
      };
      const mid03 = {
        x: (border[0].x + border[3].x) / 2,
        y: (border[0].y + border[3].y) / 2,
      };
      intersectionPoint = getIntersectionPoint(mid12, centerLine[0], laneCenterLineEndPoint);
      if (intersectionPoint.x === mid12.x || intersectionPoint.x === mid03.x
        || mid12.x === mid03.x) {
        if (intersectionPoint.y < mid12.y) {
          if (mid12.y < mid03.y) {
            // 12->03
            orderIndex = pointOnVectorRight(border[0], mid12, mid03) ? 0 : 3;
          } else {
            // 03->12
            orderIndex = pointOnVectorRight(border[1], mid03, mid12) ? 1 : 2;
          }
        } else {
          if (mid12.y < mid03.y) {
            // 03->12
            orderIndex = pointOnVectorRight(border[1], mid03, mid12) ? 1 : 2;
          } else {
            // 12->03
            orderIndex = pointOnVectorRight(border[0], mid12, mid03) ? 0 : 3;
          }
        }
      } else {
        if (intersectionPoint.x < mid12.x) {
          if (mid12.x < mid03.x) {
            // 12->03
            orderIndex = pointOnVectorRight(border[0], mid12, mid03) ? 0 : 3;
          } else {
            // 03 -> 12
            orderIndex = pointOnVectorRight(border[1], mid03, mid12) ? 1 : 2;
          }
        } else {
          if (mid12.x < mid03.x) {
            // 03->12
            orderIndex = pointOnVectorRight(border[1], mid03, mid12) ? 1 : 2;
          } else {
            // 12->03
            orderIndex = pointOnVectorRight(border[0], mid12, mid03) ? 0 : 3;
          }
        }
      }
      result = order2[orderIndex];
    }
    const successor = directionSameWithVector(border[result[0]], border[result[1]], laneVector);
    const projectionPointOnLane = getIntersectionPoint(border[result[2]], centerLine[0],
      laneCenterLineEndPoint);
    const laneWidth = getPointDistance(border[result[2]], projectionPointOnLane) * 4;
    const id = successor ? basedLane.successorId : basedLane.predecessorId;
    const routingRes = this.getRoutingPoint(successor, projectionPointOnLane,
      STORE.routeEditingManager.parkingRoutingDistanceThreshold,
      centerLine, laneVector, coordinates, id);
    if (!_.isArray(routingRes) || routingRes.length !== 2) {
      return null;
    }
    routingPoint = routingRes[0];
    const type = getPointDistance(border[result[0]],
      border[result[1]]) < getPointDistance(border[result[2]], border[result[1]]) ? 0 : 1;
    return {
      order: result,
      type,
      laneWidth,
      routingEndPoint: routingPoint,
      laneId: routingRes[1],
    };
  }

  // Get the point on the lane that is closest to the overlap
  // between junction and lane(outside of Junction)
  // junctionPoints: junction polygon point, currently there are only
  // rectangular junctions.
  // reverse means find direction
  // return the point no offset (for in lane) the related info array (for out lane)
  getPointClosestToTheJunctionOnLane(lane, junctionPoints, coordinates, reverse = false) {
    let laneEndPoint = getLaneFirstAndLastPoint(lane);
    laneEndPoint = coordinates.applyOffsetToArray(laneEndPoint);
    if (_.isEmpty(laneEndPoint)) {
      return null;
    }
    let targetLane = lane;
    const direction = reverse ? 'successorId' : 'predecessorId';
    while (isLaneCompleteInRectangle(junctionPoints, laneEndPoint)) {
      targetLane = _.find(this.data.lane,
        item => _.isEqual(item.id, _.get(lane, `${direction}.0`)));// lane.predecessorId[0]
      if (_.isEmpty(targetLane)) {
        return null;
      }
      laneEndPoint = coordinates.applyOffsetToArray(getLaneFirstAndLastPoint(targetLane));
    }
    const laneSegment = _.get(targetLane, 'centralCurve.segment');
    if (_.isEmpty(laneSegment)) {
      return null;
    }
    let findTargetPoint = false;
    let targetPoint = null;
    let points = null;
    let offsetPoints = null;
    let idx = 0;
    if (reverse) {
      for (; idx < laneSegment.length && !findTargetPoint; idx++) {
        points = _.get(laneSegment[idx], 'lineSegment.point');
        offsetPoints = coordinates.applyOffsetToArray(points);
        if (_.isEmpty(offsetPoints)) {
          return null;
        } else {
          const pointIndex = _.findIndex(offsetPoints,
            point => !IsPointInRectangle(junctionPoints, point));
          if (pointIndex !== -1) {
            targetPoint = pointIndex;
            findTargetPoint = true;
          }
        }
      }
    } else {
      for (let i = laneSegment.length - 1; i >= 0 && !findTargetPoint; i--) {
        points = _.get(laneSegment[i], 'lineSegment.point');
        offsetPoints = coordinates.applyOffsetToArray(points);
        if (_.isEmpty(offsetPoints)) {
          return null;
        } else {
          const pointIndex = _.findLastIndex(offsetPoints,
            point => !IsPointInRectangle(junctionPoints, point));
          if (pointIndex !== -1) {
            targetPoint = points[pointIndex];
            findTargetPoint = true;
          }
        }
      }
    }
    if (!findTargetPoint) {
      return null;
    }
    return reverse ? [targetPoint, points, targetLane, idx] : targetPoint; // no offset
  }

  getPointOnJunctionInLane(lane, junctionPoints, coordinates) {
    let laneEndPoint = getLaneFirstAndLastPoint(lane);
    laneEndPoint = coordinates.applyOffsetToArray(laneEndPoint);
    if (_.isEmpty(laneEndPoint)) {
      return null;
    }
    let InLane = lane;
    while (isLaneCompleteInRectangle(junctionPoints, laneEndPoint)) {
      InLane = _.find(this.data.lane, item => _.isEqual(item.id, lane.predecessorId[0]));
      if (_.isEmpty(InLane)) {
        return null;
      }
      laneEndPoint = coordinates.applyOffsetToArray(getLaneFirstAndLastPoint(InLane));
    }
    const laneSegment = _.get(InLane, 'centralCurve.segment');
    if (_.isEmpty(laneSegment)) {
      return null;
    }
    let findInLanePoint = false;
    let inLanePoint = null;
    for (let i = laneSegment.length - 1; i >= 0 && !findInLanePoint; i--) {
      const points = _.get(laneSegment[i], 'lineSegment.point');
      const offsetPoints = coordinates.applyOffsetToArray(points);
      if (_.isEmpty(offsetPoints)) {
        findInLanePoint = true;
      } else {
        const pointIndex = _.findLastIndex(offsetPoints,
          point => !IsPointInRectangle(junctionPoints, point));
        if (pointIndex !== -1) {
          inLanePoint = points[pointIndex];
          findInLanePoint = true;
        }
      }
    }
    if (!findInLanePoint) {
      return null;
    }
    return inLanePoint;
  }

  getPointsOnJunctionOutLane(lane, junctionPoints, threshold, coordinates) {
    const outLaneRelatedInfo = this.getPointClosestToTheJunctionOnLane(
      lane, junctionPoints, coordinates, true);
    if (!_.isArray(outLaneRelatedInfo) || outLaneRelatedInfo.length !== 4) {
      return null;
    }
    const outLanePointIndex = outLaneRelatedInfo[0];
    let points = outLaneRelatedInfo[1];
    let offsetPoints = coordinates.applyOffsetToArray(points);
    const outLaneStartPoint = offsetPoints[outLanePointIndex];
    const outLanePoints = [points[outLanePointIndex]];
    const distance = getPointDistance(outLaneStartPoint, _.last(offsetPoints));
    if (distance > threshold) {
      // find in current segment
      const pointIdx = _.findIndex(offsetPoints,
        point => getPointDistance(outLaneStartPoint, point) >= threshold, outLanePointIndex + 1);
      if (pointIdx === -1) {
        return null;
      }
      outLanePoints.push(points[pointIdx]);
    } else if (distance === threshold) {
      outLanePoints.push(_.last(points));
    } else {
      let findRoutingPoint = false;
      let findPointIdx = null;
      let currLane = outLaneRelatedInfo[2];
      let idx = outLaneRelatedInfo[3];
      let remainThreshold = threshold - distance;
      let laneSegment = _.get(currLane, 'centralCurve.segment');
      while (!findRoutingPoint) {
        if (idx === laneSegment.length) {
          // Change Lane
          idx = 0;
          currLane = _.find(this.data.lane, item => _.isEqual(item.id, currLane.successorId[0]));
          laneSegment = _.get(currLane, 'centralCurve.segment');
          if (_.isEmpty(laneSegment)) {
            return null;
          }
        }
        if (laneSegment[idx].length < remainThreshold) {
          remainThreshold -= laneSegment[idx].length;
          idx++;
        } else {
          points = _.get(laneSegment[idx], 'lineSegment.point');
          offsetPoints = coordinates.applyOffsetToArray(points);
          findPointIdx = _.findIndex(offsetPoints,
            p => getPointDistance(offsetPoints[0], p) >= remainThreshold, 1);
          if (findPointIdx === -1) {
            return null;
          }
          findRoutingPoint = true;
          outLanePoints.push(points[findPointIdx]);
        }
      }
    }
    return outLanePoints;
  }

  // Get lane ids which meet the following conditions
  // along a certain direction of lane: The point on
  // the lane is within a certain threshold from the starting point
  // direction: predecessorId(in) successorId(out)
  getRangeLaneIds(startPoint, lane, threshold, direction) {
    const laneEndPoint = (direction === 'predecessorId') ? getLaneFirstPoint(lane)
      : getLaneLastPoint(lane);
    if (_.isEmpty(laneEndPoint)) {
      return null;
    }
    const idsArr = [_.get(lane, 'id.id')];
    let distance = getPointDistance(startPoint, laneEndPoint);
    let nextLaneId = _.get(lane, `${direction}.0.id`);
    while (distance < threshold && nextLaneId) {
      const nextLane = _.find(this.data.lane, item => _.isEqual(_.get(item, 'id.id'), nextLaneId));
      if (_.isEmpty(nextLane)) {
        break;
      }
      distance += nextLane.length;
      idsArr.push(nextLaneId);
      nextLaneId = _.get(nextLane, `${direction}.0.id`);
    }
    return idsArr;
  }

  getInAndOutLaneForDeadEndJunction(deadJunction, coordinates) {
    const deadJunctionInfo = {};
    const { overlapId } = deadJunction;
    if (!_.isArray(overlapId) || overlapId.length < 2) {
      return null;
    }
    const lanes = [];
    overlapId.forEach(overlap => {
      const overlapLane = _.find(this.data.lane,
        lane => _.findIndex(lane.overlapId, overlap) !== -1);
      if (!_.isEmpty(overlapLane)) {
        lanes.push(overlapLane);
      }
    });
    if (lanes.length < 2) {
      return null;
    }
    // grouping overlap lane to two groups
    const laneGroup1 = [lanes[0]];
    const laneGroup2 = [];
    for (let i = 1; i < lanes.length; i++) {
      const relation1 = determineTheRelationBetweenLanes(
        laneGroup1[0].predecessorId, _.last(laneGroup1).successorId, lanes[i],
      );
      if (relation1) {
        (relation1 === 1) ? laneGroup1.unshift(lanes[i]) : laneGroup1.push(lanes[i]);
      } else {
        if (_.isEmpty(laneGroup2)) {
          laneGroup2.push(lanes[i]);
        } else {
          const relation2 = determineTheRelationBetweenLanes(
            laneGroup2[0].predecessorId, _.last(laneGroup2).successorId, lanes[i],
          );
          if (!relation2) {
            return null;
          }
          (relation2 > 1) ? laneGroup2.unshift(lanes[i]) : laneGroup2.push(lanes[i]);
        }
      }
    }

    if (_.isEmpty(laneGroup2)) {
      return null;
    }
    const laneGroup = [laneGroup1, laneGroup2];
    const deadEndJunctionPoints = coordinates.applyOffsetToArray(deadJunction.polygon.point);
    laneGroup.forEach(group => {
      let laneEndPoint = getLaneArrayFirstAndLastPoint(group[0], _.last(group));
      if (!_.isEmpty(laneEndPoint)) {
        laneEndPoint = coordinates.applyOffsetToArray(laneEndPoint);
        deadJunctionInfo[determinLaneDirection(laneEndPoint, deadEndJunctionPoints[0])] = group;
      }
    });
    if (!_.has(deadJunctionInfo, 'in') || !_.has(deadJunctionInfo, 'out')) {
      return null;
    }
    // After grouping, choose the one with the least overlap
    // Ideally, there are some points outside of junction.
    deadJunctionInfo.in = deadJunctionInfo.in[0];
    deadJunctionInfo.out = deadJunctionInfo.out[0];
    const laneDistanceThreshold = 100;
    deadJunctionInfo.inEndPoint = getLaneLastPoint(deadJunctionInfo.in);
    deadJunctionInfo.inLaneIds = this.getRangeLaneIds(
      deadJunctionInfo.inEndPoint, deadJunctionInfo.in, laneDistanceThreshold, 'predecessorId');
    const routingPointThreshold = 10;
    deadJunctionInfo.outStartPoint = getLaneFirstPoint(deadJunctionInfo.out);
    const lanePoints = this.getPointsFromLane(deadJunctionInfo.out, coordinates, false);
    if (!_.isArray(lanePoints) || lanePoints.length < 2) {
      return null;
    }
    const routingPointInfo = this.getRoutingPoint(
      true, deadJunctionInfo.outStartPoint, routingPointThreshold,
      lanePoints, null, coordinates, _.get(deadJunctionInfo.out, 'successorId'),
    );
    if (!_.isArray(routingPointInfo) || routingPointInfo.length !== 2) {
      return null;
    }
    const offsetRoutingPoint = coordinates.applyOffset(
      { x: routingPointInfo[0].x, y: routingPointInfo[0].y },
      true
    );
    deadJunctionInfo.routingPoint = offsetRoutingPoint;
    deadJunctionInfo.deadJunctionPoints = deadJunction.polygon.point;
    deadJunctionInfo.outLaneIds = this.getRangeLaneIds(
      deadJunctionInfo.outStartPoint, deadJunctionInfo.out, laneDistanceThreshold, 'successorId');
    deadJunctionInfo.deadJunctionId = deadJunction.id.id;
    let validDeadJunctionInfo = true;
    Object.keys(deadJunctionInfo).forEach(key => {
      if (_.isNil(deadJunctionInfo[key])) {
        validDeadJunctionInfo = false;
      }
    });
    return (validDeadJunctionInfo) ? deadJunctionInfo : null;
  }

  getDeadEndJunctionInfo(deadEndJunctions, coordinates) {
    const deadJunctionInfos = [];
    for (let i = 0; i < deadEndJunctions.length; i++) {
      const deadJunctionInfo =
        this.getInAndOutLaneForDeadEndJunction(deadEndJunctions[i], coordinates);
      if (_.isEmpty(deadJunctionInfo)) {
        return null;
      }
      deadJunctionInfos.push(deadJunctionInfo);
    }
    return deadJunctionInfos;
  }
}
