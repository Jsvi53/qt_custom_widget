/*** 
 * @Date: 2025-03-04 10:13:11
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-04 16:20:58
 * @FilePath: \qt_custom_widget\src\chart\balancingshowphasechart.cpp
 */
#include "chart/balancingshowphasechart.h"
#include "ui_balancingshowphasechart.h"
#include "chart/balancingphasechart.h"


BalancingShowPhaseChart::BalancingShowPhaseChart(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BalancingShowPhaseChart)
{
    ui->setupUi(this);
    phaseChart = new BalancingPhaseChart(this);
    phaseChart->resize(640, 480);
    phaseChart->show();

    // 添加示例数据
    phaseChart->addDataPoint(0, 5);
    phaseChart->addDataPoint(450, 2);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(phaseChart);
    setLayout(layout);
}

BalancingShowPhaseChart::~BalancingShowPhaseChart()
{
    delete ui;
}
