/*** 
 * @Date: 2025-03-10 19:25:39
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-18 23:53:39
 * @FilePath: \qt_custom_widget\src\test\test.cpp
 */
/*** 
 * @Date: 2025-03-10 19:25:39
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-18 23:49:45
 * @FilePath: \qt_custom_widget\src\test\test.cpp
 */
#include "test/test.h"
#include "ui_myWidget.h"
#include <QVBoxLayout>

myWidget::myWidget(QWidget *parent) : QWidget(parent), ui(new Ui::myWidget) {
    ui->setupUi(this);

    // 初始化 customPlot
    customPlot = new QCustomPlot(this);
    QVBoxLayout *verticalLayout = new QVBoxLayout(this);
    verticalLayout->addWidget(customPlot);  // 将 customPlot 添加到布局中

    // 配置 customPlot
    configureCustomPlot();
}

myWidget::~myWidget() {
    delete ui;
}

void myWidget::configureCustomPlot() {
    // 创建一个新的图形
    QCPGraph *graph = customPlot->addGraph();

    // 生成正弦波数据
    QVector<double> x(1001), y(1001);  // 1001 个数据点
    for (int i = 0; i < 1001; ++i) {
        x[i] = i / 100.0 - 5;  // x 范围从 -5 到 5
        y[i] = qSin(x[i]);     // y = sin(x)
    }

    // 将数据添加到图形
    graph->setData(x, y);

    // 设置图形样式
    graph->setPen(QPen(Qt::blue));  // 设置线条颜色为蓝色
    graph->setLineStyle(QCPGraph::lsLine);  // 设置为线条样式
    graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 3));  // 设置数据点样式

    // 配置坐标轴
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("sin(x)");
    customPlot->xAxis->setRange(-5, 5);  // 设置 x 轴范围
    customPlot->yAxis->setRange(-1.5, 1.5);  // 设置 y 轴范围

    // 显示网格
    customPlot->xAxis->grid()->setVisible(true);
    customPlot->yAxis->grid()->setVisible(true);

    // 重新生成图表
    customPlot->replot();
}