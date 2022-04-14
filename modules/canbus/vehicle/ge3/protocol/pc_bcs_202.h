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
namespace ge3 {

class Pcbcs202 : public ::apollo::drivers::canbus::ProtocolData<
                     ::apollo::canbus::ChassisDetail> {
 public:
  static const int32_t ID;

  Pcbcs202();

  uint32_t GetPeriod() const override;

  void UpdateData(uint8_t* data) override;

  void Reset() override;

  // config detail: {'description': 'Brake pedal request', 'offset': 0.0,
  // 'precision': 0.1, 'len': 10, 'name': 'PC_BrkPedReq', 'is_signed_var':
  // False, 'physical_range': '[0|100]', 'bit': 1, 'type': 'double', 'order':
  // 'motorola', 'physical_unit': '%'}
  Pcbcs202* set_pc_brkpedreq(double pc_brkpedreq);

  // config detail: {'description': 'Brake pedal control enable', 'enum': {0:
  // 'PC_BRKPEDENABLE_DISABLE', 1: 'PC_BRKPEDENABLE_ENABLE'}, 'precision': 1.0,
  // 'len': 1, 'name': 'PC_BrkPedEnable', 'is_signed_var': False, 'offset': 0.0,
  // 'physical_range': '[0|1]', 'bit': 7, 'type': 'enum', 'order': 'motorola',
  // 'physical_unit': ''}
  Pcbcs202* set_pc_brkpedenable(
      Pc_bcs_202::Pc_brkpedenableType pc_brkpedenable);

 private:
  // config detail: {'description': 'Brake pedal request', 'offset': 0.0,
  // 'precision': 0.1, 'len': 10, 'name': 'PC_BrkPedReq', 'is_signed_var':
  // False, 'physical_range': '[0|100]', 'bit': 1, 'type': 'double', 'order':
  // 'motorola', 'physical_unit': '%'}
  void set_p_pc_brkpedreq(uint8_t* data, double pc_brkpedreq);

  // config detail: {'description': 'Brake pedal control enable', 'enum': {0:
  // 'PC_BRKPEDENABLE_DISABLE', 1: 'PC_BRKPEDENABLE_ENABLE'}, 'precision': 1.0,
  // 'len': 1, 'name': 'PC_BrkPedEnable', 'is_signed_var': False, 'offset': 0.0,
  // 'physical_range': '[0|1]', 'bit': 7, 'type': 'enum', 'order': 'motorola',
  // 'physical_unit': ''}
  void set_p_pc_brkpedenable(uint8_t* data,
                             Pc_bcs_202::Pc_brkpedenableType pc_brkpedenable);

 private:
  double pc_brkpedreq_;
  Pc_bcs_202::Pc_brkpedenableType pc_brkpedenable_;
};

}  // namespace ge3
}  // namespace canbus
}  // namespace apollo
