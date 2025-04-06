#ifndef BOLUS_H
#define BOLUS_H

#include <QWidget>

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

private slots:
    void handleCalculationBtn();
    void handleLogoBtn();
};

#endif // BOLUS_H
