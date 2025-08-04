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

bool isTemperatureOk(float temperature) {
    return temperature >= TEMPERATURE_MIN && temperature <= TEMPERATURE_MAX;
}

bool isPulseRateOk(float pulseRate) {
    return pulseRate >= PULSE_MIN && pulseRate <= PULSE_MAX;
}

bool isSpO2Ok(float spo2) {
    return spo2 >= SPO2_MIN;
}

void showCriticalAlert(const char* message) {
    cout << message << "\n";
    for (int i = 0; i < ALERT_BLINKS; ++i) {
        cout << "\r* " << flush;
        sleep_for(seconds(1));
        cout << "\r *" << flush;
        sleep_for(seconds(1));
    }
}

struct VitalCheck {
    bool (*checker)(float);
    float value;
    const char* message;
};

int vitalsOk(float temperature, float pulseRate, float spo2) {
    const VitalCheck checks[] = {
        {isTemperatureOk, temperature, "Temperature is critical!"},
        {isPulseRateOk,   pulseRate,   "Pulse Rate is out of range!"},
        {isSpO2Ok,        spo2,        "Oxygen Saturation out of range!"}
    };

    for (int i = 0; i < 3; ++i) {
        if (!checks[i].checker(checks[i].value)) {
            showCriticalAlert(checks[i].message);
            return 0;
        }
    }
    return 1;
}
