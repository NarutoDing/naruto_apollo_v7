import React from 'react';
import { observer } from 'mobx-react';

import RadioItem from 'components/common/RadioItem';

@observer
export default class POI extends React.Component {
  render() {
    const { routeEditingManager, options, inNavigationMode } = this.props;
    const entries = Object.keys(routeEditingManager.defaultRoutingEndPoint)
      .map((key, index) => (
        <RadioItem
          extraClasses={['default-routing-button']}
          key={`poi_${key}`}
          id="poi"
          title={key}
          onClick={() => {
            routeEditingManager.addDefaultEndPoint(key, inNavigationMode);
            if (!options.showRouteEditingBar) {
              routeEditingManager.sendRoutingRequest(inNavigationMode);
            }
            options.showPOI = false;
          }}
          autoFocus={index === 0}
          checked={false}
        />
      ));

    return (
      <div className="card-content-row">{entries}</div>
    );
  }
}
