#include "jp_mainwindow/jp_mainwindow.h"
#include "ui_jp_mainwindow.h"
#include <QGraphicsDropShadowEffect>

JP_MainWindow::JP_MainWindow(QWidget *parent) : QWidget(parent), ui(new Ui::JP_MainWindow)
{
    ui->setupUi(this);

    // 设置Setting Button的阴影效果
    QGraphicsDropShadowEffect *basewidgetshadow = new QGraphicsDropShadowEffect(this);
    basewidgetshadow->setOffset(2.5, 5);               // 阴影的偏移量
    basewidgetshadow->setColor(QColor(43, 43, 43));  // 阴影的颜色
    basewidgetshadow->setBlurRadius(30);             // 阴影圆角的大小
    ui->base_statebar->setGraphicsEffect(basewidgetshadow);

    // 设置Setting Button的阴影效果
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(5, 5);//阴影的偏移量
    shadow->setColor(QColor(43, 43, 43));//阴影的颜色
    shadow->setBlurRadius(8); // 阴影圆角的大小
    ui->home_SettingButton->setGraphicsEffect(shadow);

    // 设置Setting Button的阴影效果
    QGraphicsDropShadowEffect *filemanagershadow = new QGraphicsDropShadowEffect(this);
    filemanagershadow->setOffset(5, 5);//阴影的偏移量
    filemanagershadow->setColor(QColor(43, 43, 43));//阴影的颜色
    filemanagershadow->setBlurRadius(8); // 阴影圆角的大小
    ui->home_FilemanagerButton->setGraphicsEffect(filemanagershadow);

}

JP_MainWindow::~JP_MainWindow()
{
    delete ui;
}