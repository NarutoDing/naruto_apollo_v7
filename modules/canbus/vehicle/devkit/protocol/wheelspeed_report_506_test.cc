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

#include "modules/canbus/vehicle/devkit/protocol/wheelspeed_report_506.h"

#include "gtest/gtest.h"

namespace apollo {
namespace canbus {
namespace devkit {
class Wheelspeedreport506Test : public ::testing::Test {
 public:
  virtual void SetUp() {}
};

TEST_F(Wheelspeedreport506Test, General) {
  uint8_t data[8] = {0x07, 0x01, 0x01, 0x02, 0x8A, 0x03, 0x04, 0x05};
  int32_t length = 8;
  ChassisDetail cd;
  Wheelspeedreport506 wheelspeedreport;
  wheelspeedreport.Parse(data, length, &cd);

  EXPECT_EQ(data[0], 0b00000111);
  EXPECT_EQ(data[1], 0b00000001);
  EXPECT_EQ(data[2], 0b00000001);
  EXPECT_EQ(data[3], 0b00000010);
  EXPECT_EQ(data[4], 0b10001010);
  EXPECT_EQ(data[5], 0b00000011);
  EXPECT_EQ(data[6], 0b00000100);
  EXPECT_EQ(data[7], 0b00000101);

  EXPECT_EQ(cd.devkit().wheelspeed_report_506().rr(), 1.029);
  EXPECT_EQ(cd.devkit().wheelspeed_report_506().rl(), 35.331);
  EXPECT_EQ(cd.devkit().wheelspeed_report_506().fr(), 0.258);
  EXPECT_EQ(cd.devkit().wheelspeed_report_506().fl(), 1.793);
}

}  // namespace devkit
}  // namespace canbus
}  // namespace apollo
