
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
    // 背景透明
    spectrumChart->setBackgroundRoundness(0);
    spectrumChart->setBackgroundVisible(false);
    // 设置刻度横轴（0-700，间隔100），纵轴（0-0.5，间隔0.1）
    Xaxis->setRange(0, 700);
    Xaxis->setTickCount(8);
    Xaxis->setLabelFormat("%d");  // 设置横坐标刻度值不带小数
    Yaxis->setRange(0, 0.5);
    Yaxis->setTickCount(6);
    Yaxis->setLabelFormat("%0.1f");   // 1位小数

    // 手动添加横坐标标题到左侧和右侧
    QGraphicsTextItem *xAxisTitleRight = new QGraphicsTextItem("f[Hz]");
    xAxisTitleRight->setFont(QFont("Microsoft YaHei", 6));
    xAxisTitleRight->setZValue(1000); // 设置较高的 z-value
    xAxisTitleRight->setPos(spectrumChart->plotArea().right()-40, spectrumChart->plotArea().bottom()-20); // 放置在右侧
    spectrumChart->scene()->addItem(xAxisTitleRight);

    // 手动添加纵坐标标题到顶部和底部
    QGraphicsTextItem *yAxisTitleTop = new QGraphicsTextItem("v[mm/s]");
    yAxisTitleTop->setFont(QFont("Microsoft YaHei", 6));
    yAxisTitleTop->setPos(spectrumChart->plotArea().left() + 10, 10);  // 放置在顶部
    spectrumChart->scene()->addItem(yAxisTitleTop);

    // 添加布局
    spectrumChartView->setRenderHint(QPainter::Antialiasing);
    QVBoxLayout *spectrumLayout = new QVBoxLayout(this);
    spectrumLayout->addWidget(spectrumChartView);
    spectrumLayout->setContentsMargins(0, 0, 0, 0);
    spectrumLayout->setSpacing(0);
    setLayout(spectrumLayout);
}
