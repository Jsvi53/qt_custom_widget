#ifndef FILE_MANAGE_H
#define FILE_MANAGE_H

#include <QMainWindow>
#include "prompt_box.h"

QT_BEGIN_NAMESPACE
namespace Ui { class file_manage; }
QT_END_NAMESPACE

class file_manage : public QMainWindow
{
    Q_OBJECT

public:
    file_manage(QWidget *parent = nullptr);
    ~file_manage();

signals:
    void requestBackToHome();

private slots:
    void on_help_btn_clicked();

private:
    Ui::file_manage *ui;
};
#endif // MAINWINDOW_H
