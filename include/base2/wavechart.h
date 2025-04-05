/*** 
 * @Date: 2025-03-03 20:23:40
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-03 22:08:34
 * @FilePath: \qt_custom_widget\include\chart\wavechart.h
 */
#ifndef __WAVECHART_H
#define __WAVECHART_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChartView>
#include <QVBoxLayout>
#include <QFrame>
#include <QTimer>

QT_CHARTS_BEGIN_NAMESPACE
    class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

// 定义波形图类
class BalancingWaveChart : public QFrame
{
    Q_OBJECT

public:
    explicit BalancingWaveChart(QWidget *parent = nullptr);
    ~BalancingWaveChart();

private:
    QChart *waveChart;
    QLineSeries *waveSeries;
    QTimer *updateTimer;
    void updateData();
    void initChart();

};


#endif
