#include "SimulationController.h"
#include "UserProfile.h"
#include <iostream>

SimulationController::SimulationController() {
    profileManager = new ProfileManager();
    bolusCalculator = new BolusCalculator();
    cgmDataHandler = new CGMDataHandler();
    deliveryManager = new InsulinDeliveryManager();
    errorManager = new ErrorManager();
    dataLogger = new DataLogger();
    pump = new InsulinPump(profileManager, bolusCalculator, cgmDataHandler, deliveryManager, errorManager, dataLogger);
    
    UserProfile defaultProfile("Default", 1.0f, 1.0f, 1.0f, 5.0f);
    profileManager->createProfile(defaultProfile);
    pump->setCurrentProfile(defaultProfile);
    
    simulationTime = 0; 
}

void SimulationController::advanceTime() {
    simulationTime++;
    std::cout << "\n--- Advancing Time: Hour " << simulationTime << " ---" << std::endl;
    
    pump->advanceTimeStep();
    
    bool basalActive = deliveryManager->isDelivering();
    
    cgmDataHandler->updateDiabeticGlucose(basalActive);
    float currentBG = cgmDataHandler->getCurrentGlucose();
    std::cout << "Updated Blood Glucose Reading: " << currentBG << " mmol/L" << std::endl;
    
    float predictedBG = cgmDataHandler->predictGlucose(basalActive);
    std::cout << "Predicted Blood Glucose (30 min): " << predictedBG << " mmol/L" << std::endl;
    
    float defaultBasalRate = 1.0f;
    if (predictedBG < 6.25f) {
        deliveryManager->setDynamicBasalRate(defaultBasalRate * 0.5f);
        dataLogger->logEvent("Basal rate decreased (predicted BG ≤ 6.25 mmol/L).");
    } else if (predictedBG > 8.9f && predictedBG < 10.0f) {
        deliveryManager->setDynamicBasalRate(defaultBasalRate * 1.2f);
        dataLogger->logEvent("Basal rate increased (predicted BG > 8.9 mmol/L).");
    } else {
        deliveryManager->setDynamicBasalRate(defaultBasalRate);
        dataLogger->logEvent("Basal delivery at profile rate (predicted BG within target range).");
    }
    
    if (predictedBG < 3.89f) {
        pump->stopInsulinDelivery();
        dataLogger->logEvent("Basal delivery stopped (predicted BG below 3.89 mmol/L).");
    }
    
    if (predictedBG >= 10.0f) {
        std::cout << "Automatic correction bolus triggered (predicted BG ≥ 10.0 mmol/L)." << std::endl;
        pump->manualBolusDelivery(0.0f, predictedBG, 0.0f);
        dataLogger->logEvent("Automatic correction bolus delivered for predicted BG (" + std::to_string(predictedBG) + " mmol/L).");
        pump->applyBolusEffect(0.1f);
    }
}

void SimulationController::simulateUserInteraction() {
    int choice;
    do {
        std::cout << "\n=== Insulin Pump Simulation Menu ===" << std::endl;
        std::cout << "1. Power On Pump" << std::endl;
        std::cout << "2. Power Off Pump" << std::endl;
        std::cout << "3. Start Basal Insulin Delivery" << std::endl;
        std::cout << "4. Stop Basal Insulin Delivery" << std::endl;
        std::cout << "5. Resume Basal Insulin Delivery" << std::endl;
        std::cout << "6. Update Battery Status" << std::endl;
        std::cout << "7. Manual Bolus Delivery" << std::endl;
        std::cout << "8. Display Pump Metrics" << std::endl;
        std::cout << "9. Check Current Blood Glucose" << std::endl;
        std::cout << "10. Advance Time" << std::endl;
        std::cout << "11. Exit Simulation" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                pump->powerOn();
                break;
            case 2:
                pump->powerOff();
                break;
            case 3:
                pump->startInsulinDelivery();
                break;
            case 4:
                pump->stopInsulinDelivery();
                break;
            case 5:
                pump->resumeInsulinDelivery();
                break;
            case 6:
                pump->updateBatteryStatus();
                break;
            case 7: {
                float carbs, currentBG, IOB;
                std::cout << "Enter carbohydrate intake (g): ";
                std::cin >> carbs;
                std::cout << "Enter current blood glucose level (mmol/L): ";
                std::cin >> currentBG;
                std::cout << "Enter Insulin On Board (units): ";
                std::cin >> IOB;
                pump->manualBolusDelivery(carbs, currentBG, IOB);
                break;
            }
            case 8:
                displayMetrics();
                break;
            case 9: {
                float bg = cgmDataHandler->getCurrentGlucose();
                std::cout << "Current Blood Glucose: " << bg << " mmol/L" << std::endl;
                break;
            }
            case 10:
                advanceTime();
                break;
            case 11:
                std::cout << "Exiting simulation." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 11);
}

void SimulationController::displayMetrics() {
    std::cout << "\n--- Pump Metrics ---" << std::endl;
    std::cout << "Battery Level: " << pump->getBatteryLevel() << "%" << std::endl;
    std::cout << "Insulin Cartridge Level: " << pump->getInsulinCartridgeLevel() << " units" << std::endl;
    std::cout << "Pump Power Status: " << (pump->isPoweredOn() ? "ON" : "OFF") << std::endl;
    std::cout << "\n--- Logged Events ---" << std::endl;
    for (const auto& event : dataLogger->getHistory()) {
        std::cout << event << std::endl;
    }
}

void SimulationController::runSimulation() {
    simulateUserInteraction();
}