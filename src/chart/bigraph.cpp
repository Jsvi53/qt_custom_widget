/***
 * @Date: 2025-03-19 19:05:12
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-19 22:13:56
 * @FilePath: \qt_custom_widget\src\chart\bigraph.cpp
 */
#include <QPainter>
#include <QtMath>
#include <limits>

#include "chart/Bigraph.h"

Bigraph::Bigraph(QWidget* parent) : QWidget(parent)
{
    setStyleSheet("background-color: transparent;");
    // 初始化图表
    initBackChart();
    initFrontChart();

    // 初始位置更新
    updateChartPositions(positionBaseAngle);
    // 开启定时器更新连接线
}

Bigraph::~Bigraph()
{
}

// frontchart 初始化
void Bigraph::initFrontChart()
{
    frontChart     = new QChart();
    frontSeries    = new QLineSeries();
    frontAxisX     = new QValueAxis();
    frontAxisY     = new QValueAxis();
    frontChartView = new QChartView(frontChart);

    // 添加图表元素
    frontChart->addSeries(frontSeries);
    frontChart->addAxis(frontAxisX, Qt::AlignBottom);
    frontChart->addAxis(frontAxisY, Qt::AlignLeft);
    frontSeries->attachAxis(frontAxisX);
    frontSeries->attachAxis(frontAxisY);

    // 图表设置
    frontChart->legend()->hide();
    frontChart->setMargins(QMargins(20, 20, 20, 20));
    frontChart->setBackgroundVisible(false);
    frontChartView->setParent(this);
    frontChartView->setFixedSize(chartWidth, chartHeight);
    frontChartView->setAttribute(Qt::WA_TranslucentBackground);  // 打开设置透明度属性
    frontChartView->setRenderHint(QPainter::Antialiasing);

    // 坐标轴设置
    frontAxisX->setTickCount(9);
    frontAxisY->setTickCount(4);

    // 去掉网格线
    frontAxisX->setGridLineVisible(false);
    frontAxisY->setGridLineVisible(false);
    frontAxisX->setLinePenColor(QColor(Qt::black));
    frontAxisY->setLinePenColor(QColor(Qt::black));

    // 将 frontChartView 放在最顶层
    frontChartView->raise();
}

// backchart 初始化
void Bigraph::initBackChart()
{
    backChart     = new QChart();
    backSeries    = new QLineSeries();
    backAxisX     = new QValueAxis();
    backAxisY     = new QValueAxis();
    backChartView = new QChartView(backChart);

    // 添加图表元素
    backChart->addSeries(backSeries);
    backChart->addAxis(backAxisX, Qt::AlignBottom);
    backChart->addAxis(backAxisY, Qt::AlignLeft);
    backSeries->attachAxis(backAxisX);
    backSeries->attachAxis(backAxisY);

    // 图表设置
    backChart->legend()->hide();
    backChart->setMargins(QMargins(20, 20, 20, 20));
    backChart->setBackgroundVisible(false);
    backChartView->setParent(this);
    backChartView->setFixedSize(chartWidth, chartHeight);
    backChartView->setAttribute(Qt::WA_TranslucentBackground);  // 打开设置透明度属性
    backChartView->setRenderHint(QPainter::Antialiasing);

    // 坐标轴设置
    backAxisX->setTickCount(9);
    backAxisY->setTickCount(4);

    // 去掉网格线
    backAxisX->setGridLineVisible(true);
    backAxisY->setGridLineVisible(true);
    backAxisX->setGridLinePen(QPen(QColor(Qt::gray), 1, Qt::DotLine));
    backAxisY->setGridLinePen(QPen(QColor(Qt::gray), 1, Qt::DotLine));
    backAxisX->setLinePenColor(QColor(Qt::black));
    backAxisY->setLinePenColor(QColor(Qt::black));

    // 将 backChartView 放在最底层
    backChartView->lower();
}

// 更新图表位置的槽函数
void Bigraph::updateChartPositions(int angle)
{
    // 将角度转换为弧度
    qreal angleInRadians = qDegreesToRadians(static_cast<double>(angle));
    // 计算 backChartView 的位置
    backChartX = static_cast<int>(static_cast<qreal>(frontChartX) + static_cast<qreal>(positionBaseLength) * qCos(angleInRadians));
    backChartY = static_cast<int>(static_cast<qreal>(frontChartY) - static_cast<qreal>(positionBaseLength) * qSin(angleInRadians));
    backChartView->move(backChartX, backChartY);
    frontChartView->move(frontChartX, frontChartY);
}

void Bigraph::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(QColor(Qt::darkGray), 1, Qt::DotLine));

    // 连接X轴和Y轴的刻度线
    connectAxisTicks(&painter, backChart, backSeries, frontChart, frontSeries, true);   // X轴
    connectAxisTicks(&painter, backChart, backSeries, frontChart, frontSeries, false);  // Y轴
}

