#include "DataLogger.h"
#include <iostream>

void DataLogger::logEvent(const std::string& event) {
    eventHistory.push_back(event);
    std::cout << "Event logged: " << event << std::endl;
}

std::vector<std::string> DataLogger::getHistory() const {
    return eventHistory;
}