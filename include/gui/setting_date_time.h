#ifndef SETTING_DATA_TIME_H
#define SETTING_DATA_TIME_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class setting_date_time; }
QT_END_NAMESPACE

class setting_date_time : public QMainWindow
{
    Q_OBJECT

public:
    explicit setting_date_time(QWidget *parent = nullptr);
    ~setting_date_time();

signals:
    void requestBackToHome();

private:
    Ui::setting_date_time *ui;
};

#endif // MAINWINDOW_H
