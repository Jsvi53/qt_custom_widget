#include "setting_date_time.h"
#include "ui_setting_date_time.h"

setting_date_time::setting_date_time(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::setting_date_time)
{
    ui->setupUi(this);

    connect(ui->btnBack, &QPushButton::clicked, this, &setting_date_time::requestBackToHome);
}

setting_date_time::~setting_date_time()
{
    delete ui;
}

