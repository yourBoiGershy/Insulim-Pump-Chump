#ifndef PROFILESPAGE_H
#define PROFILESPAGE_H

#include <QWidget>

namespace Ui {
class profiles;
}

class profiles : public QWidget
{
    Q_OBJECT

public:
    explicit profiles(QWidget *parent = nullptr);
    ~profilesPage();


private:
    Ui::profiles *ui;
};

#endif // PROFILESPAGE_H
