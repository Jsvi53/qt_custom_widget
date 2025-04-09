#ifndef __COMMONCUSTOMWIDGET_H__
#define __COMMONCUSTOMWIDGET_H__

#include <QColor>
#include <QPainter>
#include <QRandomGenerator>
#include <QSize>
#include <QTimer>
#include <QWidget>

class WGBattery : public QWidget
{
    Q_OBJECT
    // 自定义属性
    Q_PROPERTY(int powerLevel READ powerLevel WRITE setPowerLevel NOTIFY powerLevelChanged)
    Q_PROPERTY(int warnLevel READ warnLevel WRITE setWarnLevel)
    Q_PROPERTY(QSize size READ size WRITE setSize)

public:
    explicit WGBattery(QWidget *parent = nullptr);
    void  setPowerLevel(int pow);      // 设置当前电量值
    int   powerLevel() const;          // 返回当前电量值
    void  setWarnLevel(int warn);      // 设置电量低阈值
    int   warnLevel() const;           // 返回电量低阈值
    QSize size() const;                // 获取电池图标大小
    void  setSize(const QSize &size);  // 设置电池图标大小
    QSize sizeHint() const override;   // 重定义的函数，设置组件的合适大小

protected:
    void paintEvent(QPaintEvent *event) override;  // 绘制组件并显示效果

signals:
    void powerLevelChanged(int);  // 自定义信号

private:
    QColor colorBack;     // 背景色
    QColor colorBorder;   // 电池边框颜色
    QColor colorPower;    // 电量柱颜色
    QColor colorWarning;  // 电量短缺时的颜色
    int    m_powerLevel;  // 电量值为 0～100，属性 powerLevel 的存储变量
    int    m_warnLevel;   // 电量低阈值，属性 warnLevel 的存储变量
    QSize  m_size;        // 电池图标大小
};

/***********************************
    WIFI 图标
************************************/
/**
 * @brief 自定义WiFi信号强度显示控件
 *
 * 本控件用于显示类似手机信号强度的WiFi图标，支持：
 * - 5档信号强度显示（0-4）
 * - 自定义激活/非激活状态颜色
 * - 自动适应控件尺寸
 *
 * 使用示例：
 * @code
 * // 创建控件
 * WGWifi *wifi = new WGWifi;
 * wifi->setFixedSize(150, 150);
 *
 * // 设置颜色
 * wifi->setActiveColor(Qt::green);     // 激活状态颜色
 * wifi->setInactiveColor(Qt::gray);    // 非激活状态颜色
 *
 * // 设置信号强度（0-4）
 * wifi->setQuality(3);
 * @endcode
 *
 * 属性说明：
 * - activeColor:  信号有效时的颜色（默认白色）
 * - inactiveColor:信号无效时的颜色（默认深灰）
 * - quality:      信号强度等级（0-4，默认4）
 */
class WGWifi : public QWidget
{
    Q_OBJECT
    // 激活状态颜色（可通过样式表设置）
    Q_PROPERTY(QColor activeColor READ activeColor WRITE setActiveColor)
    // 非激活状态颜色（可通过样式表设置）
    Q_PROPERTY(QColor inactiveColor READ inactiveColor WRITE setInactiveColor)
    // 信号强度等级（范围0-4，0表示无信号）
    Q_PROPERTY(int quality READ quality WRITE setQuality)
public:
    explicit WGWifi(QWidget *parent = nullptr);

    /**
     * @brief 建议控件的最佳尺寸
     * @return QSize(100, 100) 默认建议尺寸
     */
    QSize sizeHint() const override;

    // 颜色访问器 ----------

    /// 获取当前激活状态颜色
    QColor activeColor() const;
    /// 获取当前非激活状态颜色
    QColor inactiveColor() const;
    /// 获取当前信号强度等级（0-4）
    int quality() const;

public slots:
    /**
     * @brief 设置激活状态颜色
     * @param color 新颜色值
     * @note 设置后会触发重绘
     */
    void setActiveColor(const QColor &color);

    /**
     * @brief 设置非激活状态颜色
     * @param color 新颜色值
     * @note 设置后会触发重绘
     */
    void setInactiveColor(const QColor &color);

    /**
     * @brief 设置信号强度等级
     * @param value 信号强度（0-4）
     * @note 值会被自动限制在0-4范围内
     *       设置后会触发重绘
     */
    void setQuality(int value);

protected:
    /// 重写绘制事件
    void paintEvent(QPaintEvent *event) override;

private:
    // 绘制中心圆点
    void drawCircle(QPainter &painter, int radius, const QColor &color);

    /**
     * @brief 绘制WiFi圆弧
     * @param painter 绘图对象
     * @param arcHeight 圆弧厚度
     * @param radius 圆弧半径
     * @param startAngle 起始角度（单位：度，时钟3点方向为0度）
     * @param lenAngle 角度跨度
     * @param color 绘制颜色
     */
    void drawWifiArc(QPainter &painter, int arcHeight, int radius, int startAngle, int lenAngle, const QColor &color);

private:
    int    m_quality       = 4;             // 当前信号强度（0-4）
    QColor m_activeColor   = Qt::white;     // 激活颜色（默认白）
    QColor m_inactiveColor = Qt::darkGray;  // 非激活颜色（默认深灰）
};

#endif  // __COMMONCUSTOMWIDGET_H__