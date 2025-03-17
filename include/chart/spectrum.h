#ifndef __SPECTRUM_H
#define __SPECTRUM_H
#include <QtCharts/QPolarChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QSplineSeries>
#include <QWidget>

#include "chart/spectrum.h"

QT_CHARTS_USE_NAMESPACE
// 构造函数

class Spectrum : public QWidget
{
    Q_OBJECT
public:
    explicit Spectrum(QWidget *parent = nullptr);
    ~Spectrum();

private:
    QChart *spectrumChart;
    QSplineSeries *spectrumSeries;
    QValueAxis *Xaxis;
    QValueAxis *Yaxis;
    QChartView *spectrumChartView;

    void initSpectrum();
};
#endif // __SPECTRUM_H
