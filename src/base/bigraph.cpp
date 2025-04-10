#include <QDebug>
#include <QPainter>

#include "bigraph.h"

// Bigraph类的构造函数
Bigraph::Bigraph(QWidget *parent) : QWidget(parent)
{
    initFrontPlot();                          // 初始化前端图表
    initBackPlot();                           // 初始化后端图表
    updateChartPositions(positionBaseAngle);  // 更新图表位置
}

// Bigraph类的析构函数
Bigraph::~Bigraph()
{
    delete frontPlot;  // 删除前端图表
    delete backPlot;   // 删除后端图表
}

// 初始化前端图表
void Bigraph::initFrontPlot()
{
    frontPlot = new QCustomPlot(this);                           // 创建一个新的前端图表
    frontPlot->setGeometry(frontChartX, frontChartY, 700, 190);  // 设置图表位置和大小

    // 设置背景为透明
    frontPlot->setBackground(Qt::transparent);

    // 初始化坐标轴
    frontAxisX = frontPlot->xAxis;
    frontAxisY = frontPlot->yAxis;
    frontAxisX->setLabel("f[Hz]");    // X轴标签
    frontAxisY->setLabel("v[mm/s]");  // Y轴标签

    // 配置刻度器
    QSharedPointer<QCPAxisTickerFixed> frontTickerX(new QCPAxisTickerFixed);
    QSharedPointer<QCPAxisTickerFixed> frontTickerY(new QCPAxisTickerFixed);
    frontAxisX->setTicker(frontTickerX);  // 设置X轴刻度器
    frontAxisY->setTicker(frontTickerY);  // 设置Y轴刻度器

    // 设置小数精度，避免显示整数
    frontAxisX->setNumberFormat("f");   // 使用浮点格式
    frontAxisY->setNumberFormat("f");   // 使用浮点格式
    frontAxisX->setNumberPrecision(2);  // 设置X轴标签精度为2位小数
    frontAxisY->setNumberPrecision(2);  // 设置Y轴标签精度为2位小数

    // 取消刻度网格线
    frontAxisX->grid()->setVisible(false);  // X轴网格不可见
    frontAxisY->grid()->setVisible(false);  // Y轴网格不可见

    // 初始化数据系列
    frontGraph = frontPlot->addGraph();
    frontGraph->setPen(QPen(Qt::blue, 1.5));  // 设置图表线条的颜色和粗细
}

// 初始化后端图表
void Bigraph::initBackPlot()
{
    backPlot = new QCustomPlot(this);                         // 创建一个新的后端图表
    backPlot->setGeometry(backChartX, backChartY, 700, 170);  // 设置图表位置和大小

    // 设置背景为透明
    backPlot->setBackground(Qt::transparent);

    // 配置坐标轴
    backAxisX = backPlot->xAxis;
    backAxisY = backPlot->yAxis;

    // 设置坐标轴颜色为透明
    backAxisX->setBasePen(QPen(Qt::NoPen));     // X轴线条透明
    backAxisY->setBasePen(QPen(Qt::NoPen));     // Y轴线条透明
    backAxisX->setTickPen(QPen(Qt::NoPen));     // X轴刻度线透明
    backAxisY->setTickPen(QPen(Qt::NoPen));     // Y轴刻度线透明
    backAxisX->setSubTickPen(QPen(Qt::NoPen));  // X轴子刻度线透明
    backAxisY->setSubTickPen(QPen(Qt::NoPen));  // Y轴子刻度线透明
    backAxisX->setTickLabels(false);            // 不显示X轴刻度标签
    backAxisY->setTickLabels(false);            // 不显示Y轴刻度标签

    // 设置网格样式
    backAxisX->grid()->setPen(QPen(Qt::gray, 1, Qt::DotLine));  // X轴网格为灰色点线
    backAxisY->grid()->setPen(QPen(Qt::gray, 1, Qt::DotLine));  // Y轴网格为灰色点线
    backAxisX->grid()->setVisible(true);                        // 确保X轴网格可见
    backAxisY->grid()->setVisible(true);                        // 确保Y轴网格可见

    // 配置刻度器
    QSharedPointer<QCPAxisTickerFixed> backTickerX(new QCPAxisTickerFixed);
    QSharedPointer<QCPAxisTickerFixed> backTickerY(new QCPAxisTickerFixed);
    backAxisX->setTicker(backTickerX);  // 设置X轴刻度器
    backAxisY->setTicker(backTickerY);  // 设置Y轴刻度器

    // 初始化数据系列
    backGraph = backPlot->addGraph();
    backGraph->setPen(QPen(Qt::lightGray, 1, Qt::DashLine));  // 设置图表线条的颜色和样式
}

// 更新图表位置
void Bigraph::updateChartPositions(int angle)
{
    qreal radians = qDegreesToRadians(static_cast<double>(angle));                       // 将角度转换为弧度
    backChartX    = frontChartX + static_cast<int>(positionBaseLength * qCos(radians));  // 计算后端图表X坐标
    backChartY    = frontChartY - static_cast<int>(positionBaseLength * qSin(radians));  // 计算后端图表Y坐标
    backPlot->move(backChartX, backChartY);                                              // 移动后端图表到新的位置
}

// 添加前端图表数据点
void Bigraph::addFrontSeriesPoint(double x, double y)
{
    frontGraph->addData(x, y);  // 向前端图表添加数据点
}

