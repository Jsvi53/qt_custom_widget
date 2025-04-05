#pragma once

#include <QVBoxLayout>
#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QPolarChart>
#include <QtCharts/QValueAxis>


QT_CHARTS_USE_NAMESPACE

class PolarDiagram : public QWidget
{
    Q_OBJECT

public:
    explicit PolarDiagram(QWidget *parent = nullptr);
    ~PolarDiagram();

    // 添加数据点
    void addDataPoint(double angle, double magnitude);

    // 清除所有数据
    void clearData();

    // 设置角度范围
    void setAngularRange(double min, double max);

    // 设置幅度轴范围
    void setRadialRange(double min, double max);

private:
    QPolarChart *polarDiagram;
    QChartView  *polarDiagramView;
    QLineSeries *polarDiagramSeries;
    QValueAxis  *angularAxis;
    QValueAxis  *radialAxis;

    void initChart();
};