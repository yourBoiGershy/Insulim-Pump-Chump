#include "profileeditor.h"
#include "ui_profileeditor.h"

ProfileEditor::ProfileEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProfileEditor),
    profileManager(nullptr),
    isNewProfile(true)
{
    ui->setupUi(this);
    
    // Connect buttons
    connect(ui->BackBtn, &QPushButton::clicked, this, &ProfileEditor::handleBackBtn);
    connect(ui->SaveBtn, &QPushButton::clicked, this, &ProfileEditor::handleSaveBtn);
    connect(ui->AddSegmentBtn, &QPushButton::clicked, this, &ProfileEditor::handleAddSegmentBtn);
    connect(ui->RemoveSegmentBtn, &QPushButton::clicked, this, &ProfileEditor::handleRemoveSegmentBtn);
    
    // Connect list widget selection change
    connect(ui->SegmentsList, &QListWidget::currentRowChanged, this, &ProfileEditor::handleSegmentSelectionChanged);
    
    // Setup UI
    setupUI();
}

ProfileEditor::~ProfileEditor()
{
    delete ui;
}

void ProfileEditor::setProfileManager(ProfileManager *manager)
{
    profileManager = manager;
}

void ProfileEditor::createNewProfile()
{
    isNewProfile = true;
    ui->TitleLabel->setText("CREATE PROFILE");
    
    // Create a new profile
    currentProfile = Profile();
    
    // Update UI
    ui->NameEdit->setText("");
    ui->NameEdit->setEnabled(true);
    
    // Update segments list
    updateSegmentsList();
}

void ProfileEditor::editProfile(const QString &profileName)
{
    if (!profileManager) {
        return;
    }
    
    isNewProfile = false;
    ui->TitleLabel->setText("EDIT PROFILE");
    
    // Load the profile
    currentProfile = profileManager->getProfile(profileName);
    
    // Update UI
    ui->NameEdit->setText(currentProfile.getName());
    ui->NameEdit->setEnabled(false); // Don't allow changing the name when editing
    
    // Update segments list
    updateSegmentsList();
}

void ProfileEditor::setupUI()
{
    // Initially disable the remove segment button
    ui->RemoveSegmentBtn->setEnabled(false);
    
    // Initially disable the segment details widget
    ui->SegmentDetailsWidget->setEnabled(false);
}

void ProfileEditor::updateSegmentsList()
{
    // Clear the list
    ui->SegmentsList->clear();
    
    // Add segments to the list
    const QVector<TimeSegment> &segments = currentProfile.getTimeSegments();
    for (int i = 0; i < segments.size(); ++i) {
        const TimeSegment &segment = segments[i];
        QString label = segment.startTime.toString("HH:mm") + " - ";
        
        // If there's a next segment, use its start time as the end time
        if (i < segments.size() - 1) {
            label += segments[i+1].startTime.toString("HH:mm");
        } else {
            // For the last segment, the end time is the start time of the first segment
            label += segments[0].startTime.toString("HH:mm");
        }
        
        ui->SegmentsList->addItem(label);
    }
    
    // Select the first segment if available
    if (ui->SegmentsList->count() > 0) {
        ui->SegmentsList->setCurrentRow(0);
    } else {
        // Disable segment details if no segments
        ui->SegmentDetailsWidget->setEnabled(false);
        ui->RemoveSegmentBtn->setEnabled(false);
    }
}

void ProfileEditor::handleBackBtn()
{
    emit backBtnPressed();
}

void ProfileEditor::handleSaveBtn()
{
    validateAndSaveProfile();
}

void ProfileEditor::handleAddSegmentBtn()
{
    // Create a new time segment
    TimeSegment newSegment;
    
    // Set default values
    newSegment.startTime = QTime(12, 0); // Noon
    newSegment.insulinToCarbRatio = 10.0;
    newSegment.correctionFactor = 2.0;
    newSegment.targetGlucose = 5.5;
    newSegment.basalRate = 1.0;
    
    // Add to profile
    currentProfile.addTimeSegment(newSegment);
    
    // Update UI
    updateSegmentsList();
    
    // Select the new segment
    ui->SegmentsList->setCurrentRow(ui->SegmentsList->count() - 1);
}

