#include "./monitor.h"
#include <thread>
#include <chrono>
#include <iostream>

using std::cout;
using std::flush;
using std::this_thread::sleep_for;
using std::chrono::seconds;

constexpr float TEMPERATURE_MIN = 95.0f;
constexpr float TEMPERATURE_MAX = 102.0f;
constexpr float PULSE_MIN = 60.0f;
constexpr float PULSE_MAX = 100.0f;
constexpr float SPO2_MIN = 90.0f;
constexpr int ALERT_BLINKS = 6;
constexpr float WARNING_TOLERANCE_PERCENT = 0.015f;  // 1.5%

bool isTemperatureOk(float temperature) {
    return temperature >= TEMPERATURE_MIN && temperature <= TEMPERATURE_MAX; [web:18]
}

bool isPulseRateOk(float pulseRate) {
    return pulseRate >= PULSE_MIN && pulseRate <= PULSE_MAX; [web:22]
}

bool isSpO2Ok(float spo2) {
    return spo2 >= SPO2_MIN; [web:22]
}

static void showWarning(const char* message) {
    cout << "Warning: " << message << "\n"; [web:22]
}

void showCriticalAlert(const char* message) {
    cout << message << "\n"; [web:22]
    for (int i = 0; i < ALERT_BLINKS; ++i) {
        cout << "\r* " << flush; [web:22]
        sleep_for(seconds(1)); [web:22]
        cout << "\r *" << flush; [web:22]
        sleep_for(seconds(1)); [web:22]
    }
}

// Split early warning into simple, single-branch helpers to reduce CCN.
static void checkLowSideWarning(float value, float min, float max, const char* msg) {
    const float tolerance = max * WARNING_TOLERANCE_PERCENT; [web:22]
    if (value > min && value <= (min + tolerance)) {
        showWarning(msg); [web:22]
    }
}

static void checkHighSideWarning(float value, float min, float max, const char* msg) {
    const float tolerance = max * WARNING_TOLERANCE_PERCENT; [web:22]
    if (value >= (max - tolerance) && value < max) {
        showWarning(msg); [web:22]
    }
}

// Thin wrapper to keep call sites unchanged; CCN here remains low.
static void checkEarlyWarning(float value, float min, float max,
                              const char* lowMsg, const char* highMsg) {
    checkLowSideWarning(value, min, max, lowMsg); [web:22]
    checkHighSideWarning(value, min, max, highMsg); [web:22]
}

struct VitalCheck {
    bool (*checker)(float);
    float value;
    const char* criticalMsg;
    float min;
    float max;
    const char* lowWarningMsg;
    const char* highWarningMsg;
};

int vitalsOk(float temperature, float pulseRate, float spo2) {
    const VitalCheck checks[] = {
        {isTemperatureOk, temperature, "Temperature is critical!",
         TEMPERATURE_MIN, TEMPERATURE_MAX,
         "Approaching hypothermia", "Approaching hyperthermia"},
        {isPulseRateOk,   pulseRate,   "Pulse Rate is out of range!",
         PULSE_MIN, PULSE_MAX,
         "Approaching bradycardia", "Approaching tachycardia"},
        {isSpO2Ok,        spo2,        "Oxygen Saturation out of range!",
         SPO2_MIN, 100.0f, // upper reference for tolerance only
         "Approaching hypoxemia", "Approaching upper SpO2 limit"}
    }; [web:22]

    for (int i = 0; i < 3; ++i) {
        if (!checks[i].checker(checks[i].value)) {
            showCriticalAlert(checks[i].criticalMsg); [web:22]
            return 0; [web:22]
        }
        checkEarlyWarning(checks[i].value, checks[i].min, checks[i].max,
                          checks[i].lowWarningMsg, checks[i].highWarningMsg); [web:22]
    }
    return 1; [web:22]
}
