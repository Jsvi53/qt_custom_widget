#pragma once

#include <QGridLayout>
#include <QProgressBar>
#include <QVector>
#include <QWidget>

#include "bigraph.h"
#include "fftw3.h"

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

signals:
    void fftCompleted(QVector<double> freq, QVector<double> amp);

private slots:
    void handleFftResults(QVector<double> freq, QVector<double> amp);

private:
    static void computeFFT(const QVector<double> &baData, QVector<double> &freq, QVector<double> &amp);

    Ui::ResultGraphScreen *ui;
    Bigraph               *resultFreqBigraph;
    Bigraph               *resultTimeBigraph;

    overallValuesPrograssBar *prograssBar_V_OP;
    overallValuesPrograssBar *prograssBar_V_RMS;
    overallValuesPrograssBar *prograssBar_A_OP;
    overallValuesPrograssBar *prograssBar_A_RMS;
    QVector<double>           baData, deData, feData;
    QFutureWatcher<void>      fftWatcher;
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