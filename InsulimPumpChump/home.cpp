#include "home.h"
#include "ui_home.h"
#include "def.h"
#include <QRandomGenerator>
#include <QtMath>
#include <QListWidgetItem>
#include <QDateTime>
#include <QElapsedTimer>
#include <QLabel>
#include <QPainter>
#include <QPen>
#include <QBrush>

home::home(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::home),
    batteryLevel(MAX_BATTERY),
    powerOn(false),
    simulationRunning(true),
    currentGlucose(5.5), // Starting glucose level in mmol/L
    insulinOnBoard(0.0),
    simulationSpeed(1000), // 1 second default
    graphLayout(nullptr),
    graphLabel(nullptr),
    displayHours(2) // Default to 2 hours view
{
    ui->setupUi(this);

    togglePower();

    // Power and charge button
    connect(ui->PowerBtn, &QPushButton::clicked, this, &home::handlePowerBtn);
    connect(ui->ChargeBtn, &QPushButton::clicked, this, &home::handleChargeBtn);

    // Bolus and Options button
    connect(ui->Bolusbtn, &QPushButton::clicked, this, &home::handleBolusBtn);
    connect(ui->OptionsBtn, &QPushButton::clicked, this, &home::handleOptionsBtn);

    // Setup battery timer
    battery.setInterval(BATTERY_TIMER);
    connect(&battery, &QTimer::timeout, this, &home::handleBatteryTime);

    // Setup time and date timers
    QTimer *timeTimer = new QTimer(this);
    timeTimer->setInterval(1000);
    connect(timeTimer, &QTimer::timeout, this, &home::updateTime);
    timeTimer->start();

    QTimer *dateTimer = new QTimer(this);
    dateTimer->setInterval(60000);
    connect(dateTimer, &QTimer::timeout, this, &home::updateDate);
    dateTimer->start();

    // Connect simulation control buttons
    connect(ui->PauseResumeBtn, &QPushButton::clicked, this, &home::handlePauseResumeBtn);
    connect(ui->SimSpeedBtn, &QPushButton::clicked, this, &home::handleSimulationSpeedBtn);
    connect(ui->TimeRangeBtn, &QPushButton::clicked, this, &home::handleTimeRangeBtn);
    connect(ui->ClearDataBtn, &QPushButton::clicked, this, &home::handleClearDataBtn);

    // Setup timer for simulation
    simTimer.setInterval(simulationSpeed);
    connect(&simTimer, &QTimer::timeout, this, &home::handleSimulationTimer);

    // Initialize displays
    ui->GlucoseLevel->display(currentGlucose);
    ui->InsulinOnBoard->display(insulinOnBoard);
    ui->SimStatusLabel->setText("Status: Running");
    ui->SimTimeLabel->setText("Sim Time: 00:00");

    // Setup graph
    setupGraph();

    // Initialize glucose data vector with 2 hours of data (24 points at 5-min intervals)
    QDateTime startTime = QDateTime::currentDateTime();
    for (int i = 0; i < 24; i++) {
        glucoseData.append(5.5);
        timeData.append(startTime.addSecs(i * 300)); // Add 5 minutes (300 seconds) for each point
    }

    // Initial updates
    drawGraph();
    updateGraph();

}

home::~home()
{
    delete ui;
    if (graphLabel) delete graphLabel;
}

