#include <QBrush>
#include <QFontMetrics>
#include <QPaintEvent>
#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include <QRect>
#include <QRectF>
#include <QTimer>

#include "commomcustomwidget.h"

WGBattery::WGBattery(QWidget *parent) : QWidget(parent), colorBack(Qt::white), colorBorder(Qt::black), colorPower(Qt::green), colorWarning(Qt::red), m_powerLevel(60), m_warnLevel(20), m_size(120, 50)
{
    // 设置默认大小
    resize(m_size);
}

void WGBattery::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect    rect(0, 0, width(), height());                    // 视口矩形区
    painter.setViewport(rect);                                 // 设置视口
    painter.setWindow(0, 0, m_size.width(), m_size.height());  // 设置窗口大小，逻辑坐标
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    // 绘制电池边框
    QPen pen(colorBorder);  // 边框线条颜色
    pen.setWidth(2);
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::BevelJoin);
    painter.setPen(pen);
    QBrush brush(colorBack);  // 画刷颜色
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    rect.setRect(1, 1, m_size.width() - 2, m_size.height() - 2);
    painter.drawRect(rect);  // 绘制电池边框
    brush.setColor(colorBorder);
    painter.setBrush(brush);
    rect.setRect(m_size.width() - 10, m_size.height() / 4, 5, m_size.height() / 2);
    painter.drawRect(rect);  // 画电池正极头

    // 画电量柱
    if(m_powerLevel > m_warnLevel)  // 正常颜色的电量柱
    {
        brush.setColor(colorPower);
        pen.setColor(colorPower);
    } else  // 电量低的电量柱
    {
        brush.setColor(colorWarning);
        pen.setColor(colorWarning);
    }
    painter.setBrush(brush);
    painter.setPen(pen);
    if(m_powerLevel > 0)
    {
        rect.setRect(5, 5, (m_size.width() - 10) * m_powerLevel / 100, m_size.height() - 10);
        painter.drawRect(rect);  // 画电量柱
    }

    // 绘制电量百分比文字
    QFontMetrics textSize(this->font());
    QString      powStr   = QString::asprintf("%d%%", m_powerLevel);
    QRect        textRect = textSize.boundingRect(powStr);  // 得到字符串的矩形区
    painter.setFont(this->font());
    pen.setColor(colorBorder);
    painter.setPen(pen);
    painter.drawText(m_size.width() / 2 - textRect.width() / 2, m_size.height() / 2 + textRect.height() / 2, powStr);

    event->accept();  // 表示事件已处理
}

void WGBattery::setPowerLevel(int pow)
{
    m_powerLevel = pow;
    emit powerLevelChanged(pow);  // 发射信号
    repaint();
}

int WGBattery::powerLevel() const
{
    return m_powerLevel;
}

void WGBattery::setWarnLevel(int warn)
{
    m_warnLevel = warn;
    repaint();
}

int WGBattery::warnLevel() const
{
    return m_warnLevel;
}

QSize WGBattery::size() const
{
    return m_size;
}

void WGBattery::setSize(const QSize &size)
{
    m_size = size;
    resize(m_size);
    repaint();
}

QSize WGBattery::sizeHint() const
{
    return m_size;
}

/***********************************
    WIFI 图标
************************************/

WGWifi::WGWifi(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(50, 50);
}

QSize WGWifi::sizeHint() const
{
    return QSize(100, 100);
}

QColor WGWifi::activeColor() const
{
    return m_activeColor;
}

QColor WGWifi::inactiveColor() const
{
    return m_inactiveColor;
}

int WGWifi::quality() const
{
    return m_quality;
}

void WGWifi::setActiveColor(const QColor &color)
{
    if(m_activeColor != color){
        m_activeColor = color;
        update();
    }
}

void WGWifi::setInactiveColor(const QColor &color)
{
    if(m_inactiveColor != color){
        m_inactiveColor = color;
        update();
    }
}

void WGWifi::setQuality(int value)
{
    value = qBound(0, value, 4);
    if(m_quality != value){
        m_quality = value;
        update();
    }
}

void WGWifi::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    
    // 抗锯齿设置
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    
    // 计算基本尺寸参数
    const int baseSize = qMin(width(), height());
    const int arcSpacing = baseSize / 20;
    const int centerRadius = baseSize / 15;
    
    // 设置坐标系原点到控件底部中心
    painter.translate(width()/2, height()*0.9);
    
    // 绘制三个信号圆弧
    for(int i = 0; i < 3; ++i){
        const int radius = baseSize * (0.3 + 0.2*i);
        const QColor color = (m_quality >= (4 - i)) ? m_activeColor : m_inactiveColor;
        drawWifiArc(painter, arcSpacing, radius, 45, 90, color);
    }
    
    // 绘制中心圆点
    const QColor centerColor = (m_quality > 0) ? m_activeColor : m_inactiveColor;
    drawCircle(painter, centerRadius, centerColor);
}

void WGWifi::drawCircle(QPainter &painter, int radius, const QColor &color)
{
    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(color);
    painter.drawEllipse(QPoint(0, 0), radius, radius);
    painter.restore();
}

void WGWifi::drawWifiArc(QPainter &painter, int arcHeight, int radius, 
                             int startAngle, int lenAngle, const QColor &color)
{
    painter.save();
    QRectF rect(-radius, -radius, radius*2, radius*2);
    
    QPainterPath path;
    path.arcTo(rect, startAngle, lenAngle);
    
    // 创建内圆路径用于剪切
    QPainterPath innerPath;
    innerPath.addEllipse(rect.adjusted(arcHeight, arcHeight, -arcHeight, -arcHeight));
    
    // 创建实际绘制路径
    QPainterPath drawPath = path - innerPath;
    
    painter.setPen(Qt::NoPen);
    painter.setBrush(color);
    painter.drawPath(drawPath);
    painter.restore();
}