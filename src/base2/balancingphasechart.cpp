#include "balancingphasechart.h"
#include <cmath>

BalancingPhaseChart::BalancingPhaseChart(QWidget *parent)
    : QWidget(parent)
{
    initChart();
}

BalancingPhaseChart::~BalancingPhaseChart()
{
    delete phaseChart;
    delete phaseChartView;
    delete angularAxis;
    delete radialAxis;
    delete phaseLineSeries;
    delete phaseScatterSeries;
}

void BalancingPhaseChart::initChart()
{
    // 创建极坐标图表
    phaseChart = new QPolarChart();
    phaseChart->setTitle("Balancing Phase Chart");
    phaseChart->legend()->setVisible(false);
    phaseChart->legend()->setAlignment(Qt::AlignBottom);

    // 绘图区域背景色为灰色, 透明度为 0.5
    phaseChart->setPlotAreaBackgroundBrush(QBrush(QColor(127, 127, 127, 20)));
    phaseChart->setPlotAreaBackgroundVisible(true);

    // 创建直线系列
    phaseLineSeries = new QLineSeries();
    phaseChart->addSeries(phaseLineSeries);

    // 创建散点系列
    phaseScatterSeries = new QScatterSeries();
    phaseScatterSeries->setMarkerSize(20); // 设置标记大小
    phaseScatterSeries->setMarkerShape(QScatterSeries::MarkerShapeCircle); // 设置标记形状
    phaseScatterSeries->setColor(QColor(0, 220, 0)); // 设置颜色
    phaseChart->addSeries(phaseScatterSeries);

    // 创建径向轴
    radialAxis = new QValueAxis();
    radialAxis->setRange(0, 10);
    radialAxis->setTickCount(6);    // 刻度数量
    phaseChart->addAxis(radialAxis, QPolarChart::PolarOrientationRadial);   // 添加径向轴
    phaseLineSeries->attachAxis(radialAxis);
    phaseScatterSeries->attachAxis(radialAxis);

    // 创建角度轴
    angularAxis = new QCategoryAxis();
    angularAxis->setRange(-90, 270);
    angularAxis->setStartValue(-90);    // 设置起始值，使其水平向右
    angularAxis->append("45°", -45);    // 标签顺序一致
    angularAxis->append("0°", 0);
    angularAxis->append("315°", 45);
    angularAxis->append("270°", 90);
    angularAxis->append("225°", 135);
    angularAxis->append("180°", 180);
    angularAxis->append("135°", 225);
    angularAxis->append("90°", 270);

    angularAxis->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue); // 设置标签位置
    phaseChart->addAxis(angularAxis, QPolarChart::PolarOrientationAngular);
    phaseLineSeries->attachAxis(angularAxis);
    phaseScatterSeries->attachAxis(angularAxis);

    // 创建图表视图, 添加到布局
    phaseChartView = new QChartView(phaseChart);
    phaseChartView->setRenderHint(QPainter::Antialiasing);
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(phaseChartView);
    setLayout(layout);
}

// 添加数据点
void BalancingPhaseChart::addDataPoint(double angle, double magnitude)
{
    // 添加数据点到直线系列
    angle = fmod(angle, 360.0); // 将角度限制在 -360 到 360 之间
    if (angle < -270) {
        angle = -angle - 360;
    } else if (angle <= 90) {
        angle *= -1;
    } else if (angle <= 270) {
        angle = 360 - angle;
    }

    phaseLineSeries->append(angle, magnitude);

}

// 添加散点
void BalancingPhaseChart::addScatterPoint(double angle, double magnitude)
{
    phaseScatterSeries->append(angle, magnitude); // 添加散点
}

// 清除所有数据
void BalancingPhaseChart::clearData()
{
    phaseLineSeries->clear(); // 清除所有数据
    phaseScatterSeries->clear(); // 清除所有散点
}