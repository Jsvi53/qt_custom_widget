#include "jp_resultgraphscreen/jp_resultgraph.h"
#include "ui_jp_resultgraph.h"
#include "utils/signalgenerator.h"
#include <QVBoxLayout>

JP_ResultGraph::JP_ResultGraph(QWidget *parent) : QWidget(parent), ui(new Ui::JP_ResultGraph)
{
    ui->setupUi(this);
    resultBigraph = new Bigraph(ui->upGraph);

    
    QVBoxLayout *upGraphLayout = new QVBoxLayout(ui->upGraph);
    upGraphLayout->addWidget(resultBigraph);




}

JP_ResultGraph::~JP_ResultGraph()
{
    delete ui;
}

