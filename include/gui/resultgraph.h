#pragma once

#include <QGridLayout>
#include <QProgressBar>
#include <QVector>
#include <QWidget>

#include "bigraph.h"

namespace Ui {
class ResultGraphScreen;
}

class overallValuesPrograssBar;

class ResultGraph : public QWidget
{
    Q_OBJECT

public:
    explicit ResultGraph(QWidget *parent = nullptr);
    ~ResultGraph();

    void graphInit();
    void addOverallValue(overallValuesPrograssBar *overallBar, int value, QGridLayout *gridLayout);
    void loadCSVData(const QString &filePath, QVector<double> &baData, QVector<double> &deData, QVector<double> &feData);

private:
    Ui::ResultGraphScreen *ui;
    Bigraph               *resultFreqBigraph;
    Bigraph               *resultTimeBigraph;

    overallValuesPrograssBar    *prograssBar_V_OP;
    overallValuesPrograssBar    *prograssBar_V_RMS;
    overallValuesPrograssBar    *prograssBar_A_OP;
    overallValuesPrograssBar    *prograssBar_A_RMS;
    QVector<double>              baData, deData, feData;
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