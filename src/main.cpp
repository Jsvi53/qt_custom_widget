/*** 
 * @Date: 2025-03-01 10:24:48
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-01 17:26:30
 * @FilePath: \qt_custom_widget\src\main.cpp
 */
#include "mainwindow.h"
#include "qswitchbutton/switchbuttonshowwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    SwitchButtonShowWindow switchbuttonwindow;
    switchbuttonwindow.show();
    return a.exec();
}
