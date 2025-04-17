#include "profilemanager.h"

ProfileManager::ProfileManager() : settings("InsulinPump", "Profiles") {
    // Check if we need to create default profiles
    if (getAllProfiles().isEmpty()) {
        createDefaultProfiles();
    }
}

QVector<Profile> ProfileManager::getAllProfiles() const {
    return loadProfiles();
}

Profile ProfileManager::getProfile(const QString &name) const {
    QVector<Profile> profiles = loadProfiles();

    for (const Profile &profile : profiles) {
        if (profile.getName() == name) {
            return profile;
        }
    }

    // Return an empty profile if not found
    return Profile();
}

Profile ProfileManager::getActiveProfile() const {
    QVector<Profile> profiles = loadProfiles();

    for (const Profile &profile : profiles) {
        if (profile.isActive()) {
            return profile;
        }
    }

    // If no active profile, return the first one or an empty profile
    if (!profiles.isEmpty()) {
        return profiles.first();
    }

    return Profile();
}

bool ProfileManager::saveProfile(const Profile &profile) {
    QVector<Profile> profiles = loadProfiles();

    // Check if profile already exists
    bool found = false;
    for (int i = 0; i < profiles.size(); ++i) {
        if (profiles[i].getName() == profile.getName()) {
            profiles[i] = profile;
            found = true;
            break;
        }
    }

    // If not found, add it
    if (!found) {
        profiles.append(profile);
    }

    // Save all profiles
    saveProfiles(profiles);

    return true;
}

bool ProfileManager::deleteProfile(const QString &name) {
    QVector<Profile> profiles = loadProfiles();

    // Find and remove the profile
    for (int i = 0; i < profiles.size(); ++i) {
        if (profiles[i].getName() == name) {
            // Don't delete the active profile
            if (profiles[i].isActive()) {
                return false;
            }

            profiles.remove(i);
            saveProfiles(profiles);
            return true;
        }
    }

    return false;
}

bool ProfileManager::setActiveProfile(const QString &name) {
    QVector<Profile> profiles = loadProfiles();

    // Deactivate all profiles and activate the selected one
    bool found = false;
    for (int i = 0; i < profiles.size(); ++i) {
        if (profiles[i].getName() == name) {
            profiles[i].setActive(true);
            found = true;
        } else {
            profiles[i].setActive(false);
        }
    }

    if (found) {
        saveProfiles(profiles);
        return true;
    }

    return false;
}

void ProfileManager::createDefaultProfiles() {
    QVector<Profile> profiles;

    // Morning profile
    Profile morningProfile("Morning");
    TimeSegment morningSegment;
    morningSegment.startTime = QTime(6, 0);
    morningSegment.insulinToCarbRatio = 10.0;
    morningSegment.correctionFactor = 2.0;
    morningSegment.targetGlucose = 5.5;
    morningSegment.basalRate = 1.0;
    morningProfile.addTimeSegment(morningSegment);
    morningProfile.setActive(true);
    profiles.append(morningProfile);

    // Exercise profile
    Profile exerciseProfile("Exercise");
    TimeSegment exerciseSegment;
    exerciseSegment.startTime = QTime(0, 0);
    exerciseSegment.insulinToCarbRatio = 15.0; // Less insulin for carbs during exercise
    exerciseSegment.correctionFactor = 3.0;    // Less insulin for corrections
    exerciseSegment.targetGlucose = 6.5;       // Higher target to prevent lows
    exerciseSegment.basalRate = 0.7;           // Reduced basal rate
    exerciseProfile.addTimeSegment(exerciseSegment);
    profiles.append(exerciseProfile);

    // Night profile
    Profile nightProfile("Night");
    TimeSegment nightSegment;
    nightSegment.startTime = QTime(22, 0);
    nightSegment.insulinToCarbRatio = 12.0;
    nightSegment.correctionFactor = 2.5;
    nightSegment.targetGlucose = 6.0;
    nightSegment.basalRate = 0.8;
    nightProfile.addTimeSegment(nightSegment);
    profiles.append(nightProfile);

    // Save the default profiles
    saveProfiles(profiles);
}

void ProfileManager::saveProfiles(const QVector<Profile> &profiles) {
    // Save profiles to settings
    settings.beginWriteArray("profiles");

    for (int i = 0; i < profiles.size(); ++i) {
        settings.setArrayIndex(i);
        settings.setValue("data", profiles[i].serialize());
    }

    settings.endArray();
    settings.sync();
}

QVector<Profile> ProfileManager::loadProfiles() const {
    QVector<Profile> profiles;

    // Load profiles from settings
    QSettings settingsRead("InsulinPump", "Profiles");
    int size = settingsRead.beginReadArray("profiles");

    for (int i = 0; i < size; ++i) {
        settingsRead.setArrayIndex(i);
        QByteArray data = settingsRead.value("data").toByteArray();

        if (!data.isEmpty()) {
            profiles.append(Profile::deserialize(data));
        }
    }

    settingsRead.endArray();

    return profiles;
}
