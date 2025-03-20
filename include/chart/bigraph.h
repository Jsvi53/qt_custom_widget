/*** 
 * @Date: 2025-03-19 19:05:25
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-20 23:02:16
 * @FilePath: \qt_custom_widget\include\chart\bigraph.h
 */
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

    QChart      *frontChart;
    QChart      *backChart;
    QValueAxis  *frontAxisX;
    QValueAxis  *frontAxisY;
    QValueAxis  *backAxisX;
    QValueAxis  *backAxisY;

    // 更新图表位置的槽函数
    void updateChartPositions(int angle);

    // 添加数据接口
    void addFrontSeriesPoint(qreal x, qreal y);
    void addBackSeriesPoint(qreal x, qreal y);

    // 清空数据接口
    void clearFrontSeries();
    void clearBackSeries();

    // 调整坐标轴范围
    void adjustAxisRanges();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QChartView  *frontChartView;
    QChartView  *backChartView;
    QLineSeries *frontSeries;
    QLineSeries *backSeries;


    // 图表大小
    int chartWidth  = 700;
    int chartHeight = 190;

    // 图表位置
    int frontChartX = 0;    // 表视口原点在左上，相对0,0的位置
    int frontChartY = 129;  // 319-212
    int backChartX;
    int backChartY;
    int positionBaseLength = 170;  // 半径
    int positionBaseAngle  = 45;   // 角度（以度为单位）

    QRectF combinedRange;// 存储合并后的坐标范围
    // 添加以下成员变量
    QRectF combinedDataRange; // 合并后的实际数据范围（不含边距）
    QRectF displayRange;      // 显示范围（包含边距）

    void         initFrontChart();
    void         initBackChart();
    void         drawConnections();

    void         connectAxisTicks(QPainter *painter, QChart *backChart, QLineSeries *backSeries, QChart *frontChart, QLineSeries *frontSeries, bool isXAxis);
    QList<qreal> getTickValues(QValueAxis *axis);
    QRectF calculateSeriesRange(QLineSeries *series);
};

#endif  // __Bigraph_H__