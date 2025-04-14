#ifndef PROFILEEDITOR_H
#define PROFILEEDITOR_H

#include <QWidget>
#include <QMessageBox>
#include <QTimeEdit>
#include <QDoubleSpinBox>
#include <QPushButton>
#include "profile.h"
#include "profilemanager.h"

namespace Ui {
class ProfileEditor;
}

class ProfileEditor : public QWidget
{
    Q_OBJECT

public:
    explicit ProfileEditor(QWidget *parent = nullptr);
    ~ProfileEditor();
    
    void setProfileManager(ProfileManager *manager);
    void createNewProfile();
    void editProfile(const QString &profileName);

signals:
    void backBtnPressed();
    void profileSaved();

private slots:
    void handleBackBtn();
    void handleSaveBtn();
    void handleAddSegmentBtn();
    void handleRemoveSegmentBtn();
    void handleSegmentSelectionChanged();

private:
    Ui::ProfileEditor *ui;
    ProfileManager *profileManager;
    Profile currentProfile;
    bool isNewProfile;
    
    // Dynamic widgets for time segments
    QVector<QWidget*> segmentWidgets;
    
    void setupUI();
    void loadProfile();
    void updateSegmentsList();
    void clearSegmentWidgets();
    void createSegmentWidgets();
    void validateAndSaveProfile();
};

#endif // PROFILEEDITOR_H
