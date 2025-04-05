#pragma once
#include <QWidget>

namespace Ui {
class JP_MainWindow;
}

class JP_MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit JP_MainWindow(QWidget *parent = nullptr);
    ~JP_MainWindow();

private:
    Ui::JP_MainWindow *ui;

};