QList<qreal> Bigraph::getTickValues(QValueAxis* axis)
{
    QList<qreal> ticks;
    qreal        min       = axis->min();
    qreal        max       = axis->max();
    int          tickCount = axis->tickCount();
    if(tickCount < 2)
        return ticks;

    qreal step = (max - min) / (tickCount - 1);
    for(int i = 0; i < tickCount; ++i)
    {
        ticks.append(min + i * step);
    }
    return ticks;
}

// 添加数据接口
void Bigraph::addFrontSeriesPoint(qreal x, qreal y)
{
    frontSeries->append(x, y);
}

void Bigraph::addBackSeriesPoint(qreal x, qreal y)
{
    backSeries->append(x, y);
}

// 清空数据接口
void Bigraph::clearFrontSeries()
{
    frontSeries->clear();
}

void Bigraph::clearBackSeries()
{
    backSeries->clear();
}

QRectF Bigraph::calculateSeriesRange(QLineSeries* series)
{
    if(series->count() == 0)
    {
        return QRectF(0, 0, 1, 1);  // 默认范围防止空数据崩溃
    }

    qreal minX = std::numeric_limits<qreal>::max();
    qreal maxX = std::numeric_limits<qreal>::lowest();
    qreal minY = minX;
    qreal maxY = maxX;

    for(const QPointF& point : series->points())
    {
        minX = qMin(minX, point.x());
        maxX = qMax(maxX, point.x());
        minY = qMin(minY, point.y());
        maxY = qMax(maxY, point.y());
    }

    // 处理单点数据情况
    if(qFuzzyCompare(minX, maxX))
    {
        maxX += 0.1;
        minX -= 0.1;
    }
    if(qFuzzyCompare(minY, maxY))
    {
        maxY += 0.1;
        minY -= 0.1;
    }

    // 添加5%边距使曲线不贴边
    qreal xMargin = (maxX - minX) * 0.05;
    qreal yMargin = (maxY - minY) * 0.05;

    return QRectF(minX - xMargin, minY - yMargin, (maxX - minX) + 2 * xMargin, (maxY - minY) + 2 * yMargin);
}
void Bigraph::adjustAxisRanges()
{
    // 计算合并范围
    QRectF frontRect = calculateSeriesRange(frontSeries);
    QRectF backRect  = calculateSeriesRange(backSeries);

    combinedRange = QRectF(qMin(frontRect.left(), backRect.left()), qMin(frontRect.top(), backRect.top()), qMax(frontRect.width(), backRect.width()), qMax(frontRect.height(), backRect.height()));

    // 添加统一边距
    qreal xMargin = combinedRange.width() * 0.05;
    qreal yMargin = combinedRange.height() * 0.05;

    // 设置统一范围到两个图表
    frontAxisX->setRange(combinedRange.left() - xMargin, combinedRange.right() + xMargin);
    frontAxisY->setRange(combinedRange.top() - yMargin, combinedRange.bottom() + yMargin);

    backAxisX->setRange(combinedRange.left() - xMargin, combinedRange.right() + xMargin);
    backAxisY->setRange(combinedRange.top() - yMargin, combinedRange.bottom() + yMargin);
}

void Bigraph::connectAxisTicks(QPainter* painter, QChart* backChart, QLineSeries* backSeries, QChart* frontChart, QLineSeries* frontSeries, bool isXAxis)
{
    QValueAxis* backAxis = isXAxis ? qobject_cast<QValueAxis*>(backChart->axes(Qt::Horizontal).first()) : qobject_cast<QValueAxis*>(backChart->axes(Qt::Vertical).first());

    QValueAxis* frontAxis = isXAxis ? qobject_cast<QValueAxis*>(frontChart->axes(Qt::Horizontal).first()) : qobject_cast<QValueAxis*>(frontChart->axes(Qt::Vertical).first());

    if(!backAxis || !frontAxis)
        return;

    // 使用合并后的范围计算基准点
    qreal baseValue = isXAxis ? combinedRange.top() : combinedRange.left();

    QList<qreal> backTicks  = getTickValues(backAxis);
    QList<qreal> frontTicks = getTickValues(frontAxis);

    int minCount = qMin(backTicks.size(), frontTicks.size());
    for(int i = 0; i < minCount; ++i)
    {
        // 转换backChart坐标
        QPointF backPoint     = isXAxis ? QPointF(backTicks[i], baseValue) : QPointF(baseValue, backTicks[i]);
        QPoint  backGlobalPos = backChartView->mapToParent(backChartView->mapFromScene(backChart->mapToPosition(backPoint, backSeries)));

        // 转换frontChart坐标
        QPointF frontPoint     = isXAxis ? QPointF(frontTicks[i], baseValue) : QPointF(baseValue, frontTicks[i]);
        QPoint  frontGlobalPos = frontChartView->mapToParent(frontChartView->mapFromScene(frontChart->mapToPosition(frontPoint, frontSeries)));

        // 绘制连接线
        painter->drawLine(backGlobalPos, frontGlobalPos);
    }
}