#include <gtest/gtest.h>
#include "./monitor.h"

extern const float TEMPERATURE_MIN;
extern const float TEMPERATURE_MAX;
extern const float PULSE_MIN;
extern const float PULSE_MAX;
extern const float SPO2_MIN;

TEST(Monitor, NotOkWhenAnyVitalIsOffRange) {
  EXPECT_FALSE(vitalsOk(99, 102, 70));
  EXPECT_TRUE(vitalsOk(98.1, 70, 98));
}

TEST(Monitor, TemperatureBoundary) {
  EXPECT_TRUE(isTemperatureOk(95.0f));
  EXPECT_TRUE(isTemperatureOk(102.0f));
  EXPECT_FALSE(isTemperatureOk(94.9f));
  EXPECT_FALSE(isTemperatureOk(102.1f));
}

TEST(Monitor, PulseBoundary) {
  EXPECT_TRUE(isPulseRateOk(60.0f));
  EXPECT_TRUE(isPulseRateOk(100.0f));
  EXPECT_FALSE(isPulseRateOk(59.9f));
  EXPECT_FALSE(isPulseRateOk(100.1f));
}

TEST(Monitor, SpO2Boundary) {
  EXPECT_TRUE(isSpO2Ok(90.0f));
  EXPECT_TRUE(isSpO2Ok(92.0f));
  EXPECT_FALSE(isSpO2Ok(89.9f));
  EXPECT_FALSE(isSpO2Ok(70.0f));
}


