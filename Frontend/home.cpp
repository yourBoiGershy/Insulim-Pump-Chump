#include "home.h"
#include "ui_home.h"
#include "def.h"

home::home(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::home)
  , battery(this)
  , batteryLevel(MAX_BATTERY)
  , powerOn(false)
{
    ui->setupUi(this);
    battery.setInterval(BATTERY_TIMER);

    togglePower();

    // Power and charge button
    connect(ui->PowerBtn, &QPushButton::clicked, this, &home::handlePowerBtn);
    connect(ui->ChargeBtn, &QPushButton::clicked, this, &home::handleChargeBtn);

    // Bolus and Options button
    connect(ui->Bolusbtn, &QPushButton::clicked, this, &home::handleBolusBtn);
    connect(ui->OptionsBtn, &QPushButton::clicked, this, &home::handleOptionsBtn);

    // battery, time, and date
    connect(&battery, &QTimer::timeout, this, &home::handleBatteryTime);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=](){
        QTime currentTime = QTime::currentTime();
        ui->TimeDisplay->setTime(currentTime);
    });

    QTimer *date = new QTimer(this);
    connect(date, &QTimer::timeout, this, [=]() {
        ui->DateDisplay->setDate(QDate::currentDate());
    });


}

home::~home()
{
    delete ui;
}

void home::togglePower(){
    if (powerOn){
        battery.start();
        ui->Bolusbtn->show();
        ui->OptionsBtn->show();
        ui->DateDisplay->show();
        ui->TimeDisplay->show();
        ui->GlucoseLevel->show();
        ui->InsulinOnBoard->show();
        ui->InsulinSpinBox->show();
        ui->glucoseUnit->show();
        ui->insulinUnit->show();
        ui->insulinLabel->show();
        ui->GraphWidget->show();
        ui->PowerBtn->hide();
    }
    else{
        battery.stop();
        ui->Bolusbtn->hide();
        ui->OptionsBtn->hide();
        ui->DateDisplay->hide();
        ui->TimeDisplay->hide();
        ui->GlucoseLevel->hide();
        ui->InsulinOnBoard->hide();
        ui->InsulinSpinBox->hide();
        ui->glucoseUnit->hide();
        ui->insulinUnit->hide();
        ui->insulinLabel->hide();
        ui->GraphWidget->hide();
        ui->PowerBtn->show();
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
}

void home::handleBolusBtn(){
    emit bolusBtnPressed();
}

void home::handleOptionsBtn(){
    emit optionsBtnPressed();
}

void home::handleBatteryTime(){
    if (batteryLevel > 0){
        batteryLevel--;
        ui->BatterySpinBox->setValue(batteryLevel);
    }
    else{
        powerOn = false;
        togglePower();
    }
}
