#pragma once
#include <QWidget>
#include <QLabel>
#include <QPushButton>

namespace Ui {
class FileManagerScreenUI;
}

// namespace FS {
// class FileManagerScreen;
// }

// 文件管理屏幕
class FileManagerScreen : public QWidget
{
    Q_OBJECT

public:
    explicit FileManagerScreen(QWidget *parent = nullptr);
    ~FileManagerScreen();

signals:
    void clicked(); // 确保信号存在

public slots:
    void buttonPressed();

private:
    Ui::FileManagerScreenUI *ui;
};

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