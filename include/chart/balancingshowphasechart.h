/*** 
 * @Date: 2025-03-04 10:13:11
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-04 11:14:07
 * @FilePath: \qt_custom_widget\include\chart\balancingshowphasechart.h
 */
#ifndef BALANCINGPHASECHART_H
#define BALANCINGPHASECHART_H

#include <QWidget>
#include "chart/balancingphasechart.h"

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
