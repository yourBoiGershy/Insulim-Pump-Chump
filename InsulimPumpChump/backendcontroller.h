// backendcontroller.h
#ifndef BACKENDCONTROLLER_H
#define BACKENDCONTROLLER_H

#include "datastorage.h"
#include "insulinmanager.h"
#include "errordetector.h"

class BackendController {
public:
    BackendController();
    ~BackendController();

    DataStorage* dataStorage;
    InsulinManager* insulinManager;
    ErrorDetector* errorDetector;

    void initialize();
};

#endif