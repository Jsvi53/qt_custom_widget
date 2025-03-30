/***
 * @Date: 2025-03-29 18:09:00
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-29 19:22:01
 * @FilePath: \custom_widget\src\chart\3dchart.cpp
 */
#include <QDebug>
#include <QPainter>
#include <QtMath>
#include "chart/3dchart.h"

MultSpectrumChart3D::MultSpectrumChart3D(QWidget *parent) : QWidget(parent)
{
    setFixedSize(640, 480);
}

void MultSpectrumChart3D::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    draw3DGraph(painter);
}

void MultSpectrumChart3D::draw3DGraph(QPainter &painter)
{
    int width  = this->width();
    int height = this->height();

    // 设置画笔颜色
    painter.setPen(QPen(Qt::black, 2));

    // 绘制3D图形
    for(int i = 0; i < 10; i++)
    {
        int x1 = i * width / 10;
        int x2 = (i + 1) * width / 10;
        int y1 = height / 2 + qSin(i * 0.1) * height / 4;
        int y2 = height / 2 + qSin((i + 1) * 0.1) * height / 4;
        painter.drawLine(x1, y1, x2, y2);
    }
    // 绘制横向网格线
    for(int i = 0; i < 10; i++)
    {
        int y = i * height / 10;
        painter.drawLine(0, y, width, y);
    }
}