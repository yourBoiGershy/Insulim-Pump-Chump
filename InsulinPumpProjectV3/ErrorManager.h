#ifndef ERRORMANAGER_H
#define ERRORMANAGER_H

#include <string>
#include <vector>

class ErrorManager {
public:
    void logError(const std::string& errorMsg);
    void handleLowBattery();
    void handleLowInsulin();
    void handleCGMDisconnection();
    void resetErrors();
    const std::vector<std::string>& getErrorLog() const;
private:
    std::vector<std::string> errorLog;
};

#endif 