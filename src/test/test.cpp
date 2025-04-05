/***
 * @Date: 2025-03-10 19:25:39
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-04-01 21:24:08
 * @FilePath: \custom_widget\src\test\test.cpp
 */
#include "test.h"

VibrationGraph ::VibrationGraph(QWidget* parent) : QWidget(parent), vibrationGraph(new QCustomPlot(this)), vibrationGenerator(new UnbalanceVibrationGenerator())
{
    // 设置窗口大小
    this->resize(1280, 800);
    this->setWindowTitle("Vibration Graph");

    vibrationGraph->addGraph();
    vibrationGraph->graph(0)->setPen(QPen(Qt::blue));
    vibrationGraph->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));

    vibrationGraph->xAxis2->setVisible(true);
    vibrationGraph->yAxis2->setVisible(true);
    vibrationGraph->xAxis2->setTickLabels(false);
    vibrationGraph->yAxis2->setTickLabels(false);

    connect(vibrationGraph->xAxis, SIGNAL(rangeChanged(QCPRange)), vibrationGraph->xAxis2, SLOT(setRange(QCPRange)));
    connect(vibrationGraph->yAxis, SIGNAL(rangeChanged(QCPRange)), vibrationGraph->yAxis2, SLOT(setRange(QCPRange)));
    vibrationGenerator->setRotationSpeed(3000);
    std::vector<double> std_vibValue = vibrationGenerator->generate(10000);
    vibValue.resize(std_vibValue.size());
    std::copy(std_vibValue.begin(), std_vibValue.end(), vibValue.begin());
    vibTime.resize(vibValue.size());
    for (int i = 0; i < vibValue.size(); ++i)
    {
        vibTime[i] = 60.0 * i / speed;
    }
    vibrationGraph->graph(0)->setData(vibTime, vibValue);
    vibrationGraph->graph(0)->rescaleAxes();
    vibrationGraph->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

VibrationGraph::~VibrationGraph()
{
}
