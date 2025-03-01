#ifndef SWITCHBUTTONSHOWWINDOW_H
#define SWITCHBUTTONSHOWWINDOW_H

#include <QFrame>

namespace Ui {
class SwitchButtonShowWindow;
}

class SwitchButtonShowWindow : public QFrame
{
    Q_OBJECT

public:
    explicit SwitchButtonShowWindow(QWidget *parent = nullptr);
    ~SwitchButtonShowWindow();

private:
    Ui::SwitchButtonShowWindow *ui;
};

#endif // SWITCHBUTTONSHOWWINDOW_H
