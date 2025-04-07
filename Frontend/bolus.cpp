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

// Calculate and administer insulin bolus
void bolus::handleCalculationBtn(){
    bool carbsOk = false;
    bool glucoseOk = false;

    // Get carbs and glucose values from input fields
    int carbs = ui->CarbsLineEdit->text().toInt(&carbsOk);
    double glucose = ui->GlucoseLineEdit->text().toDouble(&glucoseOk);

    // Validate inputs
    if (!carbsOk || !glucoseOk) {
        QMessageBox::warning(this, "Invalid Input", "Please enter valid numbers for carbs and glucose.");
        return;
    }

    // Simple insulin calculation formula (this would be more complex in a real system)
    // 1 unit per 10g carbs + correction for high glucose
    double insulinDose = carbs / 10.0;

    // Add correction if glucose is high (above 7.0 mmol/L)
    if (glucose > 7.0) {
        insulinDose += (glucose - 7.0) * 0.5; // 0.5 units per 1.0 mmol/L above target
    }

    // Round to 1 decimal place
    insulinDose = round(insulinDose * 10) / 10.0;

    // Display the calculated insulin dose
    ui->CalculationDisplay->display(insulinDose);

    // Emit signal that insulin was administered
    emit insulinAdministered(insulinDose);

    // Show confirmation message
    QMessageBox::information(this, "Bolus Administered",
                           QString("Administered %1 units of insulin.").arg(insulinDose));
}
