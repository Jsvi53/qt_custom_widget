/*** 
 * @Date: 2025-04-02 09:59:35
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-04-02 16:14:24
 * @FilePath: \qt_custom_widget\src\test\test.cpp
 */
#include "test/test.h"
#include <QDebug>

vibrationWaveGraph::vibrationWaveGraph(QWidget *parent) : QWidget(parent), vibgraph(new QCustomPlot(this)), unbalanceSignalGenerator(new UnbalanceVibrationGenerator())
{
    vibgraph->setObjectName(QStringLiteral("vibgraph"));
    vibgraph->setGeometry(QRect(0, 0, 800, 600));
    vibgraph->setMinimumSize(QSize(800, 600));
    vibgraph->setMaximumSize(QSize(800, 600));
    vibgraph->setAutoFillBackground(false);
    vibgraph->xAxis->setLabel("Time (s)");
    vibgraph->yAxis->setLabel("Amplitude (g)");
    vibgraph->xAxis2->setLabel("Frequency (Hz)");
    vibgraph->yAxis2->setLabel("Phase (rad)");
    // 设置采样率
    double samplingRate = 10000.0; // 10kHz
    unbalanceSignalGenerator->setSampleRate(samplingRate);
    unbalanceSignalGenerator->setRotationSpeed(3000);
    generatedValue           = unbalanceSignalGenerator->generate(SAMPLENUM);
    for(int i = 0; i < generatedValue.size(); i++)
    {
        double t = static_cast<double>(60 * i / samplingRate);
        // t 添加到 timeValue 向量中
        timeValue.push_back(t);
    }

    vibgraphShow();
}


vibrationWaveGraph::~vibrationWaveGraph()
{
    delete vibgraph;
    delete unbalanceSignalGenerator;
}

void vibrationWaveGraph::vibgraphShow()
{
    // 添加两个新的图形并设置它们的外观：
    vibgraph->addGraph();
    vibgraph->graph(0)->setPen(QPen(Qt::blue)); // 第一个图形的线条颜色为蓝色
    vibgraph->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // 第一个图形将用半透明蓝色填充
    vibgraph->addGraph();
    vibgraph->graph(1)->setPen(QPen(Qt::red)); // 第二个图形的线条颜色为红色

    // 配置右轴和上轴显示刻度但不显示标签：
    vibgraph->xAxis2->setVisible(true);
    vibgraph->xAxis2->setTickLabels(false);
    vibgraph->yAxis2->setVisible(true);
    vibgraph->yAxis2->setTickLabels(false);
    // 让左轴和底轴始终将它们的范围传递给右轴和上轴：
    connect(vibgraph->xAxis, SIGNAL(rangeChanged(QCPRange)), vibgraph->xAxis2, SLOT(setRange(QCPRange)));
    connect(vibgraph->yAxis, SIGNAL(rangeChanged(QCPRange)), vibgraph->yAxis2, SLOT(setRange(QCPRange)));

    // 添加数据
    for(int i = 0; i < generatedValue.size(); i++)
    {
        vibgraph->graph(0)->addData(timeValue[i], generatedValue[i]);
        qDebug() << "timeValue:" << timeValue[i] << "generatedValue:" << generatedValue[i];
    }

    // 让范围自动调整，使第一个图形完美地适应可见区域：
    vibgraph->graph(0)->rescaleAxes();
    // 对于第二个图形，也调整范围，但只放大范围（如果第二个图形比第一个图形小）：
    vibgraph->graph(1)->rescaleAxes(true);
    // 注意：我们也可以直接调用 vibgraph->rescaleAxes(); 来实现

    // 允许用户通过鼠标拖动轴范围，通过鼠标滚轮缩放，并通过点击选择图形：
    vibgraph->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}