#pragma once

#include <QWidget>

namespace Ui {
    class BaseWidget;
}


class BaseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BaseWidget(QWidget *parent = nullptr);
    ~BaseWidget();

private:
    Ui::BaseWidget *ui;
};