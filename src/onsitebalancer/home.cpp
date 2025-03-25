#include <QGraphicsDropShadowEffect>
#include <QPushButton>
#include "onsitebalancer/home.h"
#include "ui_homescreen.h"


Hs::HomeScreen::HomeScreen(QWidget *parent) : QWidget(parent), ui(new Ui::HomeScreen)
{
    ui->setupUi(this);

    // 设置base_statebar的阴影效果
    QGraphicsDropShadowEffect *basewidgetshadow = new QGraphicsDropShadowEffect(this);
    basewidgetshadow->setOffset(2.5, 5);             // 阴影的偏移量
    basewidgetshadow->setColor(QColor(43, 43, 43));  // 阴影的颜色
    basewidgetshadow->setBlurRadius(30);             // 阴影圆角的大小
    ui->base_statebar->setGraphicsEffect(basewidgetshadow);

    // 设置home_SettingButton的阴影效果
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(5, 5);               // 阴影的偏移量
    shadow->setColor(QColor(43, 43, 43));  // 阴影的颜色
    shadow->setBlurRadius(8);              // 阴影圆角的大小
    ui->home_SettingButton->setGraphicsEffect(shadow);

    // 设置home_FilemanagerButton的阴影效果
    QGraphicsDropShadowEffect *filemanagershadow = new QGraphicsDropShadowEffect(this);
    filemanagershadow->setOffset(5, 5);               // 阴影的偏移量
    filemanagershadow->setColor(QColor(43, 43, 43));  // 阴影的颜色
    filemanagershadow->setBlurRadius(8);              // 阴影圆角的大小
    ui->home_FilemanagerButton->setGraphicsEffect(filemanagershadow);

    // 设置home_MachineTemplateButton的阴影效果
    QGraphicsDropShadowEffect *machineshadow = new QGraphicsDropShadowEffect(this);
    machineshadow->setOffset(5, 5);               // 阴影的偏移量
    machineshadow->setColor(QColor(43, 43, 43));  // 阴影的颜色
    machineshadow->setBlurRadius(8);              // 阴影圆角的大小
    ui->home_MachineTemplateButton->setGraphicsEffect(machineshadow);

    // 设置home_Balance_button的阴影效果
    QGraphicsDropShadowEffect *balanceshadow = new QGraphicsDropShadowEffect(this);
    balanceshadow->setOffset(5, 5);               // 阴影的偏移量
    balanceshadow->setColor(QColor(43, 43, 43));  // 阴影的颜色
    balanceshadow->setBlurRadius(8);              // 阴影圆角的大小
    ui->home_Balance_button->setGraphicsEffect(balanceshadow);

    // 设置home_HelpButton的阴影效果
    QGraphicsDropShadowEffect *helpshadow = new QGraphicsDropShadowEffect(this);
    helpshadow->setOffset(5, 5);               // 阴影的偏移量
    helpshadow->setColor(QColor(43, 43, 43));  // 阴影的颜色
    helpshadow->setBlurRadius(8);              // 阴影圆角的大小
    ui->home_HelpButton->setGraphicsEffect(helpshadow);

    // 设置home_SpeedMeasure_button的阴影效果
    QGraphicsDropShadowEffect *speedshadow = new QGraphicsDropShadowEffect(this);
    speedshadow->setOffset(5, 5);               // 阴影的偏移量
    speedshadow->setColor(QColor(43, 43, 43));  // 阴影的颜色
    speedshadow->setBlurRadius(8);              // 阴影圆角的大小
    ui->home_SpeedMeasure_button->setGraphicsEffect(speedshadow);

    // 设置home_OneBalance_button的阴影效果
    QGraphicsDropShadowEffect *oneplaneshadow = new QGraphicsDropShadowEffect(this);
    oneplaneshadow->setOffset(5, 5);               // 阴影的偏移量
    oneplaneshadow->setColor(QColor(43, 43, 43));  // 阴影的颜色
    oneplaneshadow->setBlurRadius(8);              // 阴影圆角的大小
    ui->home_OneBalance_button->setGraphicsEffect(oneplaneshadow);

    // 设置home_TwoBalance_button的阴影效果
    QGraphicsDropShadowEffect *twoplaneshadow = new QGraphicsDropShadowEffect(this);
    twoplaneshadow->setOffset(5, 5);               // 阴影的偏移量
    twoplaneshadow->setColor(QColor(43, 43, 43));  // 阴影的颜色
    twoplaneshadow->setBlurRadius(8);              // 阴影圆角的大小
    ui->home_TwoBalance_button->setGraphicsEffect(twoplaneshadow);

}

Hs::HomeScreen::~HomeScreen()
{
    delete ui;
}

// 实现统一getter
QPushButton *Hs::HomeScreen::getButton(ButtonType buttonType) const
{
    switch(buttonType)
    {
        case SettingButton:
            return ui->home_SettingButton;

        default:
            return nullptr;
    }
}

QPushButton *Hs::HomeScreen::getButton(const QString &name) const
{
    return findChild<QPushButton *>(name);  // 注意要给按钮设置objectName
}