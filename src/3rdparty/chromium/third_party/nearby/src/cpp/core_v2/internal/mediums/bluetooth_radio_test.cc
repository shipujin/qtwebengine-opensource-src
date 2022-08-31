// Copyright 2020 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "core_v2/internal/mediums/bluetooth_radio.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace location {
namespace nearby {
namespace connections {
namespace {

TEST(BluetoothRadioTest, ConstructorDestructorWorks) {
  BluetoothRadio radio;
  EXPECT_TRUE(radio.IsAdapterValid());
}

TEST(BluetoothRadioTest, CanEnable) {
  BluetoothRadio radio;
  EXPECT_TRUE(radio.IsAdapterValid());
  EXPECT_FALSE(radio.IsEnabled());
  EXPECT_TRUE(radio.Enable());
  EXPECT_TRUE(radio.IsEnabled());
}

TEST(BluetoothRadioTest, CanDisable) {
  BluetoothRadio radio;
  EXPECT_TRUE(radio.IsAdapterValid());
  EXPECT_FALSE(radio.IsEnabled());
  EXPECT_TRUE(radio.Enable());
  EXPECT_TRUE(radio.IsEnabled());
  EXPECT_TRUE(radio.Disable());
  EXPECT_FALSE(radio.IsEnabled());
}

TEST(BluetoothRadioTest, CanToggle) {
  BluetoothRadio radio;
  EXPECT_TRUE(radio.IsAdapterValid());
  EXPECT_FALSE(radio.IsEnabled());
  EXPECT_TRUE(radio.Toggle());
  EXPECT_TRUE(radio.IsEnabled());
}

}  // namespace
}  // namespace connections
}  // namespace nearby
}  // namespace location