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

#include "modules/canbus/vehicle/ch/ch_controller.h"

#include "modules/common/proto/vehicle_signal.pb.h"

#include "cyber/common/log.h"
#include "cyber/time/time.h"
#include "modules/canbus/vehicle/ch/ch_message_manager.h"
#include "modules/canbus/vehicle/vehicle_controller.h"
#include "modules/drivers/canbus/can_comm/can_sender.h"
#include "modules/drivers/canbus/can_comm/protocol_data.h"

namespace apollo {
namespace canbus {
namespace ch {
using ::apollo::common::ErrorCode;
using ::apollo::control::ControlCommand;
using ::apollo::drivers::canbus::ProtocolData;

namespace {
const int32_t kMaxFailAttempt = 10;
const int32_t CHECK_RESPONSE_STEER_UNIT_FLAG = 1;
const int32_t CHECK_RESPONSE_SPEED_UNIT_FLAG = 2;

}  // namespace

ErrorCode ChController::Init(
    const VehicleParameter& params,
    CanSender<::apollo::canbus::ChassisDetail>* const can_sender,
    MessageManager<::apollo::canbus::ChassisDetail>* const message_manager) {
  if (is_initialized_) {
    AINFO << "ChController has already been initiated.";
    return ErrorCode::CANBUS_ERROR;
  }

  vehicle_params_.CopyFrom(
      common::VehicleConfigHelper::Instance()->GetConfig().vehicle_param());
  params_.CopyFrom(params);
  if (!params_.has_driving_mode()) {
    AERROR << "Vehicle conf pb not set driving_mode.";
    return ErrorCode::CANBUS_ERROR;
  }

  if (can_sender == nullptr) {
    AERROR << "Canbus sender is null.";
    return ErrorCode::CANBUS_ERROR;
  }
  can_sender_ = can_sender;

  if (message_manager == nullptr) {
    AERROR << "protocol manager is null.";
    return ErrorCode::CANBUS_ERROR;
  }
  message_manager_ = message_manager;

  // sender part
  brake_command_111_ = dynamic_cast<Brakecommand111*>(
      message_manager_->GetMutableProtocolDataById(Brakecommand111::ID));
  if (brake_command_111_ == nullptr) {
    AERROR << "Brakecommand111 does not exist in the ChMessageManager!";
    return ErrorCode::CANBUS_ERROR;
  }

  gear_command_114_ = dynamic_cast<Gearcommand114*>(
      message_manager_->GetMutableProtocolDataById(Gearcommand114::ID));
  if (gear_command_114_ == nullptr) {
    AERROR << "Gearcommand114 does not exist in the ChMessageManager!";
    return ErrorCode::CANBUS_ERROR;
  }

  steer_command_112_ = dynamic_cast<Steercommand112*>(
      message_manager_->GetMutableProtocolDataById(Steercommand112::ID));
  if (steer_command_112_ == nullptr) {
    AERROR << "Steercommand112 does not exist in the ChMessageManager!";
    return ErrorCode::CANBUS_ERROR;
  }

  throttle_command_110_ = dynamic_cast<Throttlecommand110*>(
      message_manager_->GetMutableProtocolDataById(Throttlecommand110::ID));
  if (throttle_command_110_ == nullptr) {
    AERROR << "Throttlecommand110 does not exist in the ChMessageManager!";
    return ErrorCode::CANBUS_ERROR;
  }

  turnsignal_command_113_ = dynamic_cast<Turnsignalcommand113*>(
      message_manager_->GetMutableProtocolDataById(Turnsignalcommand113::ID));
  if (turnsignal_command_113_ == nullptr) {
    AERROR << "Turnsignalcommand113 does not exist in the ChMessageManager!";
    return ErrorCode::CANBUS_ERROR;
  }

  can_sender_->AddMessage(Brakecommand111::ID, brake_command_111_, false);
  can_sender_->AddMessage(Gearcommand114::ID, gear_command_114_, false);
  can_sender_->AddMessage(Steercommand112::ID, steer_command_112_, false);
  can_sender_->AddMessage(Throttlecommand110::ID, throttle_command_110_, false);
  can_sender_->AddMessage(Turnsignalcommand113::ID, turnsignal_command_113_,
                          false);

  // need sleep to ensure all messages received
  AINFO << "ChController is initialized.";

  is_initialized_ = true;
  return ErrorCode::OK;
}

ChController::~ChController() {}

bool ChController::Start() {
  if (!is_initialized_) {
    AERROR << "ChController has NOT been initiated.";
    return false;
  }
  const auto& update_func = [this] { SecurityDogThreadFunc(); };
  thread_.reset(new std::thread(update_func));

  return true;
}

void ChController::Stop() {
  if (!is_initialized_) {
    AERROR << "ChController stops or starts improperly!";
    return;
  }

  if (thread_ != nullptr && thread_->joinable()) {
    thread_->join();
    thread_.reset();
    AINFO << "ChController stopped.";
  }
}

Chassis ChController::chassis() {
  chassis_.Clear();

  ChassisDetail chassis_detail;
  message_manager_->GetSensorData(&chassis_detail);

  // 21, 22, previously 1, 2
  if (driving_mode() == Chassis::EMERGENCY_MODE) {
    set_chassis_error_code(Chassis::NO_ERROR);
  }

  chassis_.set_driving_mode(driving_mode());
  chassis_.set_error_code(chassis_error_code());

  // 3
  chassis_.set_engine_started(true);
  // 4 engine rpm ch has no engine rpm
  // chassis_.set_engine_rpm(0);
  // 5 ch has no wheel spd.
  if (chassis_detail.ch().has_ecu_status_1_515() &&
      chassis_detail.ch().ecu_status_1_515().has_speed()) {
    chassis_.set_speed_mps(
        static_cast<float>(chassis_detail.ch().ecu_status_1_515().speed()));
  } else {
    chassis_.set_speed_mps(0);
  }

  // 6 ch has no odometer
  // chassis_.set_odometer_m(0);
  // 7 ch has no fuel. do not set;
  // chassis_.set_fuel_range_m(0);
  // 8 throttle
  if (chassis_detail.ch().has_throttle_status__510() &&
      chassis_detail.ch().throttle_status__510().has_throttle_pedal_sts()) {
    chassis_.set_throttle_percentage(static_cast<float>(
        chassis_detail.ch().throttle_status__510().throttle_pedal_sts()));
  } else {
    chassis_.set_throttle_percentage(0);
  }
  // 9 brake
  if (chassis_detail.ch().has_brake_status__511() &&
      chassis_detail.ch().brake_status__511().has_brake_pedal_sts()) {
    chassis_.set_brake_percentage(static_cast<float>(
        chassis_detail.ch().brake_status__511().brake_pedal_sts()));
  } else {
    chassis_.set_brake_percentage(0);
  }

  // 23, previously 10   gear
  if (chassis_detail.ch().has_gear_status_514() &&
      chassis_detail.ch().gear_status_514().has_gear_sts()) {
    Chassis::GearPosition gear_pos = Chassis::GEAR_INVALID;

    if (chassis_detail.ch().gear_status_514().gear_sts() ==
        Gear_status_514::GEAR_STS_NEUTRAL) {
      gear_pos = Chassis::GEAR_NEUTRAL;
    }
    if (chassis_detail.ch().gear_status_514().gear_sts() ==
        Gear_status_514::GEAR_STS_REVERSE) {
      gear_pos = Chassis::GEAR_REVERSE;
    }
    if (chassis_detail.ch().gear_status_514().gear_sts() ==
        Gear_status_514::GEAR_STS_DRIVE) {
      gear_pos = Chassis::GEAR_DRIVE;
    }
    if (chassis_detail.ch().gear_status_514().gear_sts() ==
        Gear_status_514::GEAR_STS_PARK) {
      gear_pos = Chassis::GEAR_PARKING;
    }

    chassis_.set_gear_location(gear_pos);
  } else {
    chassis_.set_gear_location(Chassis::GEAR_NONE);
  }
  // 11 steering
  if (chassis_detail.ch().has_steer_status__512() &&
      chassis_detail.ch().steer_status__512().has_steer_angle_sts()) {
    chassis_.set_steering_percentage(static_cast<float>(
        chassis_detail.ch().steer_status__512().steer_angle_sts() * 100.0 /
        vehicle_params_.max_steer_angle()));
  } else {
    chassis_.set_steering_percentage(0);
  }

  // 26
  if (chassis_error_mask_) {
    chassis_.set_chassis_error_mask(chassis_error_mask_);
  }

  if (chassis_detail.has_surround()) {
    chassis_.mutable_surround()->CopyFrom(chassis_detail.surround());
  }

  // give engage_advice based on error_code and canbus feedback
  if (!chassis_error_mask_ && (chassis_.throttle_percentage() == 0.0)) {
    chassis_.mutable_engage_advice()->set_advice(
        apollo::common::EngageAdvice::READY_TO_ENGAGE);
  } else {
    chassis_.mutable_engage_advice()->set_advice(
        apollo::common::EngageAdvice::DISALLOW_ENGAGE);
    chassis_.mutable_engage_advice()->set_reason(
        "CANBUS not ready, throttle percentage is not zero!");
  }

  // 27 battery soc
  if (chassis_detail.ch().has_ecu_status_2_516() &&
      chassis_detail.ch().ecu_status_2_516().has_battery_soc()) {
    chassis_.set_battery_soc_percentage(
        chassis_detail.ch().ecu_status_2_516().battery_soc());
  }

  return chassis_;
}

void ChController::Emergency() {
  set_driving_mode(Chassis::EMERGENCY_MODE);
  ResetProtocol();
}

ErrorCode ChController::EnableAutoMode() {
  if (driving_mode() == Chassis::COMPLETE_AUTO_DRIVE) {
    AINFO << "already in COMPLETE_AUTO_DRIVE mode";
    return ErrorCode::OK;
  }

  brake_command_111_->set_brake_pedal_en_ctrl(
      Brake_command_111::BRAKE_PEDAL_EN_CTRL_ENABLE);
  throttle_command_110_->set_throttle_pedal_en_ctrl(
      Throttle_command_110::THROTTLE_PEDAL_EN_CTRL_ENABLE);
  steer_command_112_->set_steer_angle_en_ctrl(
      Steer_command_112::STEER_ANGLE_EN_CTRL_ENABLE);
  AINFO << "\n\n\n set enable \n\n\n";
  can_sender_->Update();
  const int32_t flag =
      CHECK_RESPONSE_STEER_UNIT_FLAG | CHECK_RESPONSE_SPEED_UNIT_FLAG;
  if (!CheckResponse(flag, true)) {
    AERROR << "Failed to switch to COMPLETE_AUTO_DRIVE mode.";
    Emergency();
    set_chassis_error_code(Chassis::CHASSIS_ERROR);
    return ErrorCode::CANBUS_ERROR;
  } else {
    set_driving_mode(Chassis::COMPLETE_AUTO_DRIVE);
    AINFO << "Switch to COMPLETE_AUTO_DRIVE mode ok.";
    return ErrorCode::OK;
  }
}

ErrorCode ChController::DisableAutoMode() {
  ResetProtocol();
  can_sender_->Update();
  set_driving_mode(Chassis::COMPLETE_MANUAL);
  set_chassis_error_code(Chassis::NO_ERROR);
  AINFO << "Switch to COMPLETE_MANUAL OK!";
  return ErrorCode::OK;
}

ErrorCode ChController::EnableSteeringOnlyMode() {
  AFATAL << "SteeringOnlyMode Not supported!";
  return ErrorCode::OK;
}

ErrorCode ChController::EnableSpeedOnlyMode() {
  AFATAL << "SpeedOnlyMode Not supported!";
  return ErrorCode::OK;
}

// NEUTRAL, REVERSE, DRIVE
void ChController::Gear(Chassis::GearPosition gear_position) {
  if (!(driving_mode() == Chassis::COMPLETE_AUTO_DRIVE ||
        driving_mode() == Chassis::AUTO_SPEED_ONLY)) {
    AINFO << "this drive mode no need to set gear.";
    return;
  }

  // ADD YOUR OWN CAR CHASSIS OPERATION
  switch (gear_position) {
    case Chassis::GEAR_NEUTRAL: {
      gear_command_114_->set_gear_cmd(Gear_command_114::GEAR_CMD_NEUTRAL);
      break;
    }
    case Chassis::GEAR_REVERSE: {
      gear_command_114_->set_gear_cmd(Gear_command_114::GEAR_CMD_REVERSE);
      break;
    }
    case Chassis::GEAR_DRIVE: {
      gear_command_114_->set_gear_cmd(Gear_command_114::GEAR_CMD_DRIVE);
      break;
    }
    case Chassis::GEAR_PARKING: {
      gear_command_114_->set_gear_cmd(Gear_command_114::GEAR_CMD_PARK);
      break;
    }
    case Chassis::GEAR_INVALID: {
      AERROR << "Gear command is invalid!";
      gear_command_114_->set_gear_cmd(Gear_command_114::GEAR_CMD_NEUTRAL);
      break;
    }
    default: {
      gear_command_114_->set_gear_cmd(Gear_command_114::GEAR_CMD_NEUTRAL);
      break;
    }
  }
}

// brake with new acceleration
// acceleration:0.00~99.99, unit:
// acceleration:0.0 ~ 7.0, unit:m/s^2
// acceleration_spd:60 ~ 100, suggest: 90
void ChController::Brake(double pedal) {
  // Update brake value based on mode
  if (!(driving_mode() == Chassis::COMPLETE_AUTO_DRIVE ||
        driving_mode() == Chassis::AUTO_SPEED_ONLY)) {
    AINFO << "The current drive mode does not need to set acceleration.";
    return;
  }
  // ADD YOUR OWN CAR CHASSIS OPERATION
  brake_command_111_->set_brake_pedal_cmd(static_cast<int>(pedal));
}

// drive with old acceleration
// gas:0.00~99.99 unit:
void ChController::Throttle(double pedal) {
  if (driving_mode() != Chassis::COMPLETE_AUTO_DRIVE &&
      driving_mode() != Chassis::AUTO_SPEED_ONLY) {
    AINFO << "The current drive mode does not need to set acceleration.";
    return;
  }
  // ADD YOUR OWN CAR CHASSIS OPERATION
  throttle_command_110_->set_throttle_pedal_cmd(static_cast<int>(pedal));
}

void ChController::Acceleration(double acc) {}

// ch default, -23 ~ 23, left:+, right:-
// need to be compatible with control module, so reverse
// steering with old angle speed
// angle:-99.99~0.00~99.99, unit:, left:-, right:+
void ChController::Steer(double angle) {
  if (!(driving_mode() == Chassis::COMPLETE_AUTO_DRIVE ||
        driving_mode() == Chassis::AUTO_STEER_ONLY)) {
    AINFO << "The current driving mode does not need to set steer.";
    return;
  }
  const double real_angle = vehicle_params_.max_steer_angle() * angle / 100.0;
  // reverse sign
  // ADD YOUR OWN CAR CHASSIS OPERATION
  steer_command_112_->set_steer_angle_cmd(real_angle);
}

// steering with new angle speed
// angle:-99.99~0.00~99.99, unit:, left:-, right:+
// angle_spd:0.00~99.99, unit:deg/s
void ChController::Steer(double angle, double angle_spd) {
  if (!(driving_mode() == Chassis::COMPLETE_AUTO_DRIVE ||
        driving_mode() == Chassis::AUTO_STEER_ONLY)) {
    AINFO << "The current driving mode does not need to set steer.";
    return;
  }
  // ADD YOUR OWN CAR CHASSIS OPERATION
  const double real_angle = vehicle_params_.max_steer_angle() * angle / 100.0;
  steer_command_112_->set_steer_angle_cmd(real_angle);
}

void ChController::SetEpbBreak(const ControlCommand& command) {}

void ChController::SetBeam(const ControlCommand& command) {}

void ChController::SetHorn(const ControlCommand& command) {}

void ChController::SetTurningSignal(const ControlCommand& command) {}

void ChController::ResetProtocol() { message_manager_->ResetSendMessages(); }

bool ChController::CheckChassisError() {
  ChassisDetail chassis_detail;
  message_manager_->GetSensorData(&chassis_detail);
  if (!chassis_detail.has_ch()) {
    AERROR_EVERY(100) << "ChassisDetail has NO ch vehicle info."
                      << chassis_detail.DebugString();
    return false;
  }
  Ch ch = chassis_detail.ch();
  // steer motor fault
  if (ch.has_steer_status__512()) {
    if (Steer_status__512::STEER_ERR_STEER_MOTOR_ERR ==
        ch.steer_status__512().steer_err()) {
      return true;
    }
    if (Steer_status__512::SENSOR_ERR_STEER_SENSOR_ERR ==
        ch.steer_status__512().sensor_err()) {
      return true;
    }
  }
  // drive error
  if (ch.has_throttle_status__510()) {
    if (Throttle_status__510::DRIVE_MOTOR_ERR_DRV_MOTOR_ERR ==
        ch.throttle_status__510().drive_motor_err()) {
      return true;
    }
    if (Throttle_status__510::BATTERY_BMS_ERR_BATTERY_ERR ==
        ch.throttle_status__510().battery_bms_err()) {
      return true;
    }
  }
  // brake error
  if (ch.has_brake_status__511()) {
    if (Brake_status__511::BRAKE_ERR_BRAKE_SYSTEM_ERR ==
        ch.brake_status__511().brake_err()) {
      return true;
    }
  }
  return false;
}

void ChController::SecurityDogThreadFunc() {
  int32_t vertical_ctrl_fail = 0;
  int32_t horizontal_ctrl_fail = 0;

  if (can_sender_ == nullptr) {
    AERROR << "Fail to run SecurityDogThreadFunc() because can_sender_ is "
              "nullptr.";
    return;
  }
  while (!can_sender_->IsRunning()) {
    std::this_thread::yield();
  }

  std::chrono::duration<double, std::micro> default_period{50000};
  int64_t start = 0;
  int64_t end = 0;
  while (can_sender_->IsRunning()) {
    start = ::apollo::cyber::Time::Now().ToMicrosecond();
    const Chassis::DrivingMode mode = driving_mode();
    bool emergency_mode = false;

    // 1. horizontal control check
    if ((mode == Chassis::COMPLETE_AUTO_DRIVE ||
         mode == Chassis::AUTO_STEER_ONLY) &&
        CheckResponse(CHECK_RESPONSE_STEER_UNIT_FLAG, false) == false) {
      ++horizontal_ctrl_fail;
      if (horizontal_ctrl_fail >= kMaxFailAttempt) {
        emergency_mode = true;
        set_chassis_error_code(Chassis::MANUAL_INTERVENTION);
      }
    } else {
      horizontal_ctrl_fail = 0;
    }

    // 2. vertical control check
    if ((mode == Chassis::COMPLETE_AUTO_DRIVE ||
         mode == Chassis::AUTO_SPEED_ONLY) &&
        CheckResponse(CHECK_RESPONSE_SPEED_UNIT_FLAG, false) == false) {
      ++vertical_ctrl_fail;
      if (vertical_ctrl_fail >= kMaxFailAttempt) {
        emergency_mode = true;
        set_chassis_error_code(Chassis::MANUAL_INTERVENTION);
      }
    } else {
      vertical_ctrl_fail = 0;
    }
    if (CheckChassisError()) {
      set_chassis_error_code(Chassis::CHASSIS_ERROR);
      emergency_mode = true;
    }

    if (emergency_mode && mode != Chassis::EMERGENCY_MODE) {
      set_driving_mode(Chassis::EMERGENCY_MODE);
      message_manager_->ResetSendMessages();
    }
    end = ::apollo::cyber::Time::Now().ToMicrosecond();
    std::chrono::duration<double, std::micro> elapsed{end - start};
    if (elapsed < default_period) {
      std::this_thread::sleep_for(default_period - elapsed);
    } else {
      AERROR << "Too much time consumption in ChController looping process:"
             << elapsed.count();
    }
  }
}
bool ChController::CheckResponse(const int32_t flags, bool need_wait) {
  int32_t retry_num = 20;
  ChassisDetail chassis_detail;
  bool is_eps_online = false;
  bool is_vcu_online = false;
  bool is_esp_online = false;

  do {
    if (message_manager_->GetSensorData(&chassis_detail) != ErrorCode::OK) {
      AERROR_EVERY(100) << "get chassis detail failed.";
      return false;
    }
    bool check_ok = true;
    if (flags & CHECK_RESPONSE_STEER_UNIT_FLAG) {
      is_eps_online = chassis_detail.has_check_response() &&
                      chassis_detail.check_response().has_is_eps_online() &&
                      chassis_detail.check_response().is_eps_online();
      check_ok = check_ok && is_eps_online;
    }

    if (flags & CHECK_RESPONSE_SPEED_UNIT_FLAG) {
      is_vcu_online = chassis_detail.has_check_response() &&
                      chassis_detail.check_response().has_is_vcu_online() &&
                      chassis_detail.check_response().is_vcu_online();
      is_esp_online = chassis_detail.has_check_response() &&
                      chassis_detail.check_response().has_is_esp_online() &&
                      chassis_detail.check_response().is_esp_online();
      check_ok = check_ok && is_vcu_online && is_esp_online;
    }
    if (check_ok) {
      return true;
    } else {
      AINFO << "Need to check response again.";
    }
    if (need_wait) {
      --retry_num;
      std::this_thread::sleep_for(
          std::chrono::duration<double, std::milli>(20));
    }
  } while (need_wait && retry_num);

  AINFO << "check_response fail: is_eps_online:" << is_eps_online
        << ", is_vcu_online:" << is_vcu_online
        << ", is_esp_online:" << is_esp_online;

  return false;
}

void ChController::set_chassis_error_mask(const int32_t mask) {
  std::lock_guard<std::mutex> lock(chassis_mask_mutex_);
  chassis_error_mask_ = mask;
}

int32_t ChController::chassis_error_mask() {
  std::lock_guard<std::mutex> lock(chassis_mask_mutex_);
  return chassis_error_mask_;
}

Chassis::ErrorCode ChController::chassis_error_code() {
  std::lock_guard<std::mutex> lock(chassis_error_code_mutex_);
  return chassis_error_code_;
}

void ChController::set_chassis_error_code(
    const Chassis::ErrorCode& error_code) {
  std::lock_guard<std::mutex> lock(chassis_error_code_mutex_);
  chassis_error_code_ = error_code;
}

}  // namespace ch
}  // namespace canbus
}  // namespace apollo
