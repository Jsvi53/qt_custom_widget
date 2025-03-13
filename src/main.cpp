/*** 
 * @Date: 2025-03-01 10:24:48
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-13 09:58:06
 * @FilePath: \qt_custom_widget\src\main.cpp
 */
/***
 * @Date: 2025-03-01 10:24:48
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-13 00:53:36
 * @FilePath: \qt_custom_widget\src\main.cpp
 */
#include <QApplication>
#include <QDebug>
#include <QScreen>
#include <QSplashScreen>
#include <QTimer>

#include "basemodule/basewidget.h"
#include "chart/balancingshowphasechart.h"
#include "chart/barchartshowwindow.h"
#include "chart/polarchartshowwindow.h"
#include "chart/wavechartshowwindow.h"
#include "fileapp/filetemplatewindow.h"
#include "jp_mainwindow/jp_mainwindow.h"
#include "mainwindow/mainwindow.h"
#include "manager/managerwindow.h"
#include "qswitchbutton/switchbuttonshowwindow.h"
#include "schenckmain/schenckmain.h"
#include "test/test.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // SwitchButtonShowWindow swbtn_window;
    // swbtn_window.show();

    // PolarChartShowWindow chart_window;
    // chart_window.show();

    // BarChartShowWindow bar_window;
    // bar_window.show();

    // WaveChartShowWindow wave_window;
    // wave_window.show();

    // BalancingShowPhaseChart phase_window;
    // phase_window.resize(640, 480);
    // phase_window.show();

    // SchenckMain schenck_main;
    // schenck_main.show();

    // Test test;
    // test.show();

    // WindowManager windowManager;
    // windowManager.resize(1280, 800);
    // windowManager.show();

    // FileTemplateWindow fileTemplateWindow;
    // fileTemplateWindow.show();

    // MainWindow mainWindow;
    // mainWindow.show();

    // 创建主窗口
    // BaseWidget baseWidget;
    // baseWidget.show(); // 显示主窗口

    // 创建主窗口
    JP_MainWindow jp_main;

    // 定义版本号
    const QString VERSION = "v1.0.0";

    // 加载启动图片
    QPixmap pixmap("D:/shawei/temp/qt_custom_widget/assets/LaunchScreen.jpg");
    if(pixmap.isNull())
    {
        qWarning() << "Failed to load splash screen image!";
        return -1;
    }

    // 创建启动界面
    QSplashScreen splash(pixmap);
    splash.show();
    splash.showMessage(VERSION, Qt::AlignRight | Qt::AlignBottom, Qt::white);

    // 使用单个定时器：10秒后关闭启动界面并显示主窗口
    QTimer::singleShot(10000, [&]() {
        splash.close();  // 关闭启动界面
        jp_main.show();  // 显示主窗口
    });

    return a.exec();
}
