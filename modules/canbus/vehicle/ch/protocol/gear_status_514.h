/******************************************************************************
 * Copyright 2019 The Apollo Authors. All Rights Reserved.
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

#pragma once

#include "modules/canbus/proto/chassis_detail.pb.h"
#include "modules/drivers/canbus/can_comm/protocol_data.h"

namespace apollo {
namespace canbus {
namespace ch {

class Gearstatus514 : public ::apollo::drivers::canbus::ProtocolData<
                          ::apollo::canbus::ChassisDetail> {
 public:
  static const int32_t ID;
  Gearstatus514();
  void Parse(const std::uint8_t* bytes, int32_t length,
             ChassisDetail* chassis) const override;

 private:
  // config detail: {'description': 'PRND control(Status)', 'enum': {1:
  // 'GEAR_STS_PARK', 2: 'GEAR_STS_REVERSE', 3: 'GEAR_STS_NEUTRAL', 4:
  // 'GEAR_STS_DRIVE'}, 'precision': 1.0, 'len': 8, 'name': 'GEAR_STS',
  // 'is_signed_var': False, 'offset': 0.0, 'physical_range': '[1|4]', 'bit': 0,
  // 'type': 'enum', 'order': 'intel', 'physical_unit': ''}
  Gear_status_514::Gear_stsType gear_sts(const std::uint8_t* bytes,
                                         const int32_t length) const;
};

}  // namespace ch
}  // namespace canbus
}  // namespace apollo
