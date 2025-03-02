/*** 
 * @Date: 2025-03-01 10:24:48
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-02 14:13:41
 * @FilePath: \qt_custom_widget\src\main.cpp
 */
#include <QApplication>

#include "qswitchbutton/switchbuttonshowwindow.h"
#include "chart/polarchartshowwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // SwitchButtonShowWindow swbtn_window;
    // swbtn_window.show();

    PolarChartShowWindow chart_window;
    chart_window.show();

    return a.exec();
}
