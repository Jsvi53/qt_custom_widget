#include "jp_mainwindow/jp_mainwindow.h"
#include "ui_jp_mainwindow.h"

JP_MainWindow::JP_MainWindow(QWidget *parent) : QWidget(parent), ui(new Ui::JP_MainWindow)
{
    ui->setupUi(this);
}

JP_MainWindow::~JP_MainWindow()
{
    delete ui;
}