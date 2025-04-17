#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "def.h"
#include "home.h"
#include "bolus.h"
#include "options.h"
#include "profilepage.h"
#include "profileeditor.h"
#include <QInputDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // initialize pages

    Profile activeProfile = Profile::getActive();

    homePage = new home(this, activeProfile);

    bolusPage = new bolus(this);

    optionsPage = new options(this);

    profilePage = new profilepage(this);

    profileEditor = new ProfileEditor(this);
    profileEditor->setProfileManager(&profileManager);


    // add ui files to stackedwidget
    ui->stackedWidget->addWidget(homePage);
    ui->stackedWidget->addWidget(bolusPage);
    ui->stackedWidget->addWidget(optionsPage);
    ui->stackedWidget->addWidget(profilePage);
    ui->stackedWidget->addWidget(profileEditor);

    // default to homepage
    ui->stackedWidget->setCurrentWidget(homePage);

    // connect to home buttons
    connect(homePage, &home::bolusBtnPressed, this, &MainWindow::switchToBolus);
    connect(homePage, &home::optionsBtnPressed, this, &MainWindow::switchToOptions);

    // connect to bolus buttons
    connect(bolusPage, &bolus::logoBtnPressed, this, &MainWindow::switchToHome);
    connect(bolusPage, &bolus::insulinAdministered, homePage, &home::receiveInsulin);

    // connect to options buttons
    connect(optionsPage, &options::logoBtnPressed, this, &MainWindow::switchToHome);
    connect(optionsPage, &options::powerBtnPressed, this, &MainWindow::handleOptionsPowerBtn);
    connect(optionsPage, &options::profileBtnPressed, this, &MainWindow::switchToProfiles);

    connect(profilePage, &profilepage::backBtnPressed, this, &MainWindow::switchToOptions);
    connect(profilePage, &profilepage::createBtnPressed, this, &MainWindow::switchToProfileEditor);
    connect(profilePage, &profilepage::editProfileRequested, this, &MainWindow::switchToEditProfile);

    connect(profileEditor, &ProfileEditor::backBtnPressed, this, &MainWindow::switchToProfiles);
    connect(profileEditor, &ProfileEditor::profileSaved, this, &MainWindow::switchToProfiles);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::switchToBolus(){
    ui->stackedWidget->setCurrentWidget(bolusPage);
}

void MainWindow::switchToOptions(){
    ui->stackedWidget->setCurrentWidget(optionsPage);
}

void MainWindow::switchToHome(){
    ui->stackedWidget->setCurrentWidget(homePage);
}

void MainWindow::switchToProfiles(){
    // check pin
    bool ok;
    QString pin = QInputDialog::getText(this, "Please enter your PIN", "Hint: its 1234", QLineEdit::Password, "", &ok);


    if(ok){
        if(pin == "1234"){
            // Set the current widget to the profile page
            ui->stackedWidget->setCurrentWidget(profilePage);
        } else{
            QMessageBox::warning(this, "Access denied", "Incorrect PIN.");
        }
    }
}

void MainWindow::switchToProfileEditor(){
    profileEditor->createNewProfile();
    ui->stackedWidget->setCurrentWidget(profileEditor);
}

void MainWindow::switchToEditProfile(const QString &profileName){
    profileEditor->editProfile(profileName);
    ui->stackedWidget->setCurrentWidget(profileEditor);
}

void MainWindow::handleOptionsPowerBtn(){
    homePage->handlePowerBtn();
    ui->stackedWidget->setCurrentWidget(homePage);
}
