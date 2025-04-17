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
    connect(ui->ConfirmBtn, &QPushButton::clicked, this, &bolus::handleConfirmBtn);
    connect(ui->ExtendedBolusRadio, &QRadioButton::toggled, this, &bolus::handleExtendedRadio);
    connect(ui->ExtendedConfirmBtn, &QPushButton::clicked, this, &bolus::handleExtendedConfirmBtn);

    ui->ConfirmBtn->show();
    ui->ExtendedConfirmBtn->hide();
    ui->NowLabel->hide();
    ui->NowLineEdit->hide();
    ui->LaterLabel->hide();
    ui->LaterLineEdit->hide();
    ui->DurationLabel->hide();
    ui->DurationDoubleSpinBox->hide();
    ui->percentageLabel->hide();
    ui->percentagleLabel2->hide();
    ui->hrsLabel->hide();

}

bolus::~bolus()
{
    delete ui;
}

void bolus::handleLogoBtn(){
    emit logoBtnPressed();
}

// Calculate and administer insulin bolus
void bolus::handleCalculationBtn(){
    bool carbsOk = false;
    bool glucoseOk = false;

    // Get carbs and glucose values from input fields
    carbs = ui->CarbsLineEdit->text().toInt(&carbsOk);
    glucose = ui->GlucoseLineEdit->text().toDouble(&glucoseOk);

    // Validate inputs
    if (!carbsOk || !glucoseOk) {
        QMessageBox::warning(this, "Invalid Input", "Please enter valid numbers for carbs and glucose.");
        return;
    }

    // Simple insulin calculation formula (this would be more complex in a real system)
    // 1 unit per 10g carbs + correction for high glucose
    insulinDose = carbs / 10.0;

    // Add correction if glucose is high (above 7.0 mmol/L)
    if (glucose > 7.0) {
        insulinDose += (glucose - 7.0) * 0.5; // 0.5 units per 1.0 mmol/L above target
    }

    // Round to 1 decimal place
    insulinDose = qRound(insulinDose * 10) / 10.0;

    // Display the calculated insulin dose
    ui->CalculationDisplay->display(insulinDose);
}

void bolus::handleConfirmBtn(){
    // Emit signal that insulin was administered
    emit insulinAdministered(insulinDose);
    emit exportCarbs(carbs);

    // Show confirmation message
    QMessageBox::information(this, "Bolus Administered",
                           QString("Administered %1 units of insulin.").arg(insulinDose));
}

void bolus::handleExtendedRadio(bool checked){
    if(checked){
        ui->ConfirmBtn->hide();
        ui->ExtendedConfirmBtn->show();
        ui->NowLabel->show();
        ui->NowLineEdit->show();
        ui->LaterLabel->show();
        ui->LaterLineEdit->show();
        ui->DurationLabel->show();
        ui->DurationDoubleSpinBox->show();
        ui->percentageLabel->show();
        ui->percentagleLabel2->show();
        ui->hrsLabel->show();
    }
    else{
        ui->ConfirmBtn->show();
        ui->ExtendedConfirmBtn->hide();
        ui->NowLabel->hide();
        ui->NowLineEdit->hide();
        ui->LaterLabel->hide();
        ui->LaterLineEdit->hide();
        ui->DurationLabel->hide();
        ui->DurationDoubleSpinBox->hide();
        ui->percentageLabel->hide();
        ui->percentagleLabel2->hide();
        ui->hrsLabel->hide();
    }
}

void bolus::handleExtendedConfirmBtn(){
    immediate = ui->NowLineEdit->text().toDouble() / 100;
    extended = ui->LaterLineEdit->text().toDouble() / 100;
    duration = ui->DurationDoubleSpinBox->text().toDouble();

    if (duration <= 0) {
        QMessageBox::warning(this, "Invalid Duration", "Duration must be greater than zero.");
        return;
    }

    immediateBolus  = immediate * insulinDose;
    extendedBolus = (extended * insulinDose) / duration;


    emit insulinAdministered(immediateBolus);
    emit exportCarbs(carbs);
    emit extendedAdministered(extendedBolus, duration);
    QMessageBox::information(this, "Bolus Administered",
                           QString("Administered %1 units of insulin. \n %2 units will be administered after over %3 hours. \n Total adminstered: %4")
                             .arg(immediateBolus)
                             .arg(extendedBolus)
                             .arg(duration)
                             .arg(insulinDose));
}
