#include <QHBoxLayout>

#include "jp_balancerunscreen\jp_balancerun.h"
#include "ui_jp_balancerun.h"


JP_BalanceRun::JP_BalanceRun(QWidget *parent) : QWidget(parent), ui(new Ui::JP_BalanceRun)
{
    ui->setupUi(this);
    // 频谱图
    spectrum = new Spectrum(this);
    QHBoxLayout *spectrumLayout = new QHBoxLayout(ui->spectrumContainer);
    spectrumLayout->addWidget(spectrum);
    spectrumLayout->setContentsMargins(0, 0, 0, 0);
    spectrumLayout->setSpacing(0);
    ui->spectrumContainer->setLayout(spectrumLayout);

}

JP_BalanceRun::~JP_BalanceRun()
{
    delete ui;
}
