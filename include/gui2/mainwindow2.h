#ifndef MAINWINDOW2_H
#define MAINWINDOW2_H

#include <QMainWindow>
#include "filetemplatewindow.h"
#include "TemplateConfigPage.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow2; }
QT_END_NAMESPACE


class MainWindow2 : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow2(QWidget *parent = nullptr);
    ~MainWindow2();

private slots:
    void onTemplateSelected(const TemplateParams &params); // 槽函数，用于处理信号

private:
    Ui::MainWindow2 *ui;
    FileTemplateWindow *fileTemplateWindow; // 文件模板窗口
    TemplateConfigPage *templateConfigPage; // 模板配置界面
};
#endif // MAINWINDOW_H
