/*** 
 * @Date: 2025-03-08 19:58:06
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-08 21:50:29
 * @FilePath: /qt_custom_widget/src/schenckmain/schenckmain.cpp
 */
// schenckmain.cpp
#include "schenckmain/schenckmain.h"
#include "ui_schenckmain.h"

SchenckMain::SchenckMain(QWidget *parent) : QWidget(parent), ui(new Ui::SchenckMain) {
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, &SchenckMain::showSubInterface);
}

SchenckMain::~SchenckMain() { delete ui; }