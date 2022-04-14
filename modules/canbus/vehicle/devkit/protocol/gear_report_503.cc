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

#include "modules/canbus/vehicle/devkit/protocol/gear_report_503.h"

#include "glog/logging.h"
#include "modules/drivers/canbus/common/byte.h"
#include "modules/drivers/canbus/common/canbus_consts.h"

namespace apollo {
namespace canbus {
namespace devkit {

using ::apollo::drivers::canbus::Byte;

Gearreport503::Gearreport503() {}
const int32_t Gearreport503::ID = 0x503;

void Gearreport503::Parse(const std::uint8_t* bytes, int32_t length,
                          ChassisDetail* chassis) const {
  chassis->mutable_devkit()->mutable_gear_report_503()->set_gear_flt(
      gear_flt(bytes, length));
  chassis->mutable_devkit()->mutable_gear_report_503()->set_gear_actual(
      gear_actual(bytes, length));
}

// config detail: {'name': 'gear_flt', 'enum': {0: 'GEAR_FLT_NO_FAULT', 1:
// 'GEAR_FLT_FAULT'}, 'precision': 1.0, 'len': 8, 'is_signed_var': False,
// 'offset': 0.0, 'physical_range': '[0|1]', 'bit': 15, 'type': 'enum', 'order':
// 'motorola', 'physical_unit': ''}
Gear_report_503::Gear_fltType Gearreport503::gear_flt(const std::uint8_t* bytes,
                                                      int32_t length) const {
  Byte t0(bytes + 1);
  int32_t x = t0.get_byte(0, 8);

  Gear_report_503::Gear_fltType ret =
      static_cast<Gear_report_503::Gear_fltType>(x);
  return ret;
}

// config detail: {'name': 'gear_actual', 'enum': {0: 'GEAR_ACTUAL_INVALID', 1:
// 'GEAR_ACTUAL_PARK', 2: 'GEAR_ACTUAL_REVERSE', 3: 'GEAR_ACTUAL_NEUTRAL', 4:
// 'GEAR_ACTUAL_DRIVE'}, 'precision': 1.0, 'len': 3, 'is_signed_var': False,
// 'offset': 0.0, 'physical_range': '[0|4]', 'bit': 2, 'type': 'enum', 'order':
// 'motorola', 'physical_unit': ''}
Gear_report_503::Gear_actualType Gearreport503::gear_actual(
    const std::uint8_t* bytes, int32_t length) const {
  Byte t0(bytes + 0);
  int32_t x = t0.get_byte(0, 3);

  Gear_report_503::Gear_actualType ret =
      static_cast<Gear_report_503::Gear_actualType>(x);
  return ret;
}
}  // namespace devkit
}  // namespace canbus
}  // namespace apollo
