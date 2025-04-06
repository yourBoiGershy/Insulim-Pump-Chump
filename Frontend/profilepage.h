#ifndef PROFILEPAGE_H
#define PROFILEPAGE_H

#include <QWidget>

namespace Ui {
class profilepage;
}

class profilepage : public QWidget
{
    Q_OBJECT

public:
    explicit profilepage(QWidget *parent = nullptr);
    ~profilepage();

private:
    Ui::profilepage *ui;

signals:
    void backBtnPressed();
    void createBtnPressed();

private slots:
    void handleBackBtn();
    void handleCreateProfile();
};

#endif // PROFILEPAGE_H
