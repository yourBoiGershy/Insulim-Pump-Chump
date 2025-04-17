#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <home.h>
#include <bolus.h>
#include <options.h>
#include <profilepage.h>
#include <profileeditor.h>
#include "profilemanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    home *homePage;

    bolus *bolusPage;

    options *optionsPage;

    profilepage *profilePage;

    ProfileEditor *profileEditor;

    ProfileManager profileManager;

signals:
    void powerBtnPressed();

private slots:
    void switchToBolus();
    void switchToOptions();
    void switchToHome();
    void switchToProfiles();
    void switchToProfileEditor();
    void switchToEditProfile(const QString &profileName);
    void handleOptionsPowerBtn();

};
#endif // MAINWINDOW_H
