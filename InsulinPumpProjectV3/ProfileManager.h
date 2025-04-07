#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

#include "UserProfile.h"
#include <vector>
#include <string>

class ProfileManager {
public:
    void createProfile(const UserProfile& profile);
    UserProfile* readProfile(const std::string& profileName);
    void updateProfile(const UserProfile& profile);
    void deleteProfile(const std::string& profileName);
    std::vector<UserProfile> listProfiles() const;
private:
    std::vector<UserProfile> profiles;
};

#endif 