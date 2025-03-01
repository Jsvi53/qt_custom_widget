#include "qswitchbutton/switchbuttonshowwindow.h"
#include "ui_switchbuttonshowwindow.h"

SwitchButtonShowWindow::SwitchButtonShowWindow(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SwitchButtonShowWindow)
{
    ui->setupUi(this);
}

SwitchButtonShowWindow::~SwitchButtonShowWindow()
{
    delete ui;
}