// 添加后端图表数据点
void Bigraph::addBackSeriesPoint(double x, double y)
{
    backGraph->addData(x, y);  // 向后端图表添加数据点
}

// 添加前端图表多个数据点
void Bigraph::addFrontSeriesPoint(QVector<double> x, QVector<double> y)
{
    frontGraph->setData(x, y);  // 设置前端图表的数据
}

// 添加后端图表多个数据点
void Bigraph::addBackSeriesPoint(QVector<double> x, QVector<double> y)
{
    backGraph->setData(x, y);  // 设置后端图表的数据
}

// 清空前端图表的数据
void Bigraph::clearFrontSeries()
{
    frontGraph->data()->clear();  // 清空前端图表数据
}

// 清空后端图表的数据
void Bigraph::clearBackSeries()
{
    backGraph->data()->clear();  // 清空后端图表数据
}

// 调整坐标轴范围
void Bigraph::adjustAxisRanges()
{
    // 自动调整坐标轴范围并同步
    frontPlot->rescaleAxes(true);                          // 自动调整前端图表坐标轴
    backPlot->xAxis->setRange(frontPlot->xAxis->range());  // 设置后端X轴范围与前端同步
    backPlot->yAxis->setRange(frontPlot->yAxis->range());  // 设置后端Y轴范围与前端同步

    // 添加5%边距
    auto adjustWithMargin = [](QCPRange &range) {
        double margin = (range.upper - range.lower) * 0.05;  // 计算边距
        range.lower -= margin;                               // 设置下限
        range.upper += margin;                               // 设置上限
    };

    QCPRange xRange = frontPlot->xAxis->range();  // 获取前端X轴范围
    QCPRange yRange = frontPlot->yAxis->range();  // 获取前端Y轴范围
    adjustWithMargin(xRange);                     // 调整X轴范围
    adjustWithMargin(yRange);                     // 调整Y轴范围

    frontPlot->xAxis->setRange(xRange);  // 设置前端X轴范围
    frontPlot->yAxis->setRange(yRange);  // 设置前端Y轴范围
    backPlot->xAxis->setRange(xRange);   // 设置后端X轴范围
    backPlot->yAxis->setRange(yRange);   // 设置后端Y轴范围

    frontPlot->replot();  // 重新绘制前端图表
    backPlot->replot();   // 重新绘制后端图表
}

// 绘制事件
void Bigraph::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);                          // 调用基类的绘制事件
    QPainter painter(this);                              // 创建绘制对象
    painter.setRenderHint(QPainter::Antialiasing);       // 开启抗锯齿
    painter.setPen(QPen(Qt::darkGray, 1, Qt::DotLine));  // 设置绘制的笔（灰色点线）

    connectAxisTicks(&painter, true);   // 绘制X轴刻度连接线
    connectAxisTicks(&painter, false);  // 绘制Y轴刻度连接线
}

// 连接坐标轴刻度
void Bigraph::connectAxisTicks(QPainter *painter, bool isXAxis)
{
    QCPAxis *frontAxis = isXAxis ? frontAxisX : frontAxisY;  // 获取前端坐标轴
    QCPAxis *backAxis  = isXAxis ? backAxisX : backAxisY;    // 获取后端坐标轴

    QList<double> frontTicks = getTickValues(frontAxis);  // 获取前端坐标轴刻度值
    QList<double> backTicks  = getTickValues(backAxis);   // 获取后端坐标轴刻度值

    const int minCount = qMin(frontTicks.size(), backTicks.size());  // 获取最小的刻度数量
    for(int i = 0; i < minCount; ++i)
    {
        // 前端坐标转换
        QPointF frontPointF = isXAxis ? QPointF(frontAxis->coordToPixel(frontTicks[i]), frontAxisY->coordToPixel(frontAxisY->range().lower))   // X轴刻度点
                                      : QPointF(frontAxisX->coordToPixel(frontAxisX->range().lower), frontAxis->coordToPixel(frontTicks[i]));  // Y轴刻度点
        QPoint  frontPoint  = frontPlot->mapToParent(frontPointF.toPoint());                                                                   // 转换为父坐标系坐标

        // 后端坐标转换
        QPointF backPointF = isXAxis ? QPointF(backAxis->coordToPixel(backTicks[i]), backAxisY->coordToPixel(backAxisY->range().lower))   // X轴刻度点
                                     : QPointF(backAxisX->coordToPixel(backAxisX->range().lower), backAxis->coordToPixel(backTicks[i]));  // Y轴刻度点
        QPoint  backPoint  = backPlot->mapToParent(backPointF.toPoint());                                                                 // 转换为父坐标系坐标

        // 绘制连接线
        painter->drawLine(frontPoint, backPoint);  // 绘制前后图表刻度之间的连接线
    }
}

// 获取坐标轴的刻度值
QList<double> Bigraph::getTickValues(QCPAxis *axis)
{
    QList<double> ticks;
    if(auto ticker = static_cast<QCPAxisTickerFixed *>(axis->ticker().data()))
    {
        double       current = axis->range().lower;
        const double step    = ticker->tickStep();
        while(current <= axis->range().upper + 1e-6)
        {  // 处理浮点精度
            ticks.append(current);
            current += step;
        }
    }
    return ticks;
}


