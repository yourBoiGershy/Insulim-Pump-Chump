#ifndef DATALOGGER_H
#define DATALOGGER_H

#include <string>
#include <vector>

class DataLogger {
public:
    void logEvent(const std::string& event);
    std::vector<std::string> getHistory() const;
private:
    std::vector<std::string> eventHistory;
};

#endif 