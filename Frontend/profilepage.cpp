#include "profilepage.h"
#include "ui_profilepage.h"

profilepage::profilepage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::profilepage)
{
    ui->setupUi(this);

    connect(ui->BackBtn, &QPushButton::clicked, this, &profilepage::handleBackBtn);
    connect(ui->CreateBtn, &QPushButton::clicked, this, &profilepage::handleCreateProfile);

}

profilepage::~profilepage()
{
    delete ui;
}

void profilepage::handleBackBtn(){
    emit backBtnPressed();
}

void profilepage::handleCreateProfile(){
    emit createBtnPressed();
}
