// errordetector.cpp
#include "errordetector.h"
#include "def.h"

ErrorDetector::ErrorDetector(DataStorage* storage) : storage(storage) {}

void ErrorDetector::checkBattery(int battery) {
    if(battery <= BATTERY_LOW_THRESHOLD) {
        storage->logEvent("BatteryLow", "Battery critically low");
    }
}

void ErrorDetector::checkInsulin(int insulinLevel) {
    if(insulinLevel <= INSULIN_LOW_THRESHOLD) {
        storage->logEvent("InsulinLow", "Insulin level critically low");
    }
}

void ErrorDetector::checkCGMConnection(bool connected) {
    if(!connected) {
        storage->logEvent("CGMDisconnected", "CGM sensor disconnected");
    }
}

void ErrorDetector::checkGlucose(double glucose) {
    if(glucose <= BG_CRITICAL_LOW) {
        storage->logEvent("GlucoseLow", "Glucose critically low");
    } else if(glucose >= BG_CRITICAL_HIGH) {
        storage->logEvent("GlucoseHigh", "Glucose critically high");
    }
}