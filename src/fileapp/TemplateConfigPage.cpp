#include "fileapp/TemplateConfigPage.h"
#include "ui_TemplateConfigPage.h"

TemplateConfigPage::TemplateConfigPage(QWidget *parent) : QWidget(parent), ui(new Ui::TemplateConfigPage)
{
    ui->setupUi(this);
}

TemplateConfigPage::~TemplateConfigPage()
{
    delete ui;
}

void TemplateConfigPage::loadParams(const TemplateParams &params) {
    // 将参数加载到界面控件中
    ui->sensorIdLineEdit->setText(params.sensorId);
    ui->maxRpmSpinBox->setValue(params.maxRpm);
    ui->calibrationFactorLineEdit->setText(QString::number(params.calibrationFactor));
}