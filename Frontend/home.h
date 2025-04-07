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

namespace Ui {
class home;
}

class home : public QWidget
{
    Q_OBJECT

public:
    explicit home(QWidget *parent = nullptr);
    ~home();
    void togglePower();

private:
    Ui::home *ui;

    QTimer battery;
    QTimer simulationTimer;
    int batteryLevel;
    bool powerOn;
    bool simulationRunning;

    // Simulation parameters
    double currentGlucose;
    double insulinOnBoard;
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

    // Convert real seconds to simulation time
    QDateTime getSimulationTime(int secondsElapsed);

signals:
    void bolusBtnPressed();
    void optionsBtnPressed();

public slots:
    void handlePowerBtn();
    void receiveInsulin(double units);

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
