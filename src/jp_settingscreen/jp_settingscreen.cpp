/*** 
 * @Date: 2025-03-13 20:09:59
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-13 21:32:25
 * @FilePath: \qt_custom_widget\src\jp_settingscreen\jp_settingscreen.cpp
 */
#include "jp_settingscreen/jp_settingscreen.h"
#include "ui_jp_settingscreen.h"
#include <QGraphicsDropShadowEffect>

JP_SettingScreen::JP_SettingScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JP_SettingScreen)
{
    ui->setupUi(this);

    // 设置base_navigationbar的阴影效果，似乎没有效果
    // QGraphicsDropShadowEffect *navShadow = new QGraphicsDropShadowEffect(this);
    // navShadow->setOffset(0, 5); // 阴影的偏移量
    // navShadow->setColor(QColor(10, 10, 10)); // 阴影的颜色
    // navShadow->setBlurRadius(8); // 阴影模糊半径
    // ui->base_navigationbar->setGraphicsEffect(navShadow);

    // 设置 setting_taskbar 的阴影效果
    QGraphicsDropShadowEffect *taskbarShadow = new QGraphicsDropShadowEffect(this);
    taskbarShadow->setOffset(5, 5); // 阴影的偏移量
    taskbarShadow->setColor(QColor(43, 43, 43)); // 阴影的颜色
    taskbarShadow->setBlurRadius(8); // 阴影模糊半径
    ui->setting_taskbar->setGraphicsEffect(taskbarShadow);
}

JP_SettingScreen::~JP_SettingScreen()
{
    delete ui;
}


SettingItem::SettingItem(QWidget *parent) : QWidget(parent)
{
    // 创建控件
    inputButton = new QPushButton("Button", this);
    itemName    = new QLabel("Item Name", this);
    item        = new QLabel("Item Content", this);

    // 创建布局
    QHBoxLayout *mainLayout  = new QHBoxLayout(this);  // 主布局（水平）
    QVBoxLayout *rightLayout = new QVBoxLayout();      // 右侧布局（垂直）

    // 将控件添加到布局
    mainLayout->addWidget(inputButton);  // 左侧按钮
    rightLayout->addWidget(itemName);    // 右侧上方标签
    rightLayout->addWidget(item);        // 右侧下方标签
    mainLayout->addLayout(rightLayout);  // 将右侧布局添加到主布局
}