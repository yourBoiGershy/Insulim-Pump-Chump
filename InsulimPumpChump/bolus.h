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

signals:
    void logoBtnPressed();
    void insulinAdministered(double units);

private slots:
    void handleCalculationBtn();
    void handleLogoBtn();
};

#endif // BOLUS_H
