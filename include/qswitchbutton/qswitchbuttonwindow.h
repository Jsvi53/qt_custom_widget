#ifndef QSWITCHBUTTONWINDOW_H
#define QSWITCHBUTTONWINDOW_H

#include <QWidget>

namespace Ui {
class QSwitchButtonWindow;
}

class QSwitchButtonWindow : public QWidget
{
    Q_OBJECT

public:
    explicit QSwitchButtonWindow(QWidget *parent = nullptr);
    ~QSwitchButtonWindow();

private:
    Ui::QSwitchButtonWindow *ui;
};

#endif // QSWITCHBUTTONWINDOW_H