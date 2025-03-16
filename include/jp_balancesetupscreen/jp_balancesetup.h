/***
 * @Date: 2025-03-15 09:21:17
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-16 19:56:12
 * @FilePath: \qt_custom_widget\include\jp_balancesetupscreen\jp_balancesetup.h
 */

#pragma once
#include <QLabel>
#include <QPainter>
#include <QPushButton>
#include <QString>
#include <QWidget>

#include "qswitchbutton/qswitchbutton.h"

namespace Ui {
    class JP_BalanceSetup;
}


class BalanceSetupItem;
class CircleFontLabel;

// 平衡设置界面
class JP_BalanceSetup : public QWidget
{
    Q_OBJECT

public:
    explicit JP_BalanceSetup(QWidget *parent = nullptr);
    ~JP_BalanceSetup();

private:
    Ui::JP_BalanceSetup *ui;  // 正确的类型
    BalanceSetupItem    *balanceItem;
    SwitchButton        *liveSwitchButton;
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
