#ifndef BOLUS_H
#define BOLUS_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
class bolus;
}

class bolus : public QWidget
{
    Q_OBJECT

public:
    explicit bolus(QWidget *parent = nullptr);
    ~bolus();

private:
    Ui::bolus *ui;
    int carbs;
    double glucose;
    double insulinDose;
    double immediateBolus;
    double extendedBolus;
    double immediate;
    double extended;
    double duration;

signals:
    void logoBtnPressed();
    void insulinAdministered(double units);
    void extendedAdministered(double extendedBolus, double duration);
    void exportCarbs(double carbs);

private slots:
    void handleCalculationBtn();
    void handleLogoBtn();
    void handleConfirmBtn();
    void handleExtendedRadio(bool checked);
    void handleExtendedConfirmBtn();
};

#endif // BOLUS_H
