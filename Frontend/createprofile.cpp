#include "createprofile.h"
#include "ui_createprofile.h"

createprofile::createprofile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::createprofile)
{
    ui->setupUi(this);

    connect(ui->BackBtn, &QPushButton::clicked, this, &createprofile::handleBackBtn);
}

createprofile::~createprofile()
{
    delete ui;
}

void createprofile::handleBackBtn(){
    emit backBtnPressed();
}
