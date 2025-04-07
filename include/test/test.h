#pragma once
#include <QVector>
#include <QWidget>
#include <vector>
#include "qcustomplot.h"
#include "signalgenerator.h"
#include "signalgenerator2.h"

class VibrationGraph : public QWidget
{
public:
    explicit VibrationGraph(QWidget *parent = nullptr);
    ~VibrationGraph();

private:
    QCustomPlot                 *vibrationGraph;
    UnbalanceVibrationGenerator *vibrationGenerator;
    QVector<qreal>               vibValue;
    QVector<qreal>               vibTime;
    int                          speed = 3000;
};
