#include "ProfileManager.h"
#include <algorithm>

void ProfileManager::createProfile(const UserProfile& profile) {
    profiles.push_back(profile);
}

UserProfile* ProfileManager::readProfile(const std::string& profileName) {
    for (auto& profile : profiles) {
        if (profile.profileName == profileName)
            return &profile;
    }
    return nullptr;
}

void ProfileManager::updateProfile(const UserProfile& updatedProfile) {
    for (auto& profile : profiles) {
        if (profile.profileName == updatedProfile.profileName) {
            profile = updatedProfile;
            return;
        }
    }
}

void ProfileManager::deleteProfile(const std::string& profileName) {
    profiles.erase(std::remove_if(profiles.begin(), profiles.end(), 
        [&profileName](const UserProfile& p) { return p.profileName == profileName; }), profiles.end());
}

std::vector<UserProfile> ProfileManager::listProfiles() const {
    return profiles;
}