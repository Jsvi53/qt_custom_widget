/***
 * @Date: 2025-03-15 09:20:24
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-16 16:48:54
 * @FilePath: \qt_custom_widget\src\jp_balancesetupscreen\jp_balancesetup.cpp
 */
#include <QDebug>
#include <QSpacerItem>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "jp_balancesetupscreen/jp_balancesetup.h"
#include "ui_jp_balancesetup.h"


JP_BalanceSetup::JP_BalanceSetup(QWidget *parent) : QWidget(parent)
{
    ui = new Ui::JP_BalanceSetup;
    ui->setupUi(this);
    balanceItem = new BalanceSetupItem(ui->scrollAreaWidgetContents);
    balanceItem->set_openChannelButton_Icon(QString(":/balancesetup/balancingsetup_assets/icon_balancesetup_link_gray.svg"));
    balanceItem->set_iconLabel1_Icon(QString(":/balancesetup/balancingsetup_assets/icon_balancesetup_motor.svg"));
    balanceItem->set_iconLabel2_Icon(QString(":/balancesetup/balancingsetup_assets/icon_balancesetup_triangle.svg"));
    balanceItem->set_balancePlane("Plane A");
    balanceItem->set_chLabel("Ch TP1");
    balanceItem->set_sensorLabel("VIB 6.631");
    balanceItem->set_resultParaters("SPEED", "0", "RPM");

    // 添加liveSwitchButton
    // liveSwitchButton = new SwitchButton(ui->workspaceSetBar);
    // liveSwitchButton->setBackgroundColor(QColor(0xE4, 0xE4, 0xE4));

    // 获取ui->workspaceSetBar 布局
    QHBoxLayout *workspaceSetBarHLayout = static_cast<QHBoxLayout *>(ui->workspaceSetBar->layout());



    // 设置布局
    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(balanceItem);
    // 下面添加垂直弹簧，将balanceSetupItem顶到scrollAreaWidgetContents的顶部
    QSpacerItem *spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    vLayout->addSpacerItem(spacer);
    vLayout->setContentsMargins(0, 0, 0, 0);
    ui->scrollAreaWidgetContents->setLayout(vLayout);
}

JP_BalanceSetup::~JP_BalanceSetup()
{
    delete ui;
}

