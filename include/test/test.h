#ifndef TEST_H
#define TEST_H

#include <QWidget>
#include "qtcustomplot/qcustomplot.h"  // 包含 QCustomPlot 头文件

namespace Ui {
class myWidget;
}

class myWidget : public QWidget {
    Q_OBJECT

public:
    explicit myWidget(QWidget *parent = nullptr);
    ~myWidget();

private:
    Ui::myWidget *ui;
    QCustomPlot *customPlot;  // 声明 QCustomPlot 指针

private slots:
    void configureCustomPlot();  // 声明 configureCustomPlot 函数
};

#endif // TEST_H