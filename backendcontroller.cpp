// backendcontroller.cpp
#include "backendcontroller.h"

BackendController::BackendController() {
    dataStorage = new DataStorage();
    insulinManager = new InsulinManager(dataStorage);
    errorDetector = new ErrorDetector(dataStorage);
}

BackendController::~BackendController() {
    delete insulinManager;
    delete errorDetector;
    delete dataStorage;
}

void BackendController::initialize() {
    dataStorage->initializeDB();
}