#ifndef TEST_H
#define TEST_H

#include <QWidget>

#include "qtcustomplot/qcustomplot.h"
#include "utils/signalgenerator2.h"

#define SAMPLENUM 10000

class vibrationWaveGraph : public QWidget
{
    Q_OBJECT

public:
    explicit vibrationWaveGraph(QWidget *parent = nullptr);
    ~vibrationWaveGraph() ;
    void vibgraphShow();

private:
    QCustomPlot                 *vibgraph;
    std::vector<double>          generatedValue;
    std::vector<double>          timeValue;
    double                       speed                    = 3000.0;
    UnbalanceVibrationGenerator *unbalanceSignalGenerator = nullptr;
};

#endif  // TEST_H