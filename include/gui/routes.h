#pragma once
#include <QLabel>
#include <QPushButton>
#include <QWidget>

namespace Ui {
class RoutesScreen;
}

class TaskItem;

class Routes : public QWidget
{
    Q_OBJECT

public:
    explicit Routes(QWidget *parent = nullptr);
    ~Routes();

private:
    Ui::RoutesScreen *ui;

};  // class Routes

// 文件项继承自QWidget和QPushButton
class TaskItem : public QPushButton
{
    Q_OBJECT
public:
    explicit TaskItem(QWidget *parent = nullptr);
    ~TaskItem();

    void setFileIcon(const QString &iconPath);
    void setFileName(const QString &name);
    void setFileDate(const QString &date);
    void setFileType(const QString &type);
    void setFileSize(const QString &size);

    void select();    // 选中当前项
    void deselect();  // 取消选中当前项

    // 事件重写
    void mousePressEvent(QMouseEvent *event) override;

private:
    bool isSelected;

    QLabel *fileIcon;
    QLabel *fileName;
    QLabel *fileDate;
    QLabel *fileType;
    QLabel *fileSize;

    void updateStyle();
};  // class TaskItem