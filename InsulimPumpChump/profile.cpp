#include "profile.h"
#include <QDataStream>
#include <QTime>
#include <QIODevice>

Profile Profile::activeProfile;

Profile::Profile() : active(false), createdDate(QDateTime::currentDateTime()) {
    // Create a default time segment covering the whole day
    TimeSegment defaultSegment;
    defaultSegment.startTime = QTime(0, 0);
    defaultSegment.insulinToCarbRatio = 10.0;  // 1 unit per 10g carbs
    defaultSegment.correctionFactor = 2.0;     // 1 unit per 2 mmol/L
    defaultSegment.targetGlucose = 5.5;        // 5.5 mmol/L target
    defaultSegment.basalRate = 1.0;            // 1 unit per hour

    timeSegments.append(defaultSegment);
}

Profile::Profile(const QString &name) : name(name), active(false), createdDate(QDateTime::currentDateTime()) {
    // Create a default time segment covering the whole day
    TimeSegment defaultSegment;
    defaultSegment.startTime = QTime(0, 0);
    defaultSegment.insulinToCarbRatio = 10.0;  // 1 unit per 10g carbs
    defaultSegment.correctionFactor = 2.0;     // 1 unit per 2 mmol/L
    defaultSegment.targetGlucose = 5.5;        // 5.5 mmol/L target
    defaultSegment.basalRate = 1.0;            // 1 unit per hour

    timeSegments.append(defaultSegment);
}

void Profile::addTimeSegment(const TimeSegment &segment) {
    // Add a new time segment and sort by start time
    timeSegments.append(segment);

    // Sort segments by start time
    std::sort(timeSegments.begin(), timeSegments.end(),
              [](const TimeSegment &a, const TimeSegment &b) {
                  return a.startTime < b.startTime;
              });
}

void Profile::updateTimeSegment(int index, const TimeSegment &segment) {
    if (index >= 0 && index < timeSegments.size()) {
        timeSegments[index] = segment;

        // Sort segments by start time
        std::sort(timeSegments.begin(), timeSegments.end(),
                  [](const TimeSegment &a, const TimeSegment &b) {
                      return a.startTime < b.startTime;
                  });
    }
}

void Profile::removeTimeSegment(int index) {
    if (index >= 0 && index < timeSegments.size()) {
        timeSegments.remove(index);
    }
}

int Profile::findSegmentForTime(const QTime &time) const {
    // Find the appropriate time segment for the given time
    if (timeSegments.isEmpty()) {
        return -1;
    }

    // If only one segment, return it
    if (timeSegments.size() == 1) {
        return 0;
    }

    // Find the segment that starts before or at the given time
    // and is the latest such segment
    int selectedSegment = 0;
    for (int i = 0; i < timeSegments.size(); ++i) {
        if (timeSegments[i].startTime <= time &&
            (i == timeSegments.size() - 1 || timeSegments[i+1].startTime > time)) {
            selectedSegment = i;
            break;
        }

        // Handle the case where time is before the first segment
        // In this case, use the last segment (wrapping around midnight)
        if (i == 0 && time < timeSegments[i].startTime) {
            selectedSegment = timeSegments.size() - 1;
            break;
        }
    }

    return selectedSegment;
}

double Profile::getCurrentInsulinToCarbRatio() const {
    int segmentIndex = findSegmentForTime(QTime::currentTime());
    if (segmentIndex >= 0) {
        return timeSegments[segmentIndex].insulinToCarbRatio;
    }
    return 10.0; // Default value
}

double Profile::getCurrentCorrectionFactor() const {
    int segmentIndex = findSegmentForTime(QTime::currentTime());
    if (segmentIndex >= 0) {
        return timeSegments[segmentIndex].correctionFactor;
    }
    return 2.0; // Default value
}

double Profile::getCurrentTargetGlucose() const {
    int segmentIndex = findSegmentForTime(QTime::currentTime());
    if (segmentIndex >= 0) {
        return timeSegments[segmentIndex].targetGlucose;
    }
    return 5.5; // Default value
}

double Profile::getCurrentBasalRate() const {
    int segmentIndex = findSegmentForTime(QTime::currentTime());
    if (segmentIndex >= 0) {
        return timeSegments[segmentIndex].basalRate;
    }
    return 1.0; // Default value
}

QByteArray Profile::serialize() const {
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);

    // Write profile data
    stream << name;
    stream << active;
    stream << createdDate;

    // Write time segments
    stream << timeSegments.size();
    for (const TimeSegment &segment : timeSegments) {
        stream << segment.startTime;
        stream << segment.insulinToCarbRatio;
        stream << segment.correctionFactor;
        stream << segment.targetGlucose;
        stream << segment.basalRate;
    }

    return data;
}

Profile Profile::deserialize(const QByteArray &data) {
    Profile profile;
    QDataStream stream(data);

    // Read profile data
    stream >> profile.name;
    stream >> profile.active;
    stream >> profile.createdDate;

    // Read time segments
    int segmentCount;
    stream >> segmentCount;

    profile.timeSegments.clear();
    for (int i = 0; i < segmentCount; ++i) {
        TimeSegment segment;
        stream >> segment.startTime;
        stream >> segment.insulinToCarbRatio;
        stream >> segment.correctionFactor;
        stream >> segment.targetGlucose;
        stream >> segment.basalRate;

        profile.timeSegments.append(segment);
    }

    return profile;
}

void Profile::setActive(const Profile& profile){
    activeProfile = profile;
    activeProfile.active = true;
}

Profile Profile::getActive(){
    return activeProfile;
}
