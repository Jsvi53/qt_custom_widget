#pragma once
#include <QLabel>
#include <QPushButton>
#include <QWidget>


namespace Ui {
class JP_FileManager;
}

class FileItem;  // 文件项

// 文件管理界面类
class JP_FileManager : public QWidget
{
    Q_OBJECT
public:
    explicit JP_FileManager(QWidget *parent = nullptr);
    ~JP_FileManager();

private:
    Ui::JP_FileManager *ui;

};  // class JP_FileManager

// 文件项继承自QWidget和QPushButton
class FileItem : public QPushButton
{
    Q_OBJECT
public:
    explicit FileItem(QWidget *parent = nullptr);
    ~FileItem();

    void setFileIcon(const QString &iconPath);
    void setFileName(const QString &name);
    void setFileDate(const QString &date);
    void setFileType(const QString &type);
    void setFileSize(const QString &size);

private:
    QLabel *fileIcon;
    QLabel *fileName;
    QLabel *fileDate;
    QLabel *fileType;
    QLabel *fileSize;
};  // class FileItem