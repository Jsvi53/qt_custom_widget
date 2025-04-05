/*** 
 * @Date: 2025-03-08 19:58:06
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-09 00:46:03
 * @FilePath: /qt_custom_widget/include/mainwindow/mainwindow.h
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "filetemplatewindow.h"
#include "TemplateConfigPage.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onTemplateSelected(const TemplateParams &params); // 槽函数，用于处理信号

private:
    Ui::MainWindow *ui;
    FileTemplateWindow *fileTemplateWindow; // 文件模板窗口
    TemplateConfigPage *templateConfigPage; // 模板配置界面
};
#endif // MAINWINDOW_H