void home::togglePower(){
    if (powerOn){
        ui->Bolusbtn->show();
        ui->OptionsBtn->show();
        ui->DateDisplay->show();
        ui->TimeDisplay->show();
        ui->GlucoseLevel->show();
        ui->InsulinOnBoard->show();
        ui->glucoseUnit->show();
        ui->insulinUnit->show();
        ui->insulinLabel->show();
        ui->GraphWidget->show();
        ui->DataListWidget->show();
        ui->PauseResumeBtn->show();
        ui->SimSpeedBtn->show();
        ui->SimStatusLabel->show();
        ui->TimeRangeBtn->show();
        ui->ClearDataBtn->show();
        ui->SimTimeLabel->show();
        ui->PowerBtn->hide();
        ui->LogGroupBox->show();
        battery.start();
        simTimer.start();
    }
    else{
        battery.stop();
        simTimer.start();
        ui->Bolusbtn->hide();
        ui->OptionsBtn->hide();
        ui->DateDisplay->hide();
        ui->TimeDisplay->hide();
        ui->GlucoseLevel->hide();
        ui->InsulinOnBoard->hide();
        ui->glucoseUnit->hide();
        ui->insulinUnit->hide();
        ui->insulinLabel->hide();
        ui->GraphWidget->hide();
        ui->DataListWidget->hide();
        ui->PauseResumeBtn->hide();
        ui->SimSpeedBtn->hide();
        ui->SimStatusLabel->hide();
        ui->TimeRangeBtn->hide();
        ui->ClearDataBtn->hide();
        ui->SimTimeLabel->hide();
        ui->PowerBtn->show();
        ui->LogGroupBox->hide();
    }
}

void home::handlePowerBtn(){
    if (batteryLevel > 0){
        powerOn = !powerOn;
        togglePower();
    }
}

void home::handleChargeBtn(){
   batteryLevel = 100;
   ui->BatterySpinBox->setValue(batteryLevel);
   ui->LowPowerLabel->hide();
}

void home::handleBolusBtn(){
    emit bolusBtnPressed();
}

void home::handleOptionsBtn(){
    emit optionsBtnPressed();
}

void home::handleBatteryTime(){
    if (batteryLevel > 0){
        if (batteryLevel < 10) {
            ui->LowPowerLabel->show();
        }
        else {
            ui->LowPowerLabel->hide();
        }
        batteryLevel--;
        ui->BatterySpinBox->setValue(batteryLevel);
    }
    else{
        battery.start();
        simTimer.start();
        powerOn = false;
        togglePower();
    }
}

void home::receiveInsulin(double units) {
    // Add insulin to the simulation
    insulinOnBoard += units;

    // Update display
    ui->InsulinOnBoard->display(insulinOnBoard);
}

void home::setupGraph() {
    // Create a label to display the graph
    graphLabel = new QLabel();
    graphLabel->setMinimumSize(400, 300);

    // Create pixmap for drawing
    graphPixmap = QPixmap(400, 300);
    graphPixmap.fill(Qt::white);

    // Add label to layout
    graphLayout = new QVBoxLayout(ui->GraphWidget);
    graphLayout->addWidget(graphLabel);
    ui->GraphWidget->setLayout(graphLayout);
}

