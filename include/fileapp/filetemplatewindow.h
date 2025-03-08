#ifndef FILETEMPLATEWINDOW_H
#define FILETEMPLATEWINDOW_H

#include <QWidget>
#include <QFileSystemModel>
#include "fileapp/TemplateParams.h"

namespace Ui {
    class FileTemplateWindow;
}

class FileTemplateWindow : public QWidget
{
    Q_OBJECT
public:
    explicit FileTemplateWindow(QWidget *parent = nullptr);
    ~FileTemplateWindow();  // 声明析构函数

signals:
    void templateFileSelected(const TemplateParams &params); // 关键信号

public slots:
    void onFileClicked(const QModelIndex &index); // 关键槽函数

private:
    Ui::FileTemplateWindow *ui;
    QFileSystemModel *model;

    TemplateParams parseTemplateFile(const QString &filePath); // 解析模板文件
    void createTemplateFile(const QString &filePath); // 创建模板文件
};

#endif // FILETEMPLATEWINDOW_H