void ProfileEditor::handleRemoveSegmentBtn()
{
    int currentRow = ui->SegmentsList->currentRow();
    
    if (currentRow >= 0) {
        // Don't allow removing the last segment
        if (currentProfile.getTimeSegments().size() <= 1) {
            QMessageBox::warning(this, "Cannot Remove", "You must have at least one time segment in a profile.");
            return;
        }
        
        // Remove the segment
        currentProfile.removeTimeSegment(currentRow);
        
        // Update UI
        updateSegmentsList();
    }
}

void ProfileEditor::handleSegmentSelectionChanged()
{
    int currentRow = ui->SegmentsList->currentRow();
    
    // Enable/disable buttons based on selection
    ui->RemoveSegmentBtn->setEnabled(currentRow >= 0);
    ui->SegmentDetailsWidget->setEnabled(currentRow >= 0);
    
    if (currentRow >= 0 && currentRow < currentProfile.getTimeSegments().size()) {
        // Get the selected segment
        const TimeSegment &segment = currentProfile.getTimeSegments()[currentRow];
        
        // Update the segment details
        ui->StartTimeEdit->setTime(segment.startTime);
        ui->ICRSpinBox->setValue(segment.insulinToCarbRatio);
        ui->CFSpinBox->setValue(segment.correctionFactor);
        ui->TargetBGSpinBox->setValue(segment.targetGlucose);
        ui->BasalRateSpinBox->setValue(segment.basalRate);
        
        // Connect value changes to update the segment
        connect(ui->StartTimeEdit, &QTimeEdit::timeChanged, [this, currentRow](const QTime &time) {
            if (currentRow >= 0 && currentRow < currentProfile.getTimeSegments().size()) {
                TimeSegment segment = currentProfile.getTimeSegments()[currentRow];
                segment.startTime = time;
                currentProfile.updateTimeSegment(currentRow, segment);
                updateSegmentsList();
            }
        });
        
        connect(ui->ICRSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), [this, currentRow](double value) {
            if (currentRow >= 0 && currentRow < currentProfile.getTimeSegments().size()) {
                TimeSegment segment = currentProfile.getTimeSegments()[currentRow];
                segment.insulinToCarbRatio = value;
                currentProfile.updateTimeSegment(currentRow, segment);
            }
        });
        
        connect(ui->CFSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), [this, currentRow](double value) {
            if (currentRow >= 0 && currentRow < currentProfile.getTimeSegments().size()) {
                TimeSegment segment = currentProfile.getTimeSegments()[currentRow];
                segment.correctionFactor = value;
                currentProfile.updateTimeSegment(currentRow, segment);
            }
        });
        
        connect(ui->TargetBGSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), [this, currentRow](double value) {
            if (currentRow >= 0 && currentRow < currentProfile.getTimeSegments().size()) {
                TimeSegment segment = currentProfile.getTimeSegments()[currentRow];
                segment.targetGlucose = value;
                currentProfile.updateTimeSegment(currentRow, segment);
            }
        });
        
        connect(ui->BasalRateSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), [this, currentRow](double value) {
            if (currentRow >= 0 && currentRow < currentProfile.getTimeSegments().size()) {
                TimeSegment segment = currentProfile.getTimeSegments()[currentRow];
                segment.basalRate = value;
                currentProfile.updateTimeSegment(currentRow, segment);
            }
        });
    }
}

void ProfileEditor::validateAndSaveProfile()
{
    if (!profileManager) {
        QMessageBox::warning(this, "Error", "Profile manager not set.");
        return;
    }
    
    // Validate profile name
    QString name = ui->NameEdit->text().trimmed();
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Profile name cannot be empty.");
        return;
    }
    
    // Set profile name
    currentProfile.setName(name);
    
    // Save profile
    if (profileManager->saveProfile(currentProfile)) {
        QMessageBox::information(this, "Profile Saved", "Profile '" + name + "' has been saved.");
        emit profileSaved();
    } else {
        QMessageBox::warning(this, "Save Failed", "Failed to save profile '" + name + "'.");
    }
}
