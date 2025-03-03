#ifndef WaveCHARTSHOWWINDOW_H
#define WaveCHARTSHOWWINDOW_H

#include <QFrame>
#include "chart/wavechart.h"

namespace Ui {
class WaveChartShowWindow;
}

class WaveChartShowWindow : public QFrame
{
    Q_OBJECT

public:
    explicit WaveChartShowWindow(QWidget *parent = nullptr);
    ~WaveChartShowWindow();

private:
    Ui::WaveChartShowWindow *ui;
    BalancingWaveChart *waveChartObj;
};

#endif // WaveCHARTSHOWWINDOW_H
