#include "InsulinPump.h"
#include <iostream>

InsulinPump::InsulinPump(ProfileManager* profileMgr, BolusCalculator* bolusCalc, CGMDataHandler* cgmHandler,
                         InsulinDeliveryManager* deliveryMgr, ErrorManager* errMgr, DataLogger* logger)
    : batteryLevel(100.0f), insulinCartridge(300.0f), isPowered(false),
      currentProfile("Default", 1.0f, 1.0f, 1.0f, 5.0f),
      profileManager(profileMgr), bolusCalculator(bolusCalc), cgmDataHandler(cgmHandler),
      deliveryManager(deliveryMgr), errorManager(errMgr), dataLogger(logger)
{
}

void InsulinPump::powerOn() {
    isPowered = true;
    dataLogger->logEvent("Pump powered on.");
    std::cout << "Pump is now ON." << std::endl;
}

void InsulinPump::powerOff() {
    isPowered = false;
    dataLogger->logEvent("Pump powered off.");
    std::cout << "Pump is now OFF." << std::endl;
}

void InsulinPump::startInsulinDelivery() {
    if (!isPowered) {
        std::cout << "Pump is off. Cannot start delivery." << std::endl;
        return;
    }
    deliveryManager->startBasalDelivery();
    dataLogger->logEvent("Basal insulin delivery started.");
}

void InsulinPump::stopInsulinDelivery() {
    if (!isPowered) {
        std::cout << "Pump is off. Cannot stop delivery." << std::endl;
        return;
    }
    deliveryManager->suspendBasalDelivery();
    dataLogger->logEvent("Basal insulin delivery stopped.");
}

void InsulinPump::resumeInsulinDelivery() {
    if (!isPowered) {
        std::cout << "Pump is off. Cannot resume delivery." << std::endl;
        return;
    }
    deliveryManager->resumeBasalDelivery();
    dataLogger->logEvent("Basal insulin delivery resumed.");
}

void InsulinPump::updateBatteryStatus() {
    if (isPowered) {
        batteryLevel -= 0.5f;
        if (batteryLevel < 20.0f) {
            errorManager->handleLowBattery();
        }
        dataLogger->logEvent("Battery status updated. Current level: " + std::to_string(batteryLevel));
    }
}

void InsulinPump::setCurrentProfile(const UserProfile& profile) {
    currentProfile = profile;
    dataLogger->logEvent("Current profile set to: " + profile.profileName);
}


void InsulinPump::manualBolusDelivery(float carbs, float currentBG, float IOB) {
    float carbBolus = bolusCalculator->calculateCarbBolus(carbs, currentProfile.insulinToCarbRatio);
    float correctionBolus = bolusCalculator->calculateCorrectionBolus(currentBG, currentProfile.targetBloodGlucose, currentProfile.correctionFactor);
    float totalBolus = bolusCalculator->calculateTotalBolus(carbBolus, correctionBolus);
    float finalBolus = bolusCalculator->adjustForIOB(totalBolus, IOB);
    float immediateBolus = bolusCalculator->calculateImmediateBolus(finalBolus);
    float extendedBolus = bolusCalculator->calculateExtendedBolus(finalBolus);
    
    if (insulinCartridge >= finalBolus)
        insulinCartridge -= finalBolus;
    else
        insulinCartridge = 0;
    
    lastBolusDelivered = finalBolus;
    
    dataLogger->logEvent("Manual bolus delivery initiated.");
    std::cout << "Manual Bolus Calculation:" << std::endl;
    std::cout << "Carb Bolus: " << carbBolus << " units" << std::endl;
    std::cout << "Correction Bolus: " << correctionBolus << " units" << std::endl;
    std::cout << "Total Bolus (before IOB adjustment): " << totalBolus << " units" << std::endl;
    std::cout << "Final Bolus (after IOB adjustment): " << finalBolus << " units" << std::endl;
    std::cout << "Immediate Bolus (60%): " << immediateBolus << " units" << std::endl;
    std::cout << "Extended Bolus (40%): " << extendedBolus << " units" << std::endl;
}

void InsulinPump::applyBolusEffect(float reductionFactor) {
    cgmDataHandler->reduceGlucose(lastBolusDelivered * reductionFactor);
}

float InsulinPump::getBatteryLevel() const {
    return batteryLevel;
}

float InsulinPump::getInsulinCartridgeLevel() const {
    return insulinCartridge;
}

bool InsulinPump::isPoweredOn() const {
    return isPowered;
}


void InsulinPump::advanceTimeStep() {
    updateBatteryStatus();
    
    if (isPowered && deliveryManager->isDelivering()) {
        float dynamicBasal = deliveryManager->getDynamicBasalRate();
        if (insulinCartridge >= dynamicBasal) {
            insulinCartridge -= dynamicBasal;
            dataLogger->logEvent("Insulin consumed: " + std::to_string(dynamicBasal) + " units.");
        } else {
            insulinCartridge = 0;
            errorManager->logError("Insulin cartridge empty!");
        }
    }
}