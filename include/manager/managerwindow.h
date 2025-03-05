// managerwindow.h
#ifndef MANAGERWINDOW_H
#define MANAGERWINDOW_H

#include <QWidget>  // 确保包含 QWidget 头文件
#include <QStackedWidget>

class SchenckMain;
class Test;

class WindowManager : public QWidget {  // 确保继承自 QWidget
    Q_OBJECT

public:
    WindowManager(QWidget *parent = nullptr);
    ~WindowManager();

private slots:
    void showMainInterface();
    void showSubInterface();

private:
    QStackedWidget *stackedWidget;
    SchenckMain *schenckMain;
    Test *test;
};

#endif // MANAGERWINDOW_H