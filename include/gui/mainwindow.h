#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class setting_date_time;
class home_page;
class file_manage;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // 按钮点击槽函数
    void Switch_date_time_clicked();
    void switchToHomePage();
    void Switch_file_manage_clicked();

private:
    Ui::MainWindow *ui;
    QStackedWidget *m_stackedWidget;  // 堆栈窗口管理器
    home_page *m_homePage;
    // 子界面对象
    setting_date_time *date_time_window;
    file_manage *m_file_manage;
};
#endif // MAINWINDOW_H
