#ifndef PROFILEPAGE_H
#define PROFILEPAGE_H

#include <QWidget>
#include <QMessageBox>
#include <QShowEvent>
#include "profilemanager.h"

namespace Ui {
class profilepage;
}

class profilepage : public QWidget
{
    Q_OBJECT

public:
    explicit profilepage(QWidget *parent = nullptr);
    ~profilepage();

    // Call this when the page is shown to refresh the profiles list
    void showEvent(QShowEvent *event) override;

private:
    Ui::profilepage *ui;
    ProfileManager profileManager;
    QVector<Profile> profiles;

    void loadProfiles();
    void updateProfileDetails();

signals:
    void backBtnPressed();
    void createBtnPressed();
    void editProfileRequested(const QString &profileName);

private slots:
    void handleBackBtn();
    void handleCreateProfile();
    void handleActivateProfile();
    void handleEditProfile();
    void handleDeleteProfile();
    void handleProfileSelectionChanged();
};

#endif // PROFILEPAGE_H
