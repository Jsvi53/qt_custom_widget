/*** 
 * @Date: 2025-03-20 08:13:59
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-20 22:20:18
 * @FilePath: \qt_custom_widget\include\jp_resultgraphscreen\jp_resultgraph.h
 */
#pragma once

#include <QWidget>
#include <QProgressBar>
#include "chart/bigraph.h"
#include "utils/signalgenerator.h"
#include "utils/signalgenerator2.h"

namespace Ui{
    class JP_ResultGraph;
}

class overallValuesPrograssBar;

class JP_ResultGraph : public QWidget
{
    Q_OBJECT

public:
    explicit JP_ResultGraph(QWidget *parent = nullptr);
    ~JP_ResultGraph();

private:
    Ui::JP_ResultGraph *ui;
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