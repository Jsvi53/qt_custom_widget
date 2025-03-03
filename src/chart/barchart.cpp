/*** 
 * @Date: 2025-03-03 19:39:02
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-03 23:24:35
 * @FilePath: \qt_custom_widget\src\chart\barchart.cpp
 */
#include "chart/barchart.h"

BalancingBarChart::BalancingBarChart(QWidget *parent) : QFrame(parent)
{
    initChart();
}

BalancingBarChart::~BalancingBarChart()
{
    delete chart;
    delete chartView;
    delete series;
    delete axisX;
    delete axisY;
}

void BalancingBarChart::initChart()
{
    // 创建图标对象
    chart = new QChart();
    chart->setTitle("Balancing Bar Chart");
    chart->setAnimationOptions(QChart::SeriesAnimations);   // 设置图表的动画效果

    // 创建系列
    series = new QBarSeries();

    // 创建X, Y轴坐标
    axisX = new QBarCategoryAxis();
    axisX->setTitleText("类别");  // 设置X轴标题
    chart->addAxis(axisX, Qt::AlignBottom);

    // 创建Y轴
    axisY = new QValueAxis();
    axisY->setTitleText("数值");
    chart->addAxis(axisY, Qt::AlignLeft);

    // 创建图表视图
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);   // 抗锯齿

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(chartView);
    setLayout(layout); // 设置布局

}

// 设置柱状图数据
void BalancingBarChart::setData(const QMap<QString, double> &data)
{
    series->clear();    // 清空数据
    // 添加新的数据集
    for(const QString &key : data.keys())
    {
        QBarSet *set = new QBarSet(key);
        for(double value : data.values(key))
        {
            *set << value;
        }
        series->append(set);
    }
}

// 设置X轴标签
void BalancingBarChart::setAxisX(const QStringList &labels)
{
    axisX->clear();
    axisX->append(labels);
}

// 设置Y轴范围
void BalancingBarChart::setAxisY(int min, int max)
{
    axisY->setRange(min, max);
}


