#ifndef HOME_H
#define HOME_H

#include <QWidget>
#include <QTimer>

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
    int batteryLevel;
    bool powerOn;

signals:
    void bolusBtnPressed();
    void optionsBtnPressed();

public slots:
    void handlePowerBtn();

private slots:
    void handleChargeBtn();
    void handleBolusBtn();
    void handleOptionsBtn();
    void handleBatteryTime();
};

#endif // HOME_H
