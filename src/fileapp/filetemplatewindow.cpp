/***
 * @Date: 2025-03-24 15:40:07
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-04-01 14:10:51
 * @FilePath: \qt_custom_widget\src\fileapp\filetemplatewindow.cpp
 */
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QListView>

#include "fileapp/TemplateParams.h"
#include "fileapp/filetemplatewindow.h"
#include "ui_filetemplatewindow.h"


FileTemplateWindow::FileTemplateWindow(QWidget *parent) : QWidget(parent), ui(new Ui::FileTemplateWindow)
{
    ui->setupUi(this);
    model = new QFileSystemModel(this);
    model->setRootPath(QDir::currentPath() + "/build/");  // 设置当前路径为根目录
    model->setFilter(QDir::Files | QDir::NoDotAndDotDot);  // 仅显示文件，不显示 . 和 ..
    model->setNameFilters({"*.tpl"});                      // 仅显示模板文件
    model->setNameFilterDisables(false);                   // 启用文件名过滤
    ui->listView->setModel(model);
    ui->listView->setRootIndex(model->setRootPath(QDir::currentPath() + "/build/"));  // 设置根目录

    // 绑定单击事件（非双击）
    connect(ui->listView, &QListView::clicked, this, &FileTemplateWindow::onFileClicked);  // 使用自身的槽函数
    connect(ui->pushButton, &QPushButton::clicked, this, [this] {
        QString fullPath = QDir::currentPath() + "/build/new_template.tpl";  // 使用完整路径
        createTemplateFile(fullPath);
    });
}

FileTemplateWindow::~FileTemplateWindow()
{
    delete model;  // 确保释放模型资源
    delete ui;     // 确保释放 UI 资源
}

void FileTemplateWindow::onFileClicked(const QModelIndex &index)
{
    QFileSystemModel *model    = static_cast<QFileSystemModel *>(ui->listView->model());  // 使用 ui->listView
    QString           filePath = model->filePath(index);

    if(filePath.endsWith(".tpl"))
    {
        // 1. 读取并解析模板文件
        TemplateParams params = parseTemplateFile(filePath);

        // 2. 发送信号通知主窗口切换界面
        emit templateFileSelected(params);  // 关键信号
    }
}

TemplateParams FileTemplateWindow::parseTemplateFile(const QString &filePath)
{
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly))
    {
        qWarning() << "Failed to open file:" << file.errorString();
        return TemplateParams();
    }

    QJsonDocument doc  = QJsonDocument::fromJson(file.readAll());
    QJsonObject   json = doc.object();

    TemplateParams params;
    params.sensorId          = json["sensor_id"].toString();
    params.maxRpm            = json["max_rpm"].toDouble();
    params.calibrationFactor = json["calibration_factor"].toDouble();

    return params;
}

void FileTemplateWindow::createTemplateFile(const QString &filePath)
{
    // 将 ~ 替换为当前用户的主目录
    QString fullPath = filePath;
    if(fullPath.startsWith("~"))
    {
        fullPath.replace(0, 1, QDir::rootPath());
    }

    // 确保目录存在
    QDir dir = QFileInfo(fullPath).dir();
    if(!dir.exists())
    {
        dir.mkpath(".");
    }

    QJsonObject json;
    json["sensor_id"]          = "SENSOR_001";
    json["max_rpm"]            = 3000;
    json["calibration_factor"] = 0.85;
    json["balance_mode"]       = "auto";
    json["tolerance_level"]    = 0.02;
    json["measurement_units"]  = "mm/s";
    json["description"]        = "Motor vibration template for industrial equipment";

    QJsonDocument doc(json);
    QFile         file(fullPath);
    if(!file.open(QIODevice::WriteOnly))
    {
        qWarning() << "Failed to create template file:" << file.errorString();
        return;
    }

    file.write(doc.toJson());
    file.close();
    qDebug() << "Template file created successfully:" << fullPath;
}