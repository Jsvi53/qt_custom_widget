#pragma once
#include <QLabel>
#include <QPainter>
#include <QPushButton>
#include <QString>
#include <QWidget>

#include "qswitchbutton.h"

namespace Ui {
class BalanceMeasureScreenUI;
}

class BalanceSetupItem;
class CircleFontLabel;

// namespace BM
// {
//     class BalanceMeasureScreen;
// }

// 平衡测量屏幕
class BalanceMeasureScreen : public QWidget
{
    Q_OBJECT

public:
    explicit BalanceMeasureScreen(QWidget *parent = nullptr);
    ~BalanceMeasureScreen();

signals:
    void backButtonClicked();

private:
    Ui::BalanceMeasureScreenUI *ui;
    BalanceSetupItem           *balanceItem;
    SwitchButton               *liveSwitchButton;
};

// 设置项
class BalanceSetupItem : public QWidget
{
    Q_OBJECT

public:
    explicit BalanceSetupItem(QWidget *parent = nullptr);
    ~BalanceSetupItem();

    void set_openChannelButton_Icon(const QString &iconaddress);  // 设置打开通道按钮的图标
    void set_iconLabel1_Icon(const QString &iconaddress);         // 设置onlyIconLabel1的图标
    void set_iconLabel2_Icon(const QString &iconaddress);         // 设置onlyIconLabel2的图标
    void set_balancePlane(const QString &plane);                  // 设置平衡面
    void set_chLabel(const QString &ch);                          // 设置Ch标签
    void set_sensorLabel(const QString &ch);
    void set_resultParaters(const QString &type, const QString &value, const QString &unit);

private:
    QPushButton *openChannelButton;
    QLabel      *iconLabel1;
    QLabel      *iconLabel2;
    QLabel      *balancePlane;
    QLabel      *chLabel;
    QLabel      *sensorLabel;
    QWidget     *resultContainer1;
    QWidget     *resultContainer2;
    QLabel      *resultType;
    QLabel      *resultValue;
    QLabel      *resultUnit;
};

// 圈形字体标签，左边显示Ch ,接着右边圈内显示TP1
class CircleFontLabel : public QLabel
{
    Q_OBJECT

public:
    CircleFontLabel(const QString &text, QWidget *parent = nullptr);
    ~CircleFontLabel();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QString text;
};