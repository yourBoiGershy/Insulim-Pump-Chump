#include "options.h"
#include "ui_options.h"

options::options(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::options)
{
    ui->setupUi(this);

    ui->PowerBtn_2->hide();

    connect(ui->LogoBtn, &QPushButton::clicked, this, &options::handleLogoBtn);
    connect(ui->ProfilesBtn, &QPushButton::clicked, this, &options::handleProfileBtn);
    connect(ui->PowerBtn, &QPushButton::clicked, this, &options::handlePowerBtn);
    connect(ui->SleepBtn, &QPushButton::clicked, this, &options::handleSleepBtn);
    connect(ui->PowerBtn_2, &QPushButton::clicked, this, &options::handlePowerOn);
}

options::~options()
{
    delete ui;
}

void options::handleLogoBtn(){
    emit logoBtnPressed();
}

void options::handleProfileBtn(){
    emit profileBtnPressed();
}

void options::handlePowerBtn(){
    emit powerBtnPressed();
}

void options::handleSleepBtn(){
    ui->LogoBtn->hide();
    ui->OptionsLabel->hide();
    ui->PowerBtn_2->show();
    ui->ProfilesBtn->hide();
    ui->SleepBtn->hide();
    ui->PowerBtn->hide();
}

void options::handlePowerOn(){
    ui->LogoBtn->show();
    ui->OptionsLabel->show();
    ui->PowerBtn_2->hide();
    ui->ProfilesBtn->show();
    ui->SleepBtn->show();
    ui->PowerBtn->show();
}
