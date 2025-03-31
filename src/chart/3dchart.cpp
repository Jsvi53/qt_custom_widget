#include <QDebug>
#include <QPainter>
#include <QtMath>
#include "chart/3dchart.h"

MultSpectrumChart3D::MultSpectrumChart3D(QWidget *parent) : Q3DScatter()
{
    // 创建一个 QWidget 容器来嵌入 Q3DScatter
    graphContainer = new QWidget(this);
    graphContainer->setContentsMargins(0, 0, 0, 0);
    graphContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    graphContainer->setMinimumSize(800, 600);
    iniGraph3D();
}

MultSpectrumChart3D::~MultSpectrumChart3D()
{
}


void MultSpectrumChart3D::setData(const QVector<QVector<QVector3D>> &data)
{
   
}