#include "file_manage.h"
#include "ui_file_manage.h"

file_manage::file_manage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::file_manage)
{
    ui->setupUi(this);

    connect(ui->btnBack, &QPushButton::clicked, this, &file_manage::requestBackToHome);
}

file_manage::~file_manage()
{
    delete ui;
}


void file_manage::on_help_btn_clicked()
{
    prompt_box *newbox = new prompt_box;
    newbox->show();
}
