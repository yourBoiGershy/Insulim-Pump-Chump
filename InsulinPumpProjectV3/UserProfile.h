#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <string>

class UserProfile {
public:
    UserProfile(const std::string& name, float basalRate, float icr, float correctionFactor, float targetBG);
    void updateProfile(float basalRate, float icr, float correctionFactor, float targetBG);
    std::string getProfileDetails() const;

    std::string profileName;
    float basalRate;
    float insulinToCarbRatio;
    float correctionFactor;
    float targetBloodGlucose;
};

#endif 