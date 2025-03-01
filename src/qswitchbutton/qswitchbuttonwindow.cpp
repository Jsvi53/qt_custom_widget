#include "include/qswitchbutton/qswitchbuttonwindow.h"
#include "ui_qswitchbuttonwindow.h"

QSwitchButtonWindow::QSwitchButtonWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QSwitchButtonWindow)
{
    ui->setupUi(this);
}

QSwitchButtonWindow::~QSwitchButtonWindow()
{
    delete ui;
}