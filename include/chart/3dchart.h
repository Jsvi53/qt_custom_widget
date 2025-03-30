/***
 * @Date: 2025-03-29 18:08:49
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-29 18:09:43
 * @FilePath: \custom_widget\include\chart\3dchart.h
 */
#pragma once
#include <QWidget>

class MultSpectrumChart3D : public QWidget
{
    Q_OBJECT
public:
    explicit MultSpectrumChart3D(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void draw3DGraph(QPainter &painter);
};