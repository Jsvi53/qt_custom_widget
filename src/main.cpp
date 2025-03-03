/*** 
 * @Date: 2025-03-01 10:24:48
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-03 20:36:10
 * @FilePath: \qt_custom_widget\src\main.cpp
 */
#include <QApplication>

#include "qswitchbutton/switchbuttonshowwindow.h"
#include "chart/polarchartshowwindow.h"
#include "chart/barchartshowwindow.h"
#include "chart/wavechartshowwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // SwitchButtonShowWindow swbtn_window;
    // swbtn_window.show();

    // PolarChartShowWindow chart_window;
    // chart_window.show();

    BarChartShowWindow bar_window;
    bar_window.show();

    // WaveChartShowWindow wave_window;
    // wave_window.show();

    return a.exec();
}
