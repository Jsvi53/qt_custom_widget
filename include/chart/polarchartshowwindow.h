#ifndef POLARCHARTSHOWWINDOW_H
#define POLARCHARTSHOWWINDOW_H

#include <QFrame>
#include "chart/polarchart.h"

namespace Ui {
class PolarChartShowWindow;
}

class PolarChartShowWindow : public QFrame
{
    Q_OBJECT

public:
    explicit PolarChartShowWindow(QWidget *parent = nullptr);
    ~PolarChartShowWindow();

private:
    Ui::PolarChartShowWindow *ui;
    BalancingPolarChart *m_chart;
};

#endif // POLARCHARTSHOWWINDOW_H
