/*** 
 * @Date: 2025-03-03 19:39:02
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-03 23:36:47
 * @FilePath: \qt_custom_widget\src\chart\barchartshowwindow.cpp
 */
#include "chart/barchartshowwindow.h"
#include "ui_barchartshowwindow.h"

BarChartShowWindow::BarChartShowWindow(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::BarChartShowWindow)
{
    ui->setupUi(this);
    bar  = new BalancingBarChart(this);
    bar->resize(640, 480);
    bar->show();

    // 设置柱状图数据
    QMap<QString, double> data;
    data.insert("A", 1);
    data.insert("B", 2);
    data.insert("C", 3);
    data.insert("D", 4);
    data.insert("E", 5);
    bar->setData(data);

    // 设置X轴标签
    bar->setAxisX(QStringList() << "A" << "B" << "C" << "D" << "E");
    bar->setAxisY(0, 10);// 设置Y轴范围

    // 使用布局管理器将 bar 添加到 BarChartShowWindow 中
    QVBoxLayout *layout = new QVBoxLayout(this); // 创建一个垂直布局
    layout->addWidget(bar); // 将 bar 添加到布局中
    layout->setContentsMargins(0, 0, 0, 0); // 设置布局的边距为 0
    layout->setSpacing(0); // 设置布局的间距为 0
    setLayout(layout); // 将布局设置为 BarChartShowWindow 的布局
}

BarChartShowWindow::~BarChartShowWindow()
{
    delete ui;
    delete bar;
}
