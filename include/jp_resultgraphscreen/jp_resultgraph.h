#pragma once

#include <QWidget>
#include "chart/bigraph.h"
#include "utils/signalgenerator.h"

namespace Ui{
    class JP_ResultGraph;
}

class JP_ResultGraph : public QWidget
{
    Q_OBJECT

public:
    explicit JP_ResultGraph(QWidget *parent = nullptr);
    ~JP_ResultGraph();

private:
    Ui::JP_ResultGraph *ui;
    Bigraph* resultBigraph;
    SineGenerator *sineGenerator;


};