#ifndef SWITCHBUTTONSHOWWINDOW_H
#define SWITCHBUTTONSHOWWINDOW_H

#include <QFrame>
#include "qswitchbutton/qswitchbutton.h"

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
    SwitchButton *m_switchButton;
};

#endif // SWITCHBUTTONSHOWWINDOW_H