BalanceSetupItem::BalanceSetupItem(QWidget *parent) : QWidget(parent)
{
    setFixedHeight(70);
    setObjectName("BalanceSetupItem");
    setContentsMargins(0, 0, 0, 0);
    setAttribute(Qt::WA_StyledBackground, true);  // 启用样式表背景
    // 仅设置border的上下边框
    setStyleSheet(
        "QWidget#BalanceSetupItem {"
        "border-bottom: 1px solid lightgray;"
        "border-top: 1px solid lightgray;"
        "border-radius: 0;"
        "padding: 0px;"
        "}");

    // 设置控件
    openChannelButton = new QPushButton(this);
    iconLabel1        = new QLabel(this);
    iconLabel2        = new QLabel(this);
    balancePlane      = new QLabel(this);
    chLabel           = new QLabel(this);
    sensorLabel       = new QLabel(this);
    // 设置控件基本样式
    openChannelButton->setText("");
    openChannelButton->setFixedSize(50, 50);
    openChannelButton->setStyleSheet("QPushButton{border: none; border-radius:3px; border: 1px solid lightgray;}");

    iconLabel1->setFixedSize(50, 50);
    iconLabel1->setAlignment(Qt::AlignCenter);  // 居中对齐

    iconLabel2->setFixedSize(50, 50);
    iconLabel2->setAlignment(Qt::AlignCenter);  // 居中对齐
    iconLabel2->setStyleSheet("QLabel{border: none; border-radius:3px; border: 1px solid lightgray;}");

    balancePlane->setFixedSize(550, 50);
    balancePlane->setFont(QFont("微软雅黑", 14, 500));             // 微软雅黑， 14号，左对齐，黑色字体， 500为正常字重
    balancePlane->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);  //  左对齐，垂直居中
    balancePlane->setStyleSheet("QLabel{border: none; color:rgb(70,70,70);}");

    chLabel->setFixedSize(150, 50);
    chLabel->setFont(QFont("微软雅黑", 14, 500));             // 微软雅黑， 14号，左对齐，黑色字体， 500为正常字重
    chLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);  //  左对齐，垂直居中
    chLabel->setStyleSheet("QLabel{border: none; color:rgb(70,70,70);}");

    sensorLabel->setFixedSize(200, 50);
    sensorLabel->setFont(QFont("微软雅黑", 14, 500));             // 微软雅黑， 14号，左对齐，黑色字体， 500为正常字重
    sensorLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);  //  左对齐，垂直居中
    sensorLabel->setStyleSheet("QLabel{border: none; color:rgb(70,70,70);}");

    // 设置子控件
    resultContainer1 = new QWidget(this);
    resultContainer2 = new QWidget(this);
    resultType       = new QLabel(resultContainer1);
    resultValue      = new QLabel(resultContainer1);
    resultUnit       = new QLabel(resultContainer1);

    // 设置子布局
    resultContainer1->setFixedWidth(80);
    resultContainer2->setFixedWidth(80);
    resultContainer1->setStyleSheet(
        "QWidget{"
        "border-left: 1px solid lightgray;"
        "border-right: 1px solid lightgray;"
        "border-radius: 0;"
        "padding: 0px;"
        "background-color: transparent;"
        "}");
    resultType->setFont(QFont("微软雅黑", 8, 500));              // 微软雅黑， 14号，左对齐，黑色字体， 500为正常字重
    resultType->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);  //  左对齐，垂直居中
    resultType->setStyleSheet("QLabel{color:rgb(255,255,255); background-color:rgb(70,70,70);}");

    resultValue->setFont(QFont("微软雅黑", 14, 500));              // 微软雅黑， 14号，左对齐，黑色字体， 500为正常字重
    resultValue->setAlignment(Qt::AlignRight | Qt::AlignVCenter);  //  左对齐，垂直居中
    resultValue->setStyleSheet("QLabel{color:rgb(70,70,70);}");

    resultUnit->setFont(QFont("微软雅黑", 8, 500));               // 微软雅黑， 14号，左对齐，黑色字体， 500为正常字重
    resultUnit->setAlignment(Qt::AlignRight | Qt::AlignVCenter);  //  左对齐，垂直居中
    resultUnit->setStyleSheet("QLabel{color:rgb(70,70,70);}");

    QVBoxLayout *sub_vLayout = new QVBoxLayout(resultContainer1);
    QHBoxLayout *sub_hLayout = new QHBoxLayout(resultContainer2);
    sub_hLayout->setSpacing(0);                   // 设置子布局的间距
    sub_vLayout->setSpacing(0);                   // 设置父布局的间距
    sub_vLayout->setContentsMargins(0, 0, 0, 0);  // 移除父布局的边距
    sub_hLayout->setContentsMargins(0, 0, 0, 0);  // 移除布局的边距
    sub_hLayout->addWidget(resultType);
    QSpacerItem *spacer1 = new QSpacerItem(20, 15, QSizePolicy::Expanding, QSizePolicy::Minimum);
    sub_hLayout->addSpacerItem(spacer1);
    sub_vLayout->addWidget(resultContainer2, 2);  // 添加到垂直子布局
    sub_vLayout->addWidget(resultValue, 5);
    sub_vLayout->addWidget(resultUnit, 2);

    // 设置布局
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->setContentsMargins(0, 0, 0, 0);  // 移除布局的边距
    hLayout->setSpacing(0);                   // 设置布局的间距
    QSpacerItem *spacer2 = new QSpacerItem(20, 50, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem *spacer3 = new QSpacerItem(20, 50, QSizePolicy::Fixed, QSizePolicy::Minimum);
    hLayout->addSpacerItem(spacer3);
    hLayout->addWidget(openChannelButton);
    hLayout->addWidget(iconLabel1);
    hLayout->addWidget(iconLabel2);
    hLayout->addWidget(balancePlane);
    hLayout->addWidget(chLabel);
    hLayout->addWidget(sensorLabel);
    hLayout->addWidget(resultContainer1);
    hLayout->addSpacerItem(spacer2);
    setLayout(hLayout);
}

BalanceSetupItem::~BalanceSetupItem()
{
}

// 设置打开通道按钮的图标
void BalanceSetupItem::set_openChannelButton_Icon(const QString &iconaddress)
{
    QIcon icon(iconaddress);
    openChannelButton->setIcon(icon);  // 设置图标
    openChannelButton->setIconSize(QSize(30, 30));
}

// 设置onlyIconLabel1的图标
void BalanceSetupItem::set_iconLabel1_Icon(const QString &iconaddress)
{
    QIcon icon(iconaddress);
    iconLabel1->setPixmap(icon.pixmap(QSize(40, 40)));  // 设置图标
}

// 设置onlyIconLabel2的图标
void BalanceSetupItem::set_iconLabel2_Icon(const QString &iconaddress)
{
    QIcon icon(iconaddress);
    iconLabel2->clear();
    iconLabel2->setPixmap(icon.pixmap(QSize(35, 35)));  // 设置图标
}

// 设置平衡面
void BalanceSetupItem::set_balancePlane(const QString &plane)
{
    balancePlane->setText(plane);
}

// 设置传感器通道标签
void BalanceSetupItem::set_chLabel(const QString &ch)
{
    chLabel->setText(ch);
}

// 设置传感器型号标签
void BalanceSetupItem::set_sensorLabel(const QString &ch)
{
    sensorLabel->setText(ch);
}

// 设置测量参数
void BalanceSetupItem::set_resultParaters(const QString &type, const QString &value, const QString &unit)
{
    // 设置resultType类型
    resultType->setText(type);

    // 设置resultValue值
    resultValue->setText(value);

    // 设置uint值
    resultUnit->setText(unit);
}

// 圈形字体标签，左边显示Ch,接着右边圈内显示TP1
CircleFontLabel::CircleFontLabel(const QString &text, QWidget *parent) : QLabel(parent)
{
    setText(text);
}

CircleFontLabel::~CircleFontLabel()
{
}

// 重写绘制事件，绘制一个白色的圆形
void CircleFontLabel::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawEllipse(rect().adjusted(0, 0, -rect().width() / 4, 0));
}