// insulinmanager.h
#ifndef INSULINMANAGER_H
#define INSULINMANAGER_H

#include "datastorage.h"

class InsulinManager {
public:
    InsulinManager(DataStorage* storage);
    void checkGlucose(double glucose);

private:
    DataStorage* storage;
    bool isInsulinActive;

    void stopInsulin();
};

#endif