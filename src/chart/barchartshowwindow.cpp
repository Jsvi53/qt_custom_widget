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


}

BarChartShowWindow::~BarChartShowWindow()
{
    delete ui;
    delete bar;
}
