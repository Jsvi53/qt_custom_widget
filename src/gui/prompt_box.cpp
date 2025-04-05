#include "prompt_box.h"
#include "ui_prompt_box.h"

prompt_box::prompt_box(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::prompt_box)
{
    ui->setupUi(this);
}

prompt_box::~prompt_box()
{
    delete ui;
}
