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
