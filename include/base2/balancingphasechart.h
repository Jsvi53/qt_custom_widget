/*** 
 * @Date: 2025-03-04 10:22:10
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-04 14:50:42
 * @FilePath: \qt_custom_widget\include\chart\balancingphasechart.h
 */
#ifndef __BALANCINGPHASECHART_H
#define __BALANCINGPHASECHART_H
#include <QWidget>
#include <QtCharts/QPolarChart>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QCategoryAxis>
#include <QVBoxLayout>
QT_CHARTS_BEGIN_NAMESPACE
    class QChart;
QT_CHARTS_END_NAMESPACE


QT_CHARTS_USE_NAMESPACE


class BalancingPhaseChart : public QWidget
{
    Q_OBJECT

public:
    BalancingPhaseChart(QWidget *parent = nullptr);
    ~BalancingPhaseChart();

    void addDataPoint(double angle, double magnitude);  // 添加数据点
    void addScatterPoint(double angle, double magnitude);   // 添加散点
    void addScatterPointWithText(double angle, double magnitude, const QString &text);   // 添加带文本的散点
    void clearData();   // 清除所有数据
    void setAngularRange(double min, double max);   // 设置角度范围
    void setRadialRange(double min, double max);    // 设置幅度轴范围


private:
    QPolarChart *phaseChart;    // 极坐标图表
    QChartView *phaseChartView; // 图表视图
    QCategoryAxis *angularAxis;    // 角度轴
    QValueAxis *radialAxis;     // 幅度轴
    QLineSeries *phaseLineSeries;   // 数据系列
    QScatterSeries *phaseScatterSeries;  // 散点系列
    void initChart();
};

#endif
