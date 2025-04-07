// insulinmanager.cpp
#include "insulinmanager.h"
#include "def.h"

InsulinManager::InsulinManager(DataStorage* storage) : storage(storage), isInsulinActive(true) {}

void InsulinManager::checkGlucose(double glucose) {
    if(glucose < BG_CRITICAL_LOW && isInsulinActive) {
        stopInsulin();
    }
}

void InsulinManager::stopInsulin() {
    isInsulinActive = false;
    storage->logEvent("DosageStopped", "Insulin delivery stopped due to low glucose level");
}