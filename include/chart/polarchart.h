#ifndef __POLARCHART_H
#define __POLARCHART_H

#include <QtCharts/QPolarChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QFrame>
#include <QVBoxLayout> // 添加 QVBoxLayout 头文件

QT_CHARTS_USE_NAMESPACE // 使用 Qt Charts 命名空间

class BalancingPolarChart : public QFrame
{
    Q_OBJECT

public:
    explicit BalancingPolarChart(QWidget *parent = nullptr);
    ~BalancingPolarChart();

    // 添加数据点
    void addDataPoint(double angle, double magnitude);

    // 清除所有数据
    void clearData();

    // 设置角度范围
    void setAngularRange(double min, double max);

    // 设置幅度轴范围
    void setRadialRange(double min, double max);

private:
    QPolarChart *m_chart;
    QChartView *m_chartView;
    QLineSeries *m_series;
    QValueAxis *m_angularAxis;
    QValueAxis *m_radialAxis; // 修复命名一致性问题

    void initChart();
};

#endif // __POLARCHART_H