#include "./monitor.h"
#include <iostream>
#include <thread>
#include <chrono>

using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

struct VitalRange {
    float min;
    float max;
    bool has_max;
};

constexpr VitalRange TEMPERATURE_RANGE{95.0f, 102.0f, true};
constexpr VitalRange PULSE_RANGE{60.0f, 100.0f, true};
constexpr VitalRange SPO2_RANGE{90.0f, 0.0f, false};
constexpr int ALERT_BLINKS = 6;

bool isTemperatureOk(float temperature) {
    return temperature >= TEMPERATURE_RANGE.min && temperature <= TEMPERATURE_RANGE.max;
}
bool isPulseRateOk(float pulseRate) {
    return pulseRate >= PULSE_RANGE.min && pulseRate <= PULSE_RANGE.max;
}
bool isSpO2Ok(float spo2) {
    return spo2 >= SPO2_RANGE.min;
}

void showCriticalAlert(const char* message) {
    cout << message << "\n";
    for(int i = 0; i < ALERT_BLINKS; ++i) {
        cout << "\r* " << flush;
        sleep_for(seconds(1));
        cout << "\r *" << flush;
        sleep_for(seconds(1));
    }
}

int vitalsOk(float temperature, float pulseRate, float spo2) {
    if (!isTemperatureOk(temperature)) {
        showCriticalAlert("Temperature is critical!");
        return 0;
    }
    if (!isPulseRateOk(pulseRate)) {
        showCriticalAlert("Pulse Rate is out of range!");
        return 0;
    }
    if (!isSpO2Ok(spo2)) {
        showCriticalAlert("Oxygen Saturation out of range!");
        return 0;
    }
    return 1;
}
