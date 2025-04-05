#include "home_page.h"
#include "ui_home_page.h"

home_page::home_page(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::home_page)
{
    ui->setupUi(this);

    connect(ui->btnGotoSetPage, &QPushButton::clicked, this, &home_page::requestSwitchToSetPage);
    connect(ui->btnGotoFile, &QPushButton::clicked, this, &home_page::requestSwitchToFile);

}

home_page::~home_page()
{
    delete ui;
}

