// test.cpp
#include "test/test.h"
#include "ui_test.h"

Test::Test(QWidget *parent) : QWidget(parent), ui(new Ui::Test) {
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, &Test::showMainInterface);
}

Test::~Test() {
    delete ui;
}
