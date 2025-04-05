#include "wavechartshowwindow.h"
#include "wavechart.h"
#include "ui_wavechartshowwindow.h"

WaveChartShowWindow::WaveChartShowWindow(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::WaveChartShowWindow)
{
    ui->setupUi(this);
    waveChartObj = new BalancingWaveChart(this);
    waveChartObj->resize(640, 480);
    waveChartObj->show();

}

WaveChartShowWindow::~WaveChartShowWindow()
{
    delete ui;
    delete waveChartObj;
}
