#ifndef HOME_H
#define HOME_H

#include <QWidget>
#include <QTimer>
#include <QVector>
#include <QDateTime>
#include <QVBoxLayout>
#include <QPainter>
#include <QPainterPath>
#include <QPixmap>
#include <QLabel>
#include <profile.h>

namespace Ui {
class home;
}

class home : public QWidget
{
    Q_OBJECT

public:
    explicit home(QWidget *parent = nullptr, const Profile &activeProfile = Profile());
    ~home();
    void togglePower();

private:
    Ui::home *ui;

    Profile profile;

    QTimer battery;
    QTimer simulationTimer;
    QTimer simTimer;
    int batteryLevel;
    bool powerOn;
    bool simulationRunning;

    double extendedBolusRemaining = 0.0;
    double extendedBolusPerTick = 0.0;
    int extendedTicksRemaining = 0;
    int extendedStartDelayTicks = 0;
    bool extendedBolusScheduled = false;

    // Simulation parameters
    double currentGlucose;
    double insulinOnBoard;
    double carbsOnBoard;
    int simulationSpeed;
    QVector<double> glucoseData;
    QVector<QDateTime> timeData;

    // Custom graph components
    QPixmap graphPixmap;
    QVBoxLayout *graphLayout;
    QLabel *graphLabel;

    // Time range for display (in hours)
    int displayHours;

    // Generate simulated data
    void generateGlucoseData();

    // Update graph display
    void updateGraph();

    // Setup custom graph
    void setupGraph();

    // Draw the graph
    void drawGraph();

    double predictGlucose30min();

    void setBolusIndicatorColour(const QString &state);

    void logEvent(const QString &event);

    // Convert real seconds to simulation time
    QDateTime getSimulationTime(int secondsElapsed);

signals:
    void bolusBtnPressed();
    void optionsBtnPressed();

public slots:
    void handlePowerBtn();
    void receiveInsulin(double units);
    void receiveCarbs(double carbs);
    void scheduleExtendedBolus(double extendedBolusTotal, double duration);

private slots:
    void handleChargeBtn();
    void handleBolusBtn();
    void handleOptionsBtn();
    void handleBatteryTime();
    void handleSimulationTimer();
    void handlePauseResumeBtn();
    void handleSimulationSpeedBtn();
    void updateTime();
    void updateDate();
    void handleTimeRangeBtn();
    void handleClearDataBtn();
};

#endif // HOME_H
