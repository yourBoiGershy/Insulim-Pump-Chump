#include "bolus.h"
#include "ui_bolus.h"

bolus::bolus(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bolus)
{
    ui->setupUi(this);

    // connect to buttons
    connect(ui->LogoBtn, &QPushButton::clicked, this, &bolus::handleLogoBtn);
    connect(ui->CalculationBtn, &QPushButton::clicked, this, &bolus::handleCalculationBtn);
}

bolus::~bolus()
{
    delete ui;
}

void bolus::handleLogoBtn(){
    emit logoBtnPressed();
}

// add logic for calculations to be displayed
void bolus::handleCalculationBtn(){
}
