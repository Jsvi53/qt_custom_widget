#include "chart/polarchart.h"

BalancingPolarChart::BalancingPolarChart(QWidget *parent) : QFrame(parent)
{
    initChart();
}

BalancingPolarChart::~BalancingPolarChart()
{
    // 清理资源
    delete m_chart;
    delete m_chartView;
    delete m_series;
    delete m_angularAxis;
    delete m_radialAxis;
}

void BalancingPolarChart::initChart()
{
    // 创建极坐标图表
    m_chart = new QPolarChart();
    m_chart->setTitle("Dynamic Balancing Phase Diagram");

    // 创建数据系列
    m_series = new QLineSeries();
    m_chart->addSeries(m_series);

    // 创建角度轴
    m_angularAxis = new QValueAxis();
    m_angularAxis->setRange(0, 360); // 角度范围：0°到360°
    m_angularAxis->setTickCount(9); // 刻度数量
    m_angularAxis->setLabelFormat("%.1f°"); // 标签格式
    m_chart->addAxis(m_angularAxis, QPolarChart::PolarOrientationAngular);
    m_series->attachAxis(m_angularAxis);

    // 创建幅度轴
    m_radialAxis = new QValueAxis();
    m_radialAxis->setRange(0, 10); // 幅度范围：0到10
    m_radialAxis->setTickCount(6); // 刻度数量
    m_chart->addAxis(m_radialAxis, QPolarChart::PolarOrientationRadial);
    m_series->attachAxis(m_radialAxis);

    // 创建图表视图
    m_chartView = new QChartView(m_chart);
    m_chartView->setRenderHint(QPainter::Antialiasing);

    // 将图表视图添加到布局中
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_chartView);
    setLayout(layout); // 设置布局
}

void BalancingPolarChart::addDataPoint(double angle, double magnitude)
{
    m_series->append(angle, magnitude); // 添加数据点
}

void BalancingPolarChart::clearData()
{
    m_series->clear(); // 清除所有数据点
}

void BalancingPolarChart::setAngularRange(double min, double max)
{
    m_angularAxis->setRange(min, max); // 设置角度轴范围
}

void BalancingPolarChart::setRadialRange(double min, double max)
{
    m_radialAxis->setRange(min, max); // 设置幅度轴范围
}