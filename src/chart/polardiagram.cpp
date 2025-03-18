/***
 * @Date: 2025-03-18 10:17:59
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-18 15:04:58
 * @FilePath: \qt_custom_widget\src\chart\polardiagram.cpp
 */
/***
 * @Date: 2025-03-18 08:36:17
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-18 10:59:23
 * @FilePath: \qt_custom_widget\src\chart\polardiagram.cpp
 */
#include "chart/polardiagram.h"

PolarDiagram::PolarDiagram(QWidget *parent) : QWidget(parent)
{
    initChart();
}

PolarDiagram::~PolarDiagram()
{
}

void PolarDiagram::initChart()
{
    // 创建图表元素
    polarDiagram       = new QPolarChart();
    angularAxis        = new QValueAxis();
    radialAxis         = new QValueAxis();
    polarDiagramSeries = new QLineSeries();
    polarDiagramView   = new QChartView(polarDiagram);

    // 添加元素
    polarDiagram->addSeries(polarDiagramSeries);
    polarDiagram->addAxis(angularAxis, QPolarChart::PolarOrientationAngular);
    polarDiagram->addAxis(radialAxis, QPolarChart::PolarOrientationRadial);
    polarDiagramSeries->attachAxis(angularAxis);
    polarDiagramSeries->attachAxis(radialAxis);

    // 设置图表
    polarDiagram->legend()->hide();
    polarDiagram->setBackgroundVisible(false);                                // 背景透明
    polarDiagram->setPlotAreaBackgroundBrush(QBrush(QColor(240, 240, 240)));  // 设置图形区域的填充颜色
    polarDiagram->setPlotAreaBackgroundVisible(true);                         // 显示图形区域背景
    polarDiagram->setBackgroundRoundness(0);                                  // 设置背景圆角
    polarDiagram->setMargins(QMargins(0, 0, 0, 0));

    // 设置角度轴
    angularAxis->setRange(0, 360);      // 角度范围：0°到360°
    angularAxis->setTickCount(9);       // 刻度数量
    angularAxis->setLabelFormat("%d");  // 使用 Unicode 编码设置标签格式
    angularAxis->setLabelsFont(QFont("Microsoft YaHei", 12));

    // 创建幅度轴
    radialAxis->setRange(0, 10);  // 幅度范围：0到10
    radialAxis->setTickCount(6);  // 刻度数量
    radialAxis->setLabelsFont(QFont("Microsoft YaHei", 12));

    // 设置图表网格
    angularAxis->setGridLineVisible(true);
    radialAxis->setGridLineVisible(true);
    QPen gridPen(Qt::gray, 1, Qt::DotLine);  // 设置为虚线, 颜色为灰色, 宽度为1, 线帽为圆角
    angularAxis->setGridLinePen(gridPen);
    radialAxis->setGridLinePen(gridPen);

    // 创建图表视图
    polarDiagramView->setRenderHint(QPainter::Antialiasing);
    QVBoxLayout *layout = new QVBoxLayout(this);  // 将图表视图添加到布局中
    layout->addWidget(polarDiagramView);
    setLayout(layout);  // 设置布局
}