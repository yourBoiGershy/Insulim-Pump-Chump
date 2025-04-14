#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

#include "profile.h"
#include <QVector>
#include <QSettings>

class ProfileManager {
public:
    ProfileManager();
    
    // Profile management
    QVector<Profile> getAllProfiles() const;
    Profile getProfile(const QString &name) const;
    Profile getActiveProfile() const;
    
    bool saveProfile(const Profile &profile);
    bool deleteProfile(const QString &name);
    bool setActiveProfile(const QString &name);
    
    // Create default profiles
    void createDefaultProfiles();
    
private:
    QSettings settings;
    
    // Helper methods
    void saveProfiles(const QVector<Profile> &profiles);
    QVector<Profile> loadProfiles() const;
};

#endif // PROFILEMANAGER_H
