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

#include "modules/canbus/vehicle/ge3/protocol/pc_eps_204.h"
#include "gtest/gtest.h"

namespace apollo {
namespace canbus {
namespace ge3 {

class Pceps204Test : public ::testing::Test {
 public:
  virtual void SetUp() {}
};

TEST_F(Pceps204Test, reset) {
  uint8_t data[8] = {0x67, 0x62, 0x63, 0x64, 0x51, 0x52, 0x53, 0x54};
  Pceps204 pceps204;
  EXPECT_EQ(pceps204.GetPeriod(), 20 * 1000);
  pceps204.UpdateData(data);
  EXPECT_EQ(data[0], 0b01100111);
  EXPECT_EQ(data[1], 0b00010011);
  EXPECT_EQ(data[2], 0b10001000);
  EXPECT_EQ(data[3], 0b00000000);
  EXPECT_EQ(data[4], 0b00000000);
  EXPECT_EQ(data[5], 0b01010010);
  EXPECT_EQ(data[6], 0b01010011);
  EXPECT_EQ(data[7], 0b01010100);
}

}  // namespace ge3
}  // namespace canbus
}  // namespace apollo
