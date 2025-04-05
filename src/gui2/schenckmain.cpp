// schenckmain.cpp
#include "schenckmain.h"
#include "ui_schenckmain.h"

SchenckMain::SchenckMain(QWidget *parent) : QWidget(parent), ui(new Ui::SchenckMain) {
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, &SchenckMain::showSubInterface);
}

SchenckMain::~SchenckMain() { delete ui; }