void home::drawGraph() {
    // Clear the pixmap
    graphPixmap.fill(Qt::white);

    // Create painter
    QPainter painter(&graphPixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    // Calculate how many points to display based on the selected time range
    int pointsToShow = displayHours * 12; // 12 points per hour (5-minute intervals)

    // If we have fewer points than needed, use what we have
    int startIndex = qMax(0, glucoseData.size() - pointsToShow);
    int numPoints = glucoseData.size() - startIndex;

    if (numPoints < 2) {
        // Not enough points to draw a graph
        graphLabel->setPixmap(graphPixmap);
        return;
    }

    // Set up coordinate system
    int width = graphPixmap.width();
    int height = graphPixmap.height();
    int leftMargin = 60; // Left margin for Y axis and labels
    int rightMargin = 20; // Right margin
    int topMargin = 50; // Top margin for title
    int bottomMargin = 60; // Bottom margin for X axis and labels

    // Draw axes
    painter.setPen(QPen(Qt::black, 2));
    painter.drawLine(leftMargin, height - bottomMargin, width - rightMargin, height - bottomMargin); // X axis
    painter.drawLine(leftMargin, topMargin, leftMargin, height - bottomMargin); // Y axis

    // Draw axis labels with more space
    painter.drawText(width / 2 - 20, height - 15, "Time");
    painter.rotate(-90);
    painter.drawText(-height / 2 - 30, 15, "Glucose (mmol/L)");
    painter.rotate(90);

    // Draw title with more space
    painter.setFont(QFont("Arial", 12, QFont::Bold));
    painter.drawText(width / 2 - 80, 30, "Glucose Monitoring");
    painter.setFont(QFont());

    // Draw Y axis ticks and labels
    double minY = 3.0;
    double maxY = 10.0;
    int numYTicks = 7;
    double yTickStep = (maxY - minY) / (numYTicks - 1);

    for (int i = 0; i < numYTicks; i++) {
        double yValue = minY + i * yTickStep;
        int y = height - bottomMargin - (int)((yValue - minY) / (maxY - minY) * (height - topMargin - bottomMargin));

        // Draw tick
        painter.drawLine(leftMargin - 5, y, leftMargin, y);

        // Draw label
        painter.drawText(leftMargin - 35, y + 5, QString::number(yValue, 'f', 1));
    }

    // Draw X axis ticks and labels
    int numXTicks = 6;

    for (int i = 0; i < numXTicks; i++) {
        int x = leftMargin + i * ((width - leftMargin - rightMargin) / (numXTicks - 1));

        // Draw tick
        painter.drawLine(x, height - bottomMargin, x, height - bottomMargin + 5);

        // Draw label (time)
        if (!timeData.isEmpty() && numPoints > 0) {
            int dataIndex = startIndex + (i * (numPoints - 1)) / (numXTicks - 1);
            if (dataIndex < timeData.size()) {
                QString timeStr = timeData[dataIndex].toString("hh:mm");
                painter.drawText(x - 20, height - bottomMargin + 25, timeStr);
            }
        }
    }

    // Draw data points and connect them with lines
    QPainterPath path;
    bool firstPoint = true;

    // Normal range indicators (4-8 mmol/L)
    int normalLowY = height - bottomMargin - (int)((4.0 - minY) / (maxY - minY) * (height - topMargin - bottomMargin));
    int normalHighY = height - bottomMargin - (int)((8.0 - minY) / (maxY - minY) * (height - topMargin - bottomMargin));

    // Draw normal range background
    painter.setBrush(QBrush(QColor(200, 255, 200, 100)));
    painter.setPen(Qt::NoPen);
    painter.drawRect(leftMargin, normalHighY, width - leftMargin - rightMargin, normalLowY - normalHighY);

    // Draw data line
    painter.setPen(QPen(Qt::blue, 2));

    for (int i = startIndex; i < glucoseData.size(); i++) {
        // Calculate x and y coordinates
        int x = leftMargin + (int)((i - startIndex) * (width - leftMargin - rightMargin) / (numPoints - 1));
        int y = height - bottomMargin - (int)((glucoseData[i] - minY) / (maxY - minY) * (height - topMargin - bottomMargin));

        if (firstPoint) {
            path.moveTo(x, y);
            firstPoint = false;
        } else {
            path.lineTo(x, y);
        }

        // Draw point
        painter.setBrush(QBrush(Qt::blue));
        painter.drawEllipse(QPoint(x, y), 3, 3);
    }

    // Draw the line connecting all points
    painter.setPen(QPen(Qt::blue, 2));
    painter.drawPath(path);

    // Update the label with the new pixmap
    graphLabel->setPixmap(graphPixmap);
}

void home::updateGraph() {
    // Clear the list widget
    ui->DataListWidget->clear();

    // Add glucose data points to the list widget
    int startIndex = qMax(0, glucoseData.size() - 20); // Show last 20 points in the list

    for (int i = startIndex; i < glucoseData.size(); i++) {
        QString timeStr = timeData[i].toString("hh:mm");
        QString label = QString("%1: %2 mmol/L").arg(timeStr).arg(glucoseData[i], 0, 'f', 1);
        QListWidgetItem *item = new QListWidgetItem(label);
        ui->DataListWidget->addItem(item);
    }

    // Scroll to the bottom to show the most recent data
    ui->DataListWidget->scrollToBottom();
}

QDateTime home::getSimulationTime(int secondsElapsed) {
    // 1 real second = 5 simulated minutes
    QDateTime baseTime = QDateTime::currentDateTime();
    return baseTime.addSecs(secondsElapsed * 300); // 300 seconds = 5 minutes
}

void home::generateGlucoseData() {
    // Simulate glucose level changes
    // In a real system, this would be based on complex physiological models

    // Random fluctuation with some physiological constraints
    double randomFactor = (QRandomGenerator::global()->generateDouble() * 0.4) - 0.2;

    // Effect of insulin (decreases glucose)
    double insulinEffect = 0;
    if (insulinOnBoard > 0) {
        insulinEffect = -0.05 * insulinOnBoard;
        insulinOnBoard = qMax(0.0, insulinOnBoard - 0.02); // Insulin gets used up
    }

    // Calculate new glucose level
    currentGlucose += randomFactor + insulinEffect;

    // Ensure glucose stays in a reasonable range
    currentGlucose = qBound(3.0, currentGlucose, 10.0);

    // Update displays
    ui->GlucoseLevel->display(currentGlucose);
    ui->InsulinOnBoard->display(insulinOnBoard);

    // Get current simulation time
    static int secondsElapsed = 0;
    secondsElapsed++;
    QDateTime simTime = getSimulationTime(secondsElapsed);

    // Update simulation time display (format: hh:mm)
    ui->SimTimeLabel->setText("Sim Time: " + simTime.toString("hh:mm"));

    // Add data point to vectors
    glucoseData.append(currentGlucose);
    timeData.append(simTime);

    // Keep data for at least 6 hours (72 points)
    while (glucoseData.size() > 72) {
        glucoseData.removeFirst();
        timeData.removeFirst();
    }

    // Update the graph and list
    drawGraph();
    updateGraph();
    if (currentGlucose <= 3.0 && simulationRunning) {
        simulationRunning = false;
        ui->PauseResumeBtn->setText("Resume");
        ui->SimStatusLabel->setText("Status: Paused (Low Glucose)");
    }
}

void home::handleSimulationTimer() {
    if (simulationRunning) {
        generateGlucoseData();
        if (insulinOnBoard == 0.0) {
                   simulationRunning = false;
                   ui->PauseResumeBtn->setText("Resume");
                   ui->SimStatusLabel->setText("Status: Paused (Low Insulin)");
        }
    }
}

void home::handlePauseResumeBtn() {
    simulationRunning = !simulationRunning;

    if (simulationRunning) {
        ui->PauseResumeBtn->setText("Pause");
        ui->SimStatusLabel->setText("Status: Running");
    } else {
        ui->PauseResumeBtn->setText("Resume");
        ui->SimStatusLabel->setText("Status: Paused");
    }
}

void home::handleSimulationSpeedBtn() {
    // Cycle through different simulation speeds
    if (simulationSpeed == 1000) { // 1 second
        simulationSpeed = 500;  // 0.5 seconds
        ui->SimStatusLabel->setText("Speed: Fast");
    } else if (simulationSpeed == 500) {
        simulationSpeed = 2000; // 2 seconds
        ui->SimStatusLabel->setText("Speed: Slow");
    } else {
        simulationSpeed = 1000; // Back to 1 second
        ui->SimStatusLabel->setText("Speed: Normal");
    }

    // Find and update the simulation timer
    QList<QTimer*> timers = this->findChildren<QTimer*>();
    for (QTimer* timer : timers) {
        timer->setInterval(simulationSpeed);
    }
}

void home::handleTimeRangeBtn() {
    // Cycle through different time ranges (1, 3, 6 hours)
    if (displayHours == 1) {
        displayHours = 3;
        ui->TimeRangeBtn->setText("Time Range: 3h");
    } else if (displayHours == 3) {
        displayHours = 6;
        ui->TimeRangeBtn->setText("Time Range: 6h");
    } else {
        displayHours = 1;
        ui->TimeRangeBtn->setText("Time Range: 1h");
    }

    // Update the graph to reflect the new time range
    drawGraph();
}

void home::handleClearDataBtn() {
    // Clear all data points except for the current one
    double lastGlucose = currentGlucose;
    QDateTime lastTime = QDateTime::currentDateTime();

    glucoseData.clear();
    timeData.clear();

    // Add back the current point
    glucoseData.append(lastGlucose);
    timeData.append(lastTime);

    // Update displays
    drawGraph();
    updateGraph();
}

void home::updateTime() {
    QTime currentTime = QTime::currentTime();
    ui->TimeDisplay->setTime(currentTime);
}

void home::updateDate() {
    ui->DateDisplay->setDate(QDate::currentDate());
}
