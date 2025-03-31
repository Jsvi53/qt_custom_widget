/***
 * @Date: 2025-03-01 10:24:48
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-23 18:26:17
 * @FilePath: \qt_custom_widget\src\main.cpp
 */

#include <QApplication>
#include <QDebug>
#include <QQmlApplicationEngine>
#include <QScreen>
#include <QSplashScreen>
#include <QSurfaceFormat>
#include <QTimer>

#include "basemodule/basewidget.h"
#include "chart/3dchart.h"
#include "chart/balancingshowphasechart.h"
#include "chart/barchartshowwindow.h"
#include "chart/polarchartshowwindow.h"
#include "chart/wavechartshowwindow.h"
#include "databasetest/databasetest.h"
#include "fileapp/filetemplatewindow.h"
#include "jp_balancerunscreen\jp_balancerun.h"
#include "jp_balancesetupscreen/jp_balancesetup.h"
#include "jp_filemanagerscreen/jp_filemanager.h"
#include "jp_mainwindow/jp_mainwindow.h"
#include "jp_resultgraphscreen/jp_resultgraph.h"
#include "jp_routesscreen/jp_routes.h"
#include "jp_settingscreen/jp_settingscreen.h"
#include "mainwindow/mainwindow.h"
#include "manager/managerwindow.h"
#include "onsitebalancer/home.h"
#include "onsitebalancer/onsitebalancer.h"
#include "qswitchbutton/switchbuttonshowwindow.h"
#include "schenckmain/schenckmain.h"
#include "test/test.h"
#include "test_qmlmerge/test_qmlmerge.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*
        // 使用 QML 方式显示主窗口
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);   // 开启高DPI缩放
        QQmlApplicationEngine engine;
        const QUrl url(QStringLiteral("qrc:qmlwidget/qmlmain.qml"));
        QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                         &a, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);   // 队列连接
        engine.load(url);   // 加载 QML 文件
    */

    /*
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

        Test test;
        test.show();

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
    */
    /*
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
    */

    /*
        JP_MainWindow jp_main;
        jp_main.show();
    */
    // 创建主窗口

    /*
        // 创建Setting窗口
        JP_SettingScreen jp_setting;
        jp_setting.show();
    */

    /*
        // 创建FileManager窗口
        // JP_FileManager jp_filemanager;
        // jp_filemanager.show();
    */

    /*
        JP_BalanceSetup balancesetup;
        balancesetup.show();
    */

    /*
        JP_BalanceRun balancerun;
        balancerun.show();
    */

    /*
    JP_ResultGraph resultgraph;
    resultgraph.show();
    */

    /*
    HomeScreen home;
    home.show();
    */



    // 全局渲染设置

    /*
        // QApplication::setAttribute(Qt::AA_UseOpenGLES);
        // QApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
        // OnSiteBalancer onsitebalancer;
        // onsitebalancer.show();
    */

    /*
        MultSpectrumChart3D spetrumchart3d;
        spetrumchart3d.show();
    */

   MultSpectrumChart3D spetrumchart3d;
   spetrumchart3d.show();

    /*
        JP_RoutesScreen routesscreen;
        routesscreen.show();
    */

/*
    Test_qmlMerge qmlwindow;
    qmlwindow.show();
*/


    return a.exec();
}
