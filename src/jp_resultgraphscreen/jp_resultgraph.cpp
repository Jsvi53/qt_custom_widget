#include "jp_resultgraphscreen/jp_resultgraph.h"
#include "ui_jp_resultgraph.h"

#include <QVBoxLayout>

JP_ResultGraph::JP_ResultGraph(QWidget *parent) : QWidget(parent), ui(new Ui::JP_ResultGraph)
{
    ui->setupUi(this);
    resultBigraph = new Bigraph(ui->upGraph);
    sineGenerator = new SineGenerator(this);
    sineGenerator->configure(1000, 1, 44100);

    QVector<qreal> waveform = sineGenerator->generate(1000);
    resultBigraph->addFrontSeriesPoint(0, 0);
    resultBigraph->addBackSeriesPoint(0, 0);
    for(int i = 0; i < waveform.size(); i++)
    {
        resultBigraph->addFrontSeriesPoint(i, waveform[i]);
        resultBigraph->addBackSeriesPoint(i, waveform[i]);
    }
    resultBigraph->addFrontSeriesPoint(1000, 0);
    resultBigraph->addBackSeriesPoint(1000, 0);
    resultBigraph->adjustAxisRanges();

    QVBoxLayout *upGraphLayout = new QVBoxLayout(ui->upGraph);
    upGraphLayout->addWidget(resultBigraph);

}

JP_ResultGraph::~JP_ResultGraph()
{
    delete ui;
}

