#include "profilesPage.h"
#include "ui_profiles.h"

profilesPage::profiles(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::profiles)
{
    ui->setupUi(this);
}

profilesPage::~profiles()
{
    delete ui;
}
