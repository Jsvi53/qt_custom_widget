#ifndef BIGRAPH_H
#define BIGRAPH_H

#include <QPainter>
#include <QVector>
#include <QWidget>

#include "qcustomplot.h"

class Bigraph : public QWidget
{
    Q_OBJECT
public:
    explicit Bigraph(QWidget *parent = nullptr);
    ~Bigraph();

    // 图表控件
    QCustomPlot *frontPlot;
    QCustomPlot *backPlot;

    QCPGraph *frontGraph;     // 前端图表
    QCPGraph *backGraph;      // 后端图表
    QRectF    combinedRange;  // 合并的范围

    // 坐标轴
    QCPAxis *frontAxisX;
    QCPAxis *frontAxisY;
    QCPAxis *backAxisX;
    QCPAxis *backAxisY;

    void updateChartPositions(int angle);
    void addFrontSeriesPoint(double x, double y);
    void addBackSeriesPoint(double x, double y);
    void addFrontSeriesPoint(QVector<double> x, QVector<double> y);
    void addBackSeriesPoint(QVector<double> x, QVector<double> y);
    void clearFrontSeries();
    void clearBackSeries();
    void adjustAxisRanges();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int positionBaseLength = 170;
    int positionBaseAngle  = 45;
    int frontChartX        = 0;
    int frontChartY        = 129;
    int backChartX;
    int backChartY;

    void          initFrontPlot();
    void          initBackPlot();
    void          connectAxisTicks(QPainter *painter, bool isXAxis);
    QList<double> getTickValues(QCPAxis *axis);
};

#endif  // BIGRAPH_H