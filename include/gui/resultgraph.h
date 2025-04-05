#pragma once

#include <QWidget>
#include <QProgressBar>
#include "bigraph.h"
#include "signalgenerator.h"
#include "signalgenerator2.h"

namespace Ui{
    class ResultGraphScreen;
}

class overallValuesPrograssBar;

class ResultGraph : public QWidget
{
    Q_OBJECT

public:
    explicit ResultGraph(QWidget *parent = nullptr);
    ~ResultGraph();

private:
    Ui::ResultGraphScreen *ui;
    Bigraph* resultBigraph;
    Bigraph* resultDownBigraph;
    SineGenerator *sineGenerator;
    UnbalanceVibrationGenerator *unbalanceVibrationGenerator;
    overallValuesPrograssBar *prograssBar_V_OP;
    overallValuesPrograssBar *prograssBar_V_RMS;
    overallValuesPrograssBar *prograssBar_A_OP;
    overallValuesPrograssBar *prograssBar_A_RMS;
};

// 更改进度条外观
class overallValuesPrograssBar : public QProgressBar
{
    Q_OBJECT
public:
    overallValuesPrograssBar(QWidget *parent = nullptr);
    ~overallValuesPrograssBar();
private:
    void paintEvent(QPaintEvent *event) override;
};