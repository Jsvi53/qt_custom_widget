/*** 
 * @Date: 2025-03-04 09:45:24
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-04 09:55:52
 * @FilePath: \qt_custom_widget\src\schenckshowmainwindow\schencshowkmainwindow.cpp
 */
#include "schenckshowmainwindow/schencshowkmainwindow.h"
#include "ui_schencshowkmainwindow.h"

SchencShowkMainWindow::SchencShowkMainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SchencShowkMainWindow)
{
    ui->setupUi(this);
}

SchencShowkMainWindow::~SchencShowkMainWindow()
{
    delete ui;
}
