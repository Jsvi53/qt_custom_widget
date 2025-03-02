#include "chart/polarchartshowwindow.h"
#include "ui_polarchartshowwindow.h"

PolarChartShowWindow::PolarChartShowWindow(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::PolarChartShowWindow)
{
    ui->setupUi(this);

    // 初始化图表对象
    m_chart = new BalancingPolarChart(this);
    m_chart->resize(640, 480);
    m_chart->show();

    // 添加示例数据
    m_chart->addDataPoint(0, 1);
    m_chart->addDataPoint(45, 2);
    m_chart->addDataPoint(90, 3);
    m_chart->addDataPoint(135, 4);
    m_chart->addDataPoint(180, 5);
}

PolarChartShowWindow::~PolarChartShowWindow()
{
    delete ui;
    delete m_chart; // 释放图表对象
}