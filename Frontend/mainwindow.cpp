#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "def.h"
#include "home.h"
#include "bolus.h"
#include "options.h"
#include "profilepage.h"
#include "createprofile.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // initialize pages
    homePage = new home(this);

    bolusPage = new bolus(this);

    optionsPage = new options(this);

    profilePage = new profilepage(this);

    createPage = new createprofile(this);


    // add ui files to stackedwidget
    ui->stackedWidget->addWidget(homePage);
    ui->stackedWidget->addWidget(bolusPage);
    ui->stackedWidget->addWidget(optionsPage);
    ui->stackedWidget->addWidget(profilePage);
    ui->stackedWidget->addWidget(createPage);

    // default to homepage
    ui->stackedWidget->setCurrentWidget(homePage);

    connect(this, &MainWindow::powerBtnPressed, homePage, &home::handlePowerBtn);

    // connect to home buttons
    connect(homePage, &home::bolusBtnPressed, this, &MainWindow::switchToBolus);
    connect(homePage, &home::optionsBtnPressed, this, &MainWindow::switchToOptions);

    // connect to bolus buttons
    connect(bolusPage, &bolus::logoBtnPressed, this, &MainWindow::switchToHome);

    // connect to options buttons
    connect(optionsPage, &options::logoBtnPressed, this, &MainWindow::switchToHome);
    connect(optionsPage, &options::powerBtnPressed, this, &MainWindow::switchToHome);
    connect(optionsPage, &options::profileBtnPressed, this, &MainWindow::switchToProfiles);
    connect(optionsPage, &options::sleepBtnPressed, this, &MainWindow::switchToProfiles);

    connect(profilePage, &profilepage::backBtnPressed, this, &MainWindow::switchToOptions);
    connect(profilePage, &profilepage::createBtnPressed, this, &MainWindow::switchToCreatePage);

    connect(this, &MainWindow::powerBtnPressed, homePage, &home::handlePowerBtn);

    connect(createPage, &createprofile::backBtnPressed, this, &MainWindow::switchToProfiles);

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
    ui->stackedWidget->setCurrentWidget(profilePage);
}

void MainWindow::switchToCreatePage(){
    ui->stackedWidget->setCurrentWidget(createPage);

}

void MainWindow::handlePowerBtn(){
    switchToHome();
    emit powerBtnPressed();
}
