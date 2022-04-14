/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#include "modules/drivers/lidar/velodyne/parser/velodyne_parser.h"

namespace apollo {
namespace drivers {
namespace velodyne {

Velodyne32Parser::Velodyne32Parser(const Config& config)
    : VelodyneParser(config), previous_firing_stamp_(0), gps_base_usec_(0) {
  inner_time_ = &velodyne::INNER_TIME_HDL32E;
  need_two_pt_correction_ = false;
  if (config_.model() == VLP32C) {
    inner_time_ = &velodyne::INNER_TIME_VLP32C;
  }
}

void Velodyne32Parser::GeneratePointcloud(
    const std::shared_ptr<VelodyneScan>& scan_msg,
    std::shared_ptr<PointCloud> out_msg) {
  // allocate a point cloud with same time and frame ID as raw data
  out_msg->mutable_header()->set_frame_id(scan_msg->header().frame_id());
  out_msg->set_height(1);
  out_msg->mutable_header()->set_sequence_num(
      scan_msg->header().sequence_num());
  gps_base_usec_ = scan_msg->basetime();

  size_t packets_size = scan_msg->firing_pkts_size();
  if (config_.model() == VLP32C) {
    for (size_t i = 0; i < packets_size; ++i) {
      UnpackVLP32C(scan_msg->firing_pkts(static_cast<int>(i)), out_msg);
    }
  } else {
    for (size_t i = 0; i < packets_size; ++i) {
      Unpack(scan_msg->firing_pkts(static_cast<int>(i)), out_msg);
    }
  }

  // set measurement and lidar_timestampe
  int size = out_msg->point_size();
  if (size == 0) {
    // we discard this pointcloud if empty
    AERROR << "All points is NAN!Please check velodyne:" << config_.model();
  } else {
    // take the last point's timestamp as the whole frame's measurement time.
    uint64_t timestamp = out_msg->point(size - 1).timestamp();
    out_msg->set_measurement_time(static_cast<double>(timestamp) / 1e9);
    out_msg->mutable_header()->set_lidar_timestamp(timestamp);
  }

  // set default width
  out_msg->set_width(out_msg->point_size());

  last_time_stamp_ = out_msg->measurement_time();
}

uint64_t Velodyne32Parser::GetTimestamp(double base_time, float time_offset,
                                        uint16_t block_id) {
  double t = base_time - time_offset;
  if (config_.model() == VLP32C) {
    t = base_time + time_offset;
  }
  // Now t is the exact laser firing time for a specific data point.
  if (t < previous_firing_stamp_) {
    // plus 3600 when large jump back, discard little jump back for wrong time
    // in lidar
    if (std::abs(previous_firing_stamp_ - t) > 3599000000) {
      gps_base_usec_ += static_cast<uint64_t>(3600 * 1e6);
      AINFO << "Base time plus 3600s. Model: " << config_.model() << std::fixed
            << ". current:" << t << ", last time:" << previous_firing_stamp_;
    } else if (config_.model() != VLP32C ||
               (previous_firing_stamp_ - t > 34.560f) ||
               (previous_firing_stamp_ - t < 34.559f)) {
      AWARN << "Current stamp:" << std::fixed << t
            << " less than previous stamp:" << previous_firing_stamp_
            << ". GPS time stamp maybe incorrect!";
    }
  } else if (previous_firing_stamp_ != 0 &&
             t - previous_firing_stamp_ > 100000) {  // 100ms
    AERROR << "Current stamp:" << std::fixed << t
           << " ahead previous stamp:" << previous_firing_stamp_
           << " over 100ms. GPS time stamp incorrect!";
  }

  previous_firing_stamp_ = t;
  // in nano seconds
  uint64_t gps_stamp = gps_base_usec_ * 1000 + static_cast<uint64_t>(t * 1000);

  return gps_stamp;
}

void Velodyne32Parser::UnpackVLP32C(const VelodynePacket& pkt,
                                    std::shared_ptr<PointCloud> pc) {
  const RawPacket* raw = (const RawPacket*)pkt.data().c_str();
  // This is the packet timestamp which marks the moment of the first data point
  // in the first firing sequence of the first data block. The time stamp’s
  // value is the number of microseconds elapsed since the top of the hour. The
  // number ranges from 0 to 3,599,999,999, the number of microseconds in one
  // hour (Sec. 9.3.1.6 in VLP-32C User Manual).
  double basetime = static_cast<double>(raw->gps_timestamp);  // usec
  float azimuth = 0.0f;
  float azimuth_diff = 0.0f;
  float last_azimuth_diff = 0.0f;
  float azimuth_corrected_f = 0.0f;
  int azimuth_corrected = 0;

  for (int i = 0; i < BLOCKS_PER_PACKET; i++) {  // 12
    azimuth = static_cast<float>(raw->blocks[i].rotation);
    if (i < (BLOCKS_PER_PACKET - 1)) {
      azimuth_diff = static_cast<float>(
          (36000 + raw->blocks[i + 1].rotation - raw->blocks[i].rotation) %
          36000);
      last_azimuth_diff = azimuth_diff;
    } else {
      azimuth_diff = last_azimuth_diff;
    }
    for (int laser_id = 0, k = 0; laser_id < SCANS_PER_BLOCK;
         ++laser_id, k += RAW_SCAN_SIZE) {  // 32, 3
      LaserCorrection& corrections = calibration_.laser_corrections_[laser_id];

      union RawDistance raw_distance;
      raw_distance.bytes[0] = raw->blocks[i].data[k];
      raw_distance.bytes[1] = raw->blocks[i].data[k + 1];

      // compute the actual timestamp associated with the data point at data
      // block i and laser_id
      uint64_t timestamp = GetTimestamp(basetime, (*inner_time_)[i][laser_id],
                                        static_cast<uint16_t>(i));

      azimuth_corrected_f =
          azimuth + (azimuth_diff * (static_cast<float>(laser_id) / 2.0f) *
                     CHANNEL_TDURATION / SEQ_TDURATION);
      azimuth_corrected =
          static_cast<int>(round(fmod(azimuth_corrected_f, 36000.0)));

      float real_distance =
          raw_distance.raw_distance * VLP32_DISTANCE_RESOLUTION;
      float distance = real_distance + corrections.dist_correction;

      // AINFO << "raw_distance:" << raw_distance.raw_distance << ", distance:"
      // << distance;
      if (raw_distance.raw_distance == 0 ||
          !is_scan_valid(azimuth_corrected, distance)) {
        if (config_.organized()) {
          apollo::drivers::PointXYZIT* point_new = pc->add_point();
          point_new->set_x(nan);
          point_new->set_y(nan);
          point_new->set_z(nan);
          point_new->set_timestamp(timestamp);
          point_new->set_intensity(0);
        }
        continue;
      }

      apollo::drivers::PointXYZIT* point = pc->add_point();
      point->set_timestamp(timestamp);
      // Position Calculation, append this point to the cloud
      ComputeCoords(real_distance, corrections,
                    static_cast<uint16_t>(azimuth_corrected), point);
      point->set_intensity(raw->blocks[i].data[k + 2]);
    }
  }
}

void Velodyne32Parser::Unpack(const VelodynePacket& pkt,
                              std::shared_ptr<PointCloud> pc) {
  // const RawPacket* raw = (const RawPacket*)&pkt.data[0];
  const RawPacket* raw = (const RawPacket*)pkt.data().c_str();
  double basetime = raw->gps_timestamp;  // usec

  for (int i = 0; i < BLOCKS_PER_PACKET; i++) {  // 12
    for (int laser_id = 0, k = 0; laser_id < SCANS_PER_BLOCK;
         ++laser_id, k += RAW_SCAN_SIZE) {  // 32, 3
      LaserCorrection& corrections = calibration_.laser_corrections_[laser_id];

      union RawDistance raw_distance;
      raw_distance.bytes[0] = raw->blocks[i].data[k];
      raw_distance.bytes[1] = raw->blocks[i].data[k + 1];

      // compute time
      uint64_t timestamp = static_cast<uint64_t>(GetTimestamp(
          basetime, (*inner_time_)[i][laser_id], static_cast<uint16_t>(i)));

      int rotation = static_cast<int>(raw->blocks[i].rotation);
      float real_distance = raw_distance.raw_distance * DISTANCE_RESOLUTION;
      float distance = real_distance + corrections.dist_correction;

      if (raw_distance.raw_distance == 0 ||
          !is_scan_valid(rotation, distance)) {
        // if organized append a nan point to the cloud
        if (config_.organized()) {
          apollo::drivers::PointXYZIT* point_new = pc->add_point();
          point_new->set_x(nan);
          point_new->set_y(nan);
          point_new->set_z(nan);
          point_new->set_timestamp(timestamp);
          point_new->set_intensity(0);
        }
        continue;
      }

      apollo::drivers::PointXYZIT* point = pc->add_point();
      point->set_timestamp(timestamp);
      // Position Calculation, append this point to the cloud
      ComputeCoords(real_distance, corrections, static_cast<uint16_t>(rotation),
                    point);
      point->set_intensity(raw->blocks[i].data[k + 2]);
      // append this point to the cloud
    }
  }
}

void Velodyne32Parser::Order(std::shared_ptr<PointCloud> cloud) {
  if (config_.model() == VLP32C) {
    return;
  }
  int width = 32;
  cloud->set_width(width);
  int height = cloud->point_size() / cloud->width();
  cloud->set_height(height);

  std::shared_ptr<PointCloud> cloud_origin = std::make_shared<PointCloud>();
  cloud_origin->CopyFrom(*cloud);

  for (int i = 0; i < width; ++i) {
    int col = velodyne::ORDER_HDL32E[i];

    for (int j = 0; j < height; ++j) {
      // make sure offset is initialized, should be init at setup() just once
      int target_index = j * width + i;
      int origin_index = j * width + col;
      cloud->mutable_point(target_index)
          ->CopyFrom(cloud_origin->point(origin_index));
    }
  }
}

}  // namespace velodyne
}  // namespace drivers
}  // namespace apollo
