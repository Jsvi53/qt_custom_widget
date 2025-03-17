
#include <QDebug>
#include <QGraphicsTextItem>
#include <QVBoxLayout>

#include "chart/spectrum.h"

Spectrum::Spectrum(QWidget *parent) : QWidget(parent)
{
    initSpectrum();
}

Spectrum::~Spectrum()
{
}

// 初始化频谱图
void Spectrum::initSpectrum()
{
    // 创建图表元素
    spectrumChart     = new QChart();
    spectrumSeries    = new QSplineSeries();
    Xaxis             = new QValueAxis;
    Yaxis             = new QValueAxis;
    spectrumChartView = new QChartView(spectrumChart);

    // 添加图表元素
    spectrumChart->addSeries(spectrumSeries);
    spectrumChart->addAxis(Xaxis, Qt::AlignBottom);
    spectrumChart->addAxis(Yaxis, Qt::AlignLeft);
    spectrumSeries->attachAxis(Xaxis);
    spectrumSeries->attachAxis(Yaxis);

    // 图表设置
    spectrumChart->legend()->hide();
    spectrumChart->setBackgroundRoundness(0);  // 背景透明
    spectrumChart->setBackgroundVisible(false);

    // 设置图表边框
    spectrumChart->setMargins(QMargins(10, 15, 30, 0));  // 设置边距为0,即去掉图表的边框

    // 设置图表网格
    Xaxis->setGridLineVisible(true);
    Yaxis->setGridLineVisible(true);
    QPen gridPen(Qt::gray, 1, Qt::DotLine, Qt::RoundCap);  // 设置为虚线, 颜色为灰色, 宽度为1, 线帽为圆角
    Xaxis->setGridLinePen(gridPen);
    Yaxis->setGridLinePen(gridPen);

    // 设置坐标轴颜色为黑色
    QPen AxisPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap);
    Xaxis->setLinePen(AxisPen);
    Yaxis->setLinePen(AxisPen);

    // 设置刻度范围
    Xaxis->setRange(0, 700);  // 设置刻度横轴（0-700，间隔100），纵轴（0-0.5，间隔0.1）
    Xaxis->setTickCount(8);
    Xaxis->setLabelFormat("%d");  // 设置横坐标刻度值不带小数
    Yaxis->setRange(0, 0.5);
    Yaxis->setTickCount(6);
    Yaxis->setLabelFormat("%0.1f");  // 1位小数

    Xaxis->setLabelsFont(QFont("Microsoft YaHei", 12));
    Yaxis->setLabelsFont(QFont("Microsoft YaHei", 12));
    // 添加横坐标标题到右侧
    QGraphicsTextItem *xAxisTitleRight = new QGraphicsTextItem("f[Hz]");
    xAxisTitleRight->setFont(QFont("Microsoft YaHei", 12));
    spectrumChart->scene()->addItem(xAxisTitleRight);

    // 添加纵坐标标题到顶部
    QGraphicsTextItem *yAxisTitleTop = new QGraphicsTextItem("v[mm/s]");
    yAxisTitleTop->setFont(QFont("Microsoft YaHei", 12));
    yAxisTitleTop->setPos(0, -5);  // 放置在顶部
    spectrumChart->scene()->addItem(yAxisTitleTop);

    // 添加布局
    spectrumChartView->setFixedSize(660, 280);
    spectrumChartView->setRenderHint(QPainter::Antialiasing);
    QVBoxLayout *spectrumLayout = new QVBoxLayout(this);
    spectrumLayout->setContentsMargins(0, 0, 0, 0);
    spectrumLayout->setSpacing(0);
    spectrumLayout->addWidget(spectrumChartView);
    setLayout(spectrumLayout);

    // 监听绘图区域变化，直接设置xPos，yPos，而不设置用connect，其值为0
    connect(spectrumChart, &QChart::plotAreaChanged, [=](const QRectF &plotArea) {
        qreal xPos = plotArea.right();   // X 轴末端
        qreal yPos = plotArea.bottom();  // Y 轴底部
        xAxisTitleRight->setPos(xPos + 15, yPos);
    });
}
