#ifndef __BARCHART_H
#define __BARCHART_H

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QVBoxLayout>
#include <QStringList>

QT_CHARTS_USE_NAMESPACE // 使用 Qt Charts 命名空间

class BalancingBarChart : public QFrame
{
    Q_OBJECT
public:
    explicit BalancingBarChart(QWidget *parent = nullptr);
    ~BalancingBarChart();

    // 设置柱状图数据
    void setData(const QMap<QString, double> &data);

    // 设置X轴标签
    void setAxisX(const QStringList &labels);

    // 设置Y轴范围
    void setAxisY(int min, int max);

private:
    void initChart();
    QChart *chart;  // 图标对象
    QChartView *chartView;  // 图表视图对象
    QBarSeries *series;  // 系列对象
    QBarCategoryAxis *axisX;  // X轴
    QValueAxis *axisY;  // Y轴
};

#endif // __BARCHART_H