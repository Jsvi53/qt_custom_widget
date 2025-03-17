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
    // 创建极坐标图表
    polarDiagram = new QPolarChart();

    // 创建数据系列
    polarDiagramSeries = new QLineSeries();
    polarDiagram->addSeries(polarDiagramSeries);

    // 图表设置
    polarDiagram->legend()->hide();
    // 背景灰色
    polarDiagram->setBackgroundVisible(true);
    polarDiagram->setBackgroundBrush(QBrush(Qt::lightGray));
    polarDiagram->setMargins(QMargins(0, 0, 0, 0));

    // 创建角度轴
    angularAxis = new QValueAxis();
    angularAxis->setRange(0, 360);         // 角度范围：0°到360°
    angularAxis->setTickCount(9);          // 刻度数量
    angularAxis->setLabelFormat("%.1f°");  // 标签格式
    polarDiagram->addAxis(angularAxis, QPolarChart::PolarOrientationAngular);
    polarDiagramSeries->attachAxis(angularAxis);

    // 创建幅度轴
    radialAxis = new QValueAxis();
    radialAxis->setRange(0, 10);  // 幅度范围：0到10
    radialAxis->setTickCount(6);  // 刻度数量
    polarDiagram->addAxis(radialAxis, QPolarChart::PolarOrientationRadial);
    polarDiagramSeries->attachAxis(radialAxis);

    // 创建图表视图
    polarDiagramView = new QChartView(polarDiagram);
    polarDiagramView->setRenderHint(QPainter::Antialiasing);

    // 将图表视图添加到布局中
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(polarDiagramView);
    setLayout(layout);  // 设置布局
}