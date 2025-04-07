#ifndef SIMULATIONCONTROLLER_H
#define SIMULATIONCONTROLLER_H

#include "InsulinPump.h"
#include "ProfileManager.h"
#include "BolusCalculator.h"
#include "CGMDataHandler.h"
#include "InsulinDeliveryManager.h"
#include "ErrorManager.h"
#include "DataLogger.h"

class SimulationController {
public:
    SimulationController();
    void runSimulation();
private:
    InsulinPump* pump;
    ProfileManager* profileManager;
    BolusCalculator* bolusCalculator;
    CGMDataHandler* cgmDataHandler;
    InsulinDeliveryManager* deliveryManager;
    ErrorManager* errorManager;
    DataLogger* dataLogger;
    void simulateUserInteraction();
    void displayMetrics();
    int simulationTime; 
    void advanceTime(); 
};

#endif 