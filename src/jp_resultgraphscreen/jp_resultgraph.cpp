
/***
 * @Date: 2025-03-20 08:13:59
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-20 16:17:14
 * @FilePath: \qt_custom_widget\src\jp_resultgraphscreen\jp_resultgraph.cpp
 */
#include <QGraphicsDropShadowEffect>
#include <QVBoxLayout> 
#include "jp_resultgraphscreen/jp_resultgraph.h"
#include "ui_jp_resultgraph.h"

JP_ResultGraph::JP_ResultGraph(QWidget *parent) : QWidget(parent), ui(new Ui::JP_ResultGraph)
{
    ui->setupUi(this);
    // 设置Setting Button的阴影效果
    QGraphicsDropShadowEffect *base_navigationbarshadow = new QGraphicsDropShadowEffect(this);
    base_navigationbarshadow->setOffset(0, 5);               // 阴影的偏移量
    base_navigationbarshadow->setColor(QColor(43, 43, 43));  // 阴影的颜色
    base_navigationbarshadow->setBlurRadius(30);             // 阴影圆角的大小
    ui->base_navigationbar->setGraphicsEffect(base_navigationbarshadow);

    // 设置Setting Button的阴影效果
    QGraphicsDropShadowEffect *graphWorkAreaShadow = new QGraphicsDropShadowEffect(this);
    graphWorkAreaShadow->setOffset(5, 5);               // 阴影的偏移量
    graphWorkAreaShadow->setColor(QColor(43, 43, 43));  // 阴影的颜色
    graphWorkAreaShadow->setBlurRadius(10);             // 阴影圆角的大小
    ui->graphWorkplace->setGraphicsEffect(graphWorkAreaShadow);

    // 设置Setting Button的阴影效果
    QGraphicsDropShadowEffect *styleBarShadow = new QGraphicsDropShadowEffect(this);
    styleBarShadow->setOffset(5, 5);               // 阴影的偏移量
    styleBarShadow->setColor(QColor(43, 43, 43));  // 阴影的颜色
    styleBarShadow->setBlurRadius(10);             // 阴影圆角的大小
    ui->styleBar->setGraphicsEffect(styleBarShadow);

    // 整体值
    prograssBar_V_OP = new overallValuesPrograssBar(this);
    prograssBar_V_RMS = new  overallValuesPrograssBar(this);
    prograssBar_A_OP = new  overallValuesPrograssBar(this);
    prograssBar_A_RMS = new  overallValuesPrograssBar(this);
    prograssBar_V_OP->setRange(0, 100);
    prograssBar_V_OP->setValue(15);
    ui->gridLayout->addWidget(prograssBar_V_OP, 1, 0);      // 添加进度条到布局, 位置在第二行第一列

    prograssBar_V_RMS->setRange(0, 100);
    prograssBar_V_RMS->setValue(20);
    ui->gridLayout_4->addWidget(prograssBar_V_RMS, 1, 0);

    prograssBar_A_OP->setRange(0, 100);
    prograssBar_A_OP->setValue(12);
    ui->gridLayout_5->addWidget(prograssBar_A_OP, 1, 0);

    prograssBar_A_RMS->setRange(0, 100);
    prograssBar_A_RMS->setValue(8);
    ui->gridLayout_6->addWidget(prograssBar_A_RMS, 1, 0);


    // 上图表
    resultBigraph = new Bigraph(ui->upGraph);
    sineGenerator = new SineGenerator(this);
    sineGenerator->configure(1000, 1, 44100);

    QVector<qreal> waveform = sineGenerator->generate(1000);
    resultBigraph->addFrontSeriesPoint(0, 0);
    resultBigraph->addBackSeriesPoint(0, 0);
    for(int i = 0; i < waveform.size(); i++)
    {
        resultBigraph->addFrontSeriesPoint(i, waveform[i]);
        resultBigraph->addBackSeriesPoint(i, waveform[i]);
    }
    resultBigraph->addFrontSeriesPoint(1000, 0);
    resultBigraph->addBackSeriesPoint(1000, 0);
    resultBigraph->adjustAxisRanges();

    resultBigraph->frontAxisX->setTitleText("f[Hz]");
    resultBigraph->frontAxisY->setTitleText("v[mm/s]");
    resultBigraph->backChart->setTitle("PlaneA Speed");

    QVBoxLayout *upGraphLayout = new QVBoxLayout(ui->upGraph);
    upGraphLayout->addWidget(resultBigraph);

    // 下图表
    resultDownBigraph = new Bigraph(ui->upGraph);
    resultDownBigraph->addFrontSeriesPoint(0, 0);
    resultDownBigraph->addBackSeriesPoint(0, 0);
    resultDownBigraph->addFrontSeriesPoint(1000, 0);
    resultDownBigraph->addBackSeriesPoint(1000, 0);
    resultDownBigraph->adjustAxisRanges();

    resultDownBigraph->frontAxisX->setTitleText("t[s]");
    resultDownBigraph->frontAxisY->setTitleText("v[mm/s]");
    resultDownBigraph->backChart->setTitle("PlaneB Speed");

    QVBoxLayout *downGraphLayout = new QVBoxLayout(ui->downGraph);
    downGraphLayout->addWidget(resultDownBigraph);


}

JP_ResultGraph::~JP_ResultGraph()
{
    delete ui;
}


overallValuesPrograssBar::overallValuesPrograssBar(QWidget *parent) : QProgressBar(parent)
{
    // 隐藏进度条的文本值
    setTextVisible(false);

    // 设置样式表，清除默认的绿色背景
    setStyleSheet("QProgressBar { background-color: transparent; border: none; }");
}

overallValuesPrograssBar::~overallValuesPrograssBar()
{

}

// 一条竖线在一条横线上滑动, 隐藏进度条的值
void overallValuesPrograssBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event); // 忽略事件参数

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 获取进度条的矩形区域
    QRect rect = this->rect();

    // 计算当前进度对应的竖线位置
    int progressWidth = rect.width() * value() / maximum();

    // 绘制横线
    // 竖线左侧为黑色
    painter.setPen(Qt::black);
    painter.drawLine(rect.left(), rect.height() / 2, progressWidth, rect.height() / 2);

    // 竖线右侧为灰色
    painter.setPen(Qt::gray);
    painter.drawLine(progressWidth, rect.height() / 2, rect.right(), rect.height() / 2);

    // 绘制黑色竖线
    painter.setPen(Qt::black);
    painter.drawLine(progressWidth, rect.top(), progressWidth, rect.bottom());
}