/*** 
 * @Date: 2025-03-03 20:23:40
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-03 23:08:19
 * @FilePath: \qt_custom_widget\src\chart\wavechart.cpp
 */
#include "chart/wavechart.h"
#include <QtMath>


// 波形图构造函数
BalancingWaveChart::BalancingWaveChart(QWidget *parent) : QFrame(parent)
{
    initChart();
}

// 波形图析构函数
BalancingWaveChart::~BalancingWaveChart()
{
    delete waveChart;
    delete waveSeries;
}

void BalancingWaveChart::initChart()
{
    waveChart = new QChart();
    waveChart->setTitle("Wave Chart");
    waveSeries = new QLineSeries();
    waveChart->addSeries(waveSeries);

    // 在 initChart 中初始化定时器
    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &BalancingWaveChart::updateData);
    updateTimer->start(100);  // 每 100 毫秒更新一次数据

    waveChart->legend()->hide();  // 隐藏图例

    // 设置X轴
    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(0, 100);  // X轴范围
    axisX->setTitleText("Time");  // X轴标题

    // 设置Y轴
    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(-1, 1);  // Y轴范围
    axisY->setTitleText("Amplitude");  // Y轴标题

    // 将X轴和Y轴添加到图表中
    waveChart->addAxis(axisX, Qt::AlignBottom);
    waveSeries->attachAxis(axisX);
    waveChart->addAxis(axisY, Qt::AlignLeft);
    waveSeries->attachAxis(axisY);

    // 向 waveSeries 添加数据
    for (int i = 0; i <= 100; ++i) {
        // 生成一些示例数据（例如正弦波）
        qreal x = i;  // X值
        qreal y = qSin(i * 2 * M_PI / 100);  // Y值（正弦函数）
        waveSeries->append(x, y);  // 添加数据点
    }

    // 创建图表视图并设置为主窗口的中心部件
    QChartView *chartView = new QChartView(waveChart);
    chartView->setRenderHint(QPainter::Antialiasing);  // 启用抗锯齿

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(chartView);
    setLayout(layout);
}


// 更新数据的槽函数
void BalancingWaveChart::updateData()
{
    static int x = 0;
    qreal y = qSin(x * 2 * M_PI / 100);  // 生成新的 Y 值
    waveSeries->append(x, y);  // 添加新数据点
    x++;

    // 如果数据点太多，可以移除旧数据
    if (waveSeries->count() > 100) {
        waveSeries->remove(0);  // 移除第一个数据点
    }
}