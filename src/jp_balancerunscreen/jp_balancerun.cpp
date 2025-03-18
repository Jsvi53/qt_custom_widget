/*** 
 * @Date: 2025-03-15 23:18:41
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-18 20:05:31
 * @FilePath: \qt_custom_widget\src\jp_balancerunscreen\jp_balancerun.cpp
 */
/***
 * @Date: 2025-03-18 10:18:56
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-18 13:25:31
 * @FilePath: \qt_custom_widget\src\jp_balancerunscreen\jp_balancerun.cpp
 */
#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>

#include "jp_balancerunscreen\jp_balancerun.h"
#include "ui_jp_balancerun.h"

JP_BalanceRun::JP_BalanceRun(QWidget *parent) : QWidget(parent), ui(new Ui::JP_BalanceRun)
{
    ui->setupUi(this);
    // 设置Setting Button的阴影效果
    QGraphicsDropShadowEffect *workspaceContainer_shadow = new QGraphicsDropShadowEffect(this);
    workspaceContainer_shadow->setOffset(0, 5);               // 阴影的偏移量
    workspaceContainer_shadow->setColor(QColor(43, 43, 43));  // 阴影的颜色
    workspaceContainer_shadow->setBlurRadius(10);             // 阴影圆角的大小
    ui->workspaceContainer->setGraphicsEffect(workspaceContainer_shadow);

    QGraphicsDropShadowEffect *buttomContainer_shadow = new QGraphicsDropShadowEffect(this);
    buttomContainer_shadow->setOffset(0, 5);               // 阴影的偏移量
    buttomContainer_shadow->setColor(QColor(43, 43, 43));  // 阴影的颜色
    buttomContainer_shadow->setBlurRadius(10);             // 阴影圆角的大小
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

JP_BalanceRun::~JP_BalanceRun()
{
    delete ui;
}
