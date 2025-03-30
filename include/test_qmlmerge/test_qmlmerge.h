#pragma once
#include <QDebug>
#include <QQuickView>
#include <QQuickWidget>
#include <QVBoxLayout>
#include <QWidget>

// qwidget 中使用qml
class Test_qmlMerge : public QWidget
{
    Q_OBJECT
public:
    Test_qmlMerge(QWidget *parent = nullptr);
    ~Test_qmlMerge();

private:
    QQuickWidget *quickWidget;
};