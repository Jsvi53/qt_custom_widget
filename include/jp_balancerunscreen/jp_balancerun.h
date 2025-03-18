#pragma once
#include <QWidget>

#include "chart/polardiagram.h"
#include "chart/spectrum.h"
#include "qswitchbutton/qswitchbutton.h"

namespace Ui {
class JP_BalanceRun;
}

class JP_BalanceRun : public QWidget
{
    Q_OBJECT

public:
    JP_BalanceRun(QWidget *parent = 0);
    ~JP_BalanceRun();

private:
    Ui::JP_BalanceRun *ui;
    SwitchButton      *liveSwitchButton;
    Spectrum          *spectrum;
    PolarDiagram      *polardiagram;
};
