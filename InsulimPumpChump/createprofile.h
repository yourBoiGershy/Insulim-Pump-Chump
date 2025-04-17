#ifndef CREATEPROFILE_H
#define CREATEPROFILE_H

#include <QWidget>

namespace Ui {
class createprofile;
}

class createprofile : public QWidget
{
    Q_OBJECT

public:
    explicit createprofile(QWidget *parent = nullptr);
    ~createprofile();

private:
    Ui::createprofile *ui;

signals:
    void backBtnPressed();

private slots:
    void handleBackBtn();
};

#endif // CREATEPROFILE_H
