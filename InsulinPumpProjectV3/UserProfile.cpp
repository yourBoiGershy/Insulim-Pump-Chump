#include "UserProfile.h"
#include <sstream>

UserProfile::UserProfile(const std::string& name, float basalRate, float icr, float correctionFactor, float targetBG)
    : profileName(name), basalRate(basalRate), insulinToCarbRatio(icr),
      correctionFactor(correctionFactor), targetBloodGlucose(targetBG) {}

void UserProfile::updateProfile(float newBasalRate, float newIcr, float newCorrectionFactor, float newTargetBG) {
    basalRate = newBasalRate;
    insulinToCarbRatio = newIcr;
    correctionFactor = newCorrectionFactor;
    targetBloodGlucose = newTargetBG;
}

std::string UserProfile::getProfileDetails() const {
    std::ostringstream oss;
    oss << "Profile: " << profileName 
        << "\nBasal Rate: " << basalRate 
        << "\nICR: " << insulinToCarbRatio 
        << "\nCorrection Factor: " << correctionFactor 
        << "\nTarget BG: " << targetBloodGlucose;
    return oss.str();
}