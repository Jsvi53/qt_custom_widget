/*** 
 * @Date: 2025-03-01 10:24:48
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-01 12:37:45
 * @FilePath: \qt_custom_widget\src\main.cpp
 */
#include "mainwindow.h"
//#include "qswitchbutton/qswitchbuttonwindow.h"  // 包含 QSwitchButtonWindow 头文件
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    // QSwitchButtonWindow window;
    // window.show();
    return a.exec();
}
