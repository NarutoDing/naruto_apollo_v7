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

#pragma once

#include "modules/canbus/proto/chassis_detail.pb.h"
#include "modules/drivers/canbus/can_comm/protocol_data.h"

namespace apollo {
namespace canbus {
namespace lexus {

class Brakeauxrpt304 : public ::apollo::drivers::canbus::ProtocolData<
                           ::apollo::canbus::ChassisDetail> {
 public:
  static const int32_t ID;
  Brakeauxrpt304();
  void Parse(const std::uint8_t* bytes, int32_t length,
             ChassisDetail* chassis) const override;

 private:
  // config detail: {'name': 'BRAKE_ON_OFF_IS_VALID', 'offset': 0.0,
  // 'precision': 1.0, 'len': 1, 'is_signed_var': False, 'physical_range':
  // '[0|1]', 'bit': 60, 'type': 'bool', 'order': 'motorola', 'physical_unit':
  // ''}
  bool brake_on_off_is_valid(const std::uint8_t* bytes,
                             const int32_t length) const;

  // config detail: {'name': 'BRAKE_ON_OFF', 'offset': 0.0, 'precision': 1.0,
  // 'len': 1, 'is_signed_var': False, 'physical_range': '[0|1]', 'bit': 49,
  // 'type': 'bool', 'order': 'motorola', 'physical_unit': ''}
  bool brake_on_off(const std::uint8_t* bytes, const int32_t length) const;

  // config detail: {'name': 'USER_INTERACTION_IS_VALID', 'offset': 0.0,
  // 'precision': 1.0, 'len': 1, 'is_signed_var': False, 'physical_range':
  // '[0|1]', 'bit': 59, 'type': 'bool', 'order': 'motorola', 'physical_unit':
  // ''}
  bool user_interaction_is_valid(const std::uint8_t* bytes,
                                 const int32_t length) const;

  // config detail: {'name': 'USER_INTERACTION', 'offset': 0.0,
  // 'precision': 1.0, 'len': 1, 'is_signed_var': False, 'physical_range':
  // '[0|1]', 'bit': 48, 'type': 'bool', 'order': 'motorola', 'physical_unit':
  // ''}
  bool user_interaction(const std::uint8_t* bytes, const int32_t length) const;

  // config detail: {'name': 'RAW_BRAKE_PRESSURE_IS_VALID', 'offset': 0.0,
  // 'precision': 1.0, 'len': 1, 'is_signed_var': False, 'physical_range':
  // '[0|1]', 'bit': 58, 'type': 'bool', 'order': 'motorola', 'physical_unit':
  // ''}
  bool raw_brake_pressure_is_valid(const std::uint8_t* bytes,
                                   const int32_t length) const;

  // config detail: {'name': 'RAW_BRAKE_PRESSURE', 'offset': 0.0,
  // 'precision': 1.0, 'len': 16, 'is_signed_var': True, 'physical_range':
  // '[-32.768|32.767]', 'bit': 39, 'type': 'double', 'order': 'motorola',
  // 'physical_unit': ''}
  double raw_brake_pressure(const std::uint8_t* bytes,
                            const int32_t length) const;

  // config detail: {'name': 'RAW_PEDAL_FORCE_IS_VALID', 'offset': 0.0,
  // 'precision': 1.0, 'len': 1, 'is_signed_var': False, 'physical_range':
  // '[0|1]', 'bit': 57, 'type': 'bool', 'order': 'motorola', 'physical_unit':
  // ''}
  bool raw_pedal_force_is_valid(const std::uint8_t* bytes,
                                const int32_t length) const;

  // config detail: {'name': 'RAW_PEDAL_FORCE', 'offset': 0.0, 'precision': 1.0,
  // 'len': 16, 'is_signed_var': True, 'physical_range': '[-32.768|32.767]',
  // 'bit': 23, 'type': 'double', 'order': 'motorola', 'physical_unit': ''}
  double raw_pedal_force(const std::uint8_t* bytes, const int32_t length) const;

  // config detail: {'name': 'RAW_PEDAL_POS_IS_VALID', 'offset': 0.0,
  // 'precision': 1.0, 'len': 1, 'is_signed_var': False, 'physical_range':
  // '[0|1]', 'bit': 56, 'type': 'bool', 'order': 'motorola', 'physical_unit':
  // ''}
  bool raw_pedal_pos_is_valid(const std::uint8_t* bytes,
                              const int32_t length) const;

  // config detail: {'name': 'RAW_PEDAL_POS', 'offset': 0.0, 'precision': 1.0,
  // 'len': 16, 'is_signed_var': True, 'physical_range': '[-32.768|32.767]',
  // 'bit': 7, 'type': 'double', 'order': 'motorola', 'physical_unit': ''}
  double raw_pedal_pos(const std::uint8_t* bytes, const int32_t length) const;
};

}  // namespace lexus
}  // namespace canbus
}  // namespace apollo
