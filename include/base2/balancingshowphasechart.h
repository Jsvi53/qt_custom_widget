#ifndef BALANCINGPHASECHART_H
#define BALANCINGPHASECHART_H

#include <QWidget>
#include "balancingphasechart.h"

namespace Ui {
class BalancingShowPhaseChart;
}

class BalancingShowPhaseChart : public QWidget
{
    Q_OBJECT

public:
    explicit BalancingShowPhaseChart(QWidget *parent = nullptr);
    ~BalancingShowPhaseChart();


private:
    Ui::BalancingShowPhaseChart *ui;
    BalancingPhaseChart *phaseChart;
};

#endif // BALANCINGSHOWPHASECHART_H
