#ifndef BARCHARTSHOWWINDOW_H
#define BARCHARTSHOWWINDOW_H

#include <QFrame>
#include "barchart.h"

namespace Ui {
class BarChartShowWindow;
}

class BarChartShowWindow : public QFrame
{
    Q_OBJECT

public:
    explicit BarChartShowWindow(QWidget *parent = nullptr);
    ~BarChartShowWindow();

private:
    Ui::BarChartShowWindow *ui;
    BalancingBarChart *bar;
};

#endif // BARCHARTSHOWWINDOW_H
