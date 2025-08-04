#include <gtest/gtest.h>
#include "./monitor.h"

TEST(Monitor, NotOkWhenAnyVitalIsOffRange) {
    ASSERT_FALSE(vitalsOk(99, 102, 70));
    ASSERT_TRUE(vitalsOk(98.1, 70, 98));
}

TEST(Monitor, TemperatureCheck) {
    ASSERT_TRUE(isTemperatureOk(95.0f));
    ASSERT_TRUE(isTemperatureOk(102.0f));
    ASSERT_FALSE(isTemperatureOk(94.9f));
    ASSERT_FALSE(isTemperatureOk(102.1f));
}

TEST(Monitor, PulseRateCheck) {
    ASSERT_TRUE(isPulseRateOk(60.0f));
    ASSERT_TRUE(isPulseRateOk(100.0f));
    ASSERT_FALSE(isPulseRateOk(59.9f));
    ASSERT_FALSE(isPulseRateOk(100.1f));
}

TEST(Monitor, SpO2Check) {
    ASSERT_TRUE(isSpO2Ok(90.0f));
    ASSERT_TRUE(isSpO2Ok(99.0f));
    ASSERT_FALSE(isSpO2Ok(89.9f));
}
