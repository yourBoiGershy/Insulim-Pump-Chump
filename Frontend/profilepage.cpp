#include "profilepage.h"
#include "ui_profilepage.h"
#include <QDebug>

profilepage::profilepage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::profilepage)
{
    ui->setupUi(this);

    // Connect buttons
    connect(ui->BackBtn, &QPushButton::clicked, this, &profilepage::handleBackBtn);
    connect(ui->CreateBtn, &QPushButton::clicked, this, &profilepage::handleCreateProfile);
    connect(ui->ActivateBtn, &QPushButton::clicked, this, &profilepage::handleActivateProfile);
    connect(ui->EditBtn, &QPushButton::clicked, this, &profilepage::handleEditProfile);
    connect(ui->DeleteBtn, &QPushButton::clicked, this, &profilepage::handleDeleteProfile);

    // Connect list widget selection change
    connect(ui->ProfilesList, &QListWidget::currentRowChanged, this, &profilepage::handleProfileSelectionChanged);

    // Load profiles
    loadProfiles();
}

profilepage::~profilepage()
{
    delete ui;
}

void profilepage::showEvent(QShowEvent *event)
{
    // Call the base class implementation
    QWidget::showEvent(event);

    // Refresh the profiles list whenever the page is shown
    loadProfiles();
}

void profilepage::handleBackBtn(){
    emit backBtnPressed();
}

void profilepage::handleCreateProfile(){
    emit createBtnPressed();
}

void profilepage::loadProfiles() {
    // Clear the list
    ui->ProfilesList->clear();

    // Get all profiles
    profiles = profileManager.getAllProfiles();

    // Debug output
    qDebug() << "Loaded" << profiles.size() << "profiles";

    // Add profiles to the list
    for (const Profile &profile : profiles) {
        QListWidgetItem *item = new QListWidgetItem(profile.getName());

        // Mark active profile with an asterisk
        if (profile.isActive()) {
            item->setText(profile.getName() + " (Active)");
            item->setForeground(Qt::blue);
        }

        ui->ProfilesList->addItem(item);
        qDebug() << "Added profile:" << profile.getName();
    }

    // Enable/disable buttons based on selection
    bool hasSelection = (ui->ProfilesList->currentRow() >= 0);
    ui->ActivateBtn->setEnabled(hasSelection);
    ui->EditBtn->setEnabled(hasSelection);
    ui->DeleteBtn->setEnabled(hasSelection);

    // Update profile details
    updateProfileDetails();
}

void profilepage::updateProfileDetails() {
    int currentRow = ui->ProfilesList->currentRow();

    if (currentRow >= 0 && currentRow < profiles.size()) {
        const Profile &profile = profiles[currentRow];
        QString details = "Name: " + profile.getName() + "\n";

        if (profile.isActive()) {
            details += "Status: Active\n";
        } else {
            details += "Status: Inactive\n";
        }

        details += "Created: " + profile.getCreatedDate().toString("yyyy-MM-dd") + "\n";
        details += "Time Segments: " + QString::number(profile.getTimeSegments().size()) + "\n";

        // Add current settings
        details += "Current Settings:\n";
        details += "- Insulin-to-Carb Ratio: 1:" + QString::number(profile.getCurrentInsulinToCarbRatio(), 'f', 1) + "\n";
        details += "- Correction Factor: 1:" + QString::number(profile.getCurrentCorrectionFactor(), 'f', 1) + "\n";
        details += "- Target Glucose: " + QString::number(profile.getCurrentTargetGlucose(), 'f', 1) + " mmol/L\n";
        details += "- Basal Rate: " + QString::number(profile.getCurrentBasalRate(), 'f', 2) + " U/hr";

        ui->ProfileDetailsLabel->setText(details);
    } else {
        ui->ProfileDetailsLabel->setText("Select a profile to see details");
    }
}

void profilepage::handleActivateProfile() {
    int currentRow = ui->ProfilesList->currentRow();

    if (currentRow >= 0 && currentRow < profiles.size()) {
        const Profile &profile = profiles[currentRow];

        // Set as active profile
        if (profileManager.setActiveProfile(profile.getName())) {
            QMessageBox::information(this, "Profile Activated",
                                   "Profile '" + profile.getName() + "' has been activated.");

            // Reload profiles to update the UI
            loadProfiles();
        } else {
            QMessageBox::warning(this, "Activation Failed",
                               "Failed to activate profile '" + profile.getName() + "'.");
        }
    }
}

void profilepage::handleEditProfile() {
    int currentRow = ui->ProfilesList->currentRow();

    if (currentRow >= 0 && currentRow < profiles.size()) {
        const Profile &profile = profiles[currentRow];

        // Emit signal to request profile editing
        emit editProfileRequested(profile.getName());
    }
}

void profilepage::handleDeleteProfile() {
    int currentRow = ui->ProfilesList->currentRow();

    if (currentRow >= 0 && currentRow < profiles.size()) {
        const Profile &profile = profiles[currentRow];

        // Confirm deletion
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirm Deletion",
                                                              "Are you sure you want to delete profile '" + profile.getName() + "'?",
                                                              QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            // Delete profile
            if (profileManager.deleteProfile(profile.getName())) {
                QMessageBox::information(this, "Profile Deleted",
                                       "Profile '" + profile.getName() + "' has been deleted.");

                // Reload profiles to update the UI
                loadProfiles();
            } else {
                QMessageBox::warning(this, "Deletion Failed",
                                   "Failed to delete profile '" + profile.getName() + "'. Active profiles cannot be deleted.");
            }
        }
    }
}

void profilepage::handleProfileSelectionChanged() {
    // Enable/disable buttons based on selection
    bool hasSelection = (ui->ProfilesList->currentRow() >= 0);
    ui->ActivateBtn->setEnabled(hasSelection);
    ui->EditBtn->setEnabled(hasSelection);
    ui->DeleteBtn->setEnabled(hasSelection);

    // Update profile details
    updateProfileDetails();
}
