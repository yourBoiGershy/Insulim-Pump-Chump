// errordetector.h
#ifndef ERRORDETECTOR_H
#define ERRORDETECTOR_H

#include "datastorage.h"

class ErrorDetector {
public:
    ErrorDetector(DataStorage* storage);
    void checkBattery(int battery);
    void checkInsulin(int insulinLevel);
    void checkCGMConnection(bool connected);
    void checkGlucose(double glucose);

private:
    DataStorage* storage;
};

#endif