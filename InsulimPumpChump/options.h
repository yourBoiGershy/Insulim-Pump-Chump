#ifndef OPTIONS_H
#define OPTIONS_H

#include <QWidget>

namespace Ui {
class options;
}

class options : public QWidget
{
    Q_OBJECT

public:
    explicit options(QWidget *parent = nullptr);
    ~options();

private:
    Ui::options *ui;

signals:
    void logoBtnPressed();
    void powerBtnPressed();
    void profileBtnPressed();
    void sleepBtnPressed();

private slots:
    void handleLogoBtn();
    void handleProfileBtn();
    void handlePowerBtn();
    void handleSleepBtn();
    void handlePowerOn();
};

#endif // OPTIONS_H
