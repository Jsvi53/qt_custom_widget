#pragma once
#include <QWidget>

#include "polardiagram.h"
#include "qswitchbutton.h"
#include "spectrum.h"


namespace Ui {
    class BalanceRunScreen;
}

class BalanceRun : public QWidget
{
    Q_OBJECT

public:
    BalanceRun(QWidget *parent = nullptr);
    ~BalanceRun();

private:
    Ui::BalanceRunScreen *ui;
    SwitchButton         *liveSwitchButton;
    Spectrum             *spectrum;
    PolarDiagram         *polardiagram;
};
