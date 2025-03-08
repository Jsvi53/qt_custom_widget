/*** 
 * @Date: 2025-03-01 10:24:48
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-09 01:03:31
 * @FilePath: /qt_custom_widget/src/main.cpp
 */
#include <QApplication>

#include "qswitchbutton/switchbuttonshowwindow.h"
#include "chart/polarchartshowwindow.h"
#include "chart/barchartshowwindow.h"
#include "chart/wavechartshowwindow.h"
#include "chart/balancingshowphasechart.h"
#include "schenckmain/schenckmain.h"
#include "test/test.h"
#include "manager/managerwindow.h"
#include "fileapp/filetemplatewindow.h"
#include "mainwindow/mainwindow.h"

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

    MainWindow mainWindow;
    mainWindow.show();

    return a.exec();
}
