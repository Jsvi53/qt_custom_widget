#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>
#include "balancerun.h"
#include "ui_balancerunscreen.h"

BalanceRun::BalanceRun(QWidget *parent) : QWidget(parent), ui(new Ui::BalanceRunScreen)
{
    ui->setupUi(this);
    // 设置Setting Button的阴影效果
    QGraphicsDropShadowEffect *workspaceContainer_shadow = new QGraphicsDropShadowEffect(this);
    workspaceContainer_shadow->setOffset(0, 5);
    workspaceContainer_shadow->setColor(QColor(43, 43, 43));
    workspaceContainer_shadow->setBlurRadius(10);
    ui->workspaceContainer->setGraphicsEffect(workspaceContainer_shadow);

    QGraphicsDropShadowEffect *buttomContainer_shadow = new QGraphicsDropShadowEffect(this);
    buttomContainer_shadow->setOffset(0, 5);
    buttomContainer_shadow->setColor(QColor(43, 43, 43));
    buttomContainer_shadow->setBlurRadius(10);
    ui->buttomContainer->setGraphicsEffect(buttomContainer_shadow);

    // 频谱图
    spectrum                    = new Spectrum(this);
    QHBoxLayout *spectrumLayout = new QHBoxLayout(ui->spectrumContainer);
    spectrumLayout->addWidget(spectrum);
    spectrumLayout->setContentsMargins(0, 0, 0, 0);
    spectrumLayout->setSpacing(0);
    ui->spectrumContainer->setLayout(spectrumLayout);

    // 相位图
    polardiagram                    = new PolarDiagram(ui->polarDiagramContainer);
    QVBoxLayout *polardiagramLayout = new QVBoxLayout(ui->polarDiagramContainer);
    polardiagramLayout->addWidget(polardiagram);
    polardiagramLayout->setContentsMargins(0, 0, 0, 0);
    polardiagramLayout->setSpacing(0);
    ui->polarDiagramContainer->setLayout(polardiagramLayout);

    // 添加liveSwitchButton
    liveSwitchButton = new SwitchButton(ui->workspaceSetBar);
    liveSwitchButton->setBackgroundColor(QColor(0xE4, 0xE4, 0xE4));
    liveSwitchButton->setDisabledColor(QColor(0x60, 0x5e, 0x5c));
    QHBoxLayout *switchWidgetLayout = new QHBoxLayout(ui->switchWidget);
    switchWidgetLayout->addWidget(liveSwitchButton, 3);
}

BalanceRun::~BalanceRun()
{
    delete ui;
}
