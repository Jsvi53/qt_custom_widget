/*** 
 * @Date: 2025-03-08 19:58:06
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-09 01:09:22
 * @FilePath: /qt_custom_widget/src/mainwindow/mainwindow.cpp
 */
#include "mainwindow/mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QStackedWidget>
#include "fileapp/TemplateParams.h"
#include "fileapp/filetemplatewindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 初始化文件模板窗口和模板配置界面
    fileTemplateWindow = new FileTemplateWindow(this);
    templateConfigPage = new TemplateConfigPage(this);

    // 将模板配置界面添加到主窗口的堆栈中
    ui->stackedWidget->addWidget(templateConfigPage);

    // 连接信号和槽
    connect(fileTemplateWindow, &FileTemplateWindow::templateFileSelected,
            this, &MainWindow::onTemplateSelected);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete fileTemplateWindow;
    delete templateConfigPage;
}

void MainWindow::onTemplateSelected(const TemplateParams &params) {
    // 处理接收到的模板参数
    qDebug() << "Template selected with parameters:";
    qDebug() << "Sensor ID:" << params.sensorId;
    qDebug() << "Max RPM:" << params.maxRpm;
    qDebug() << "Calibration Factor:" << params.calibrationFactor;

    // 切换到模板配置界面
    ui->stackedWidget->setCurrentWidget(templateConfigPage);

    // 将参数传递给模板配置界面
    templateConfigPage->loadParams(params);
}