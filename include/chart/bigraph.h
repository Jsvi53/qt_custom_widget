#ifndef __Bigraph_H__
#define __Bigraph_H__

#include <QGraphicsLineItem>  // 用于绘制连接线
#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

QT_CHARTS_USE_NAMESPACE

class Bigraph : public QWidget
{
    Q_OBJECT
public:
    explicit Bigraph(QWidget *parent = nullptr);
    ~Bigraph();

    // 更新图表位置的槽函数
    void updateChartPositions(int angle);

    // 添加数据接口
    void addFrontSeriesPoint(qreal x, qreal y);
    void addBackSeriesPoint(qreal x, qreal y);

    // 清空数据接口
    void clearFrontSeries();
    void clearBackSeries();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QChart      *frontChart;
    QChart      *backChart;
    QChartView  *frontChartView;
    QChartView  *backChartView;
    QLineSeries *frontSeries;
    QLineSeries *backSeries;
    QValueAxis  *frontAxisX;
    QValueAxis  *frontAxisY;
    QValueAxis  *backAxisX;
    QValueAxis  *backAxisY;

    // 图表大小
    int chartWidth  = 700;
    int chartHeight = 212;

    // 图表位置
    int frontChartX = 0;    // 表视口原点在左上，相对0,0的位置
    int frontChartY = 107;  // 319-212
    int backChartX;
    int backChartY;
    int positionBaseLength = 150;  // 半径
    int positionBaseAngle  = 45;   // 角度（以度为单位）

    void         initFrontChart();
    void         initBackChart();
    void         drawConnections();

    void         connectAxisTicks(QPainter *painter, QChart *backChart, QLineSeries *backSeries, QChart *frontChart, QLineSeries *frontSeries, bool isXAxis);
    QList<qreal> getTickValues(QValueAxis *axis);
};

#endif  // __Bigraph_H__