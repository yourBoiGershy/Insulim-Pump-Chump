#include "ErrorManager.h"
#include <iostream>

void ErrorManager::logError(const std::string& errorMsg) {
    errorLog.push_back(errorMsg);
    std::cout << "Error: " << errorMsg << std::endl;
}

void ErrorManager::handleLowBattery() {
    logError("Low Battery detected. Please recharge the pump.");
}

void ErrorManager::handleLowInsulin() {
    logError("Low Insulin detected. Please refill the insulin cartridge.");
}

void ErrorManager::handleCGMDisconnection() {
    logError("CGM Disconnected. Check the sensor connection.");
}

void ErrorManager::resetErrors() {
    errorLog.clear();
}

const std::vector<std::string>& ErrorManager::getErrorLog() const {
    return errorLog;
}