#ifndef INSULINPUMP_H
#define INSULINPUMP_H

#include "UserProfile.h"
#include "ProfileManager.h"
#include "BolusCalculator.h"
#include "CGMDataHandler.h"
#include "InsulinDeliveryManager.h"
#include "ErrorManager.h"
#include "DataLogger.h"

class InsulinPump {
public:
    InsulinPump(ProfileManager* profileMgr, BolusCalculator* bolusCalc, CGMDataHandler* cgmHandler,
                InsulinDeliveryManager* deliveryMgr, ErrorManager* errMgr, DataLogger* logger);
    void powerOn();
    void powerOff();
    void startInsulinDelivery();
    void stopInsulinDelivery();
    void resumeInsulinDelivery();
    void updateBatteryStatus();
    void setCurrentProfile(const UserProfile& profile);
    void manualBolusDelivery(float carbs, float currentBG, float IOB);
    float getBatteryLevel() const;
    float getInsulinCartridgeLevel() const;
    bool isPoweredOn() const;
    void advanceTimeStep();
    void applyBolusEffect(float reductionFactor);
    
private:
    float batteryLevel;
    float insulinCartridge;
    bool isPowered;
    UserProfile currentProfile;
    ProfileManager* profileManager;
    BolusCalculator* bolusCalculator;
    CGMDataHandler* cgmDataHandler;
    InsulinDeliveryManager* deliveryManager;
    ErrorManager* errorManager;
    DataLogger* dataLogger;
    float lastBolusDelivered; 

};

#endif 