#include "jp_mainwindow/jp_mainwindow.h"
#include "ui_jp_mainwindow.h"
#include <QGraphicsDropShadowEffect>

JP_MainWindow::JP_MainWindow(QWidget *parent) : QWidget(parent), ui(new Ui::JP_MainWindow)
{
    ui->setupUi(this);

    // 设置Setting Button的阴影效果
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(5, 5);//阴影的偏移量
    shadow->setColor(QColor(43, 43, 43));//阴影的颜色
    shadow->setBlurRadius(8); // 阴影圆角的大小
    ui->home_SettingButton->setGraphicsEffect(shadow);

}

JP_MainWindow::~JP_MainWindow()
{
    delete ui;
}