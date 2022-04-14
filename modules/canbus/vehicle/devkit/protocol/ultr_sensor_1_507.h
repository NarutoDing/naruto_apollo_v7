/******************************************************************************
 * Copyright 2020 The Apollo Authors. All Rights Reserved.
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
namespace devkit {

class Ultrsensor1507 : public ::apollo::drivers::canbus::ProtocolData<
                           ::apollo::canbus::ChassisDetail> {
 public:
  static const int32_t ID;
  Ultrsensor1507();
  void Parse(const std::uint8_t* bytes, int32_t length,
             ChassisDetail* chassis) const override;

 private:
  // config detail: {'name': 'uiUSS9_ToF_Direct', 'offset': 0.0, 'precision':
  // 0.01724, 'len': 16, 'is_signed_var': False, 'physical_range': '[0|65535]',
  // 'bit': 23, 'type': 'double', 'order': 'motorola', 'physical_unit': 'cm'}
  double uiuss9_tof_direct(const std::uint8_t* bytes,
                           const int32_t length) const;

  // config detail: {'name': 'uiUSS8_ToF_Direct', 'offset': 0.0, 'precision':
  // 0.01724, 'len': 16, 'is_signed_var': False, 'physical_range': '[0|65535]',
  // 'bit': 7, 'type': 'double', 'order': 'motorola', 'physical_unit': 'cm'}
  double uiuss8_tof_direct(const std::uint8_t* bytes,
                           const int32_t length) const;

  // config detail: {'name': 'uiUSS11_ToF_Direct', 'offset': 0.0, 'precision':
  // 0.01724, 'len': 16, 'is_signed_var': False, 'physical_range': '[0|65535]',
  // 'bit': 55, 'type': 'double', 'order': 'motorola', 'physical_unit': 'cm'}
  double uiuss11_tof_direct(const std::uint8_t* bytes,
                            const int32_t length) const;

  // config detail: {'name': 'uiUSS10_ToF_Direct', 'offset': 0.0, 'precision':
  // 0.01724, 'len': 16, 'is_signed_var': False, 'physical_range': '[0|65535]',
  // 'bit': 39, 'type': 'double', 'order': 'motorola', 'physical_unit': 'cm'}
  double uiuss10_tof_direct(const std::uint8_t* bytes,
                            const int32_t length) const;
};

}  // namespace devkit
}  // namespace canbus
}  // namespace apollo
