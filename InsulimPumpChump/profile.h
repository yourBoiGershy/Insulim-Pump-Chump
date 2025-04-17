#ifndef PROFILE_H
#define PROFILE_H

#include <QString>
#include <QVector>
#include <QMap>
#include <QDateTime>

// Structure to represent a time segment in a profile
struct TimeSegment {
    QTime startTime;
    double insulinToCarbRatio;  // Units per gram of carbs
    double correctionFactor;    // Units per mmol/L above target
    double targetGlucose;       // Target glucose in mmol/L
    double basalRate;           // Units per hour
};

class Profile {
public:
    Profile();
    Profile(const QString &name);

    static void setActive(const Profile& profile);
    static Profile getActive();
    
    // Getters
    QString getName() const { return name; }
    QVector<TimeSegment> getTimeSegments() const { return timeSegments; }
    bool isActive() const { return active; }
    QDateTime getCreatedDate() const { return createdDate; }
    
    // Setters
    void setName(const QString &name) { this->name = name; }
    void setActive(bool active) { this->active = active; }
    
    // Time segment management
    void addTimeSegment(const TimeSegment &segment);
    void updateTimeSegment(int index, const TimeSegment &segment);
    void removeTimeSegment(int index);
    
    // Get settings for current time
    double getCurrentInsulinToCarbRatio() const;
    double getCurrentCorrectionFactor() const;
    double getCurrentTargetGlucose() const;
    double getCurrentBasalRate() const;
    
    // Serialization for storage
    QByteArray serialize() const;
    static Profile deserialize(const QByteArray &data);
    
private:
    QString name;
    QVector<TimeSegment> timeSegments;
    bool active;
    QDateTime createdDate;

    static Profile activeProfile;
    
    // Helper to find the appropriate time segment for a given time
    int findSegmentForTime(const QTime &time) const;
};

#endif // PROFILE_H
