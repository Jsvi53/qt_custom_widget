/***
 * @Date: 2025-03-30 14:47:59
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-30 15:18:34
 * @FilePath: \custom_widget\src\jp_routesscreen\jp_routes.cpp
 */
#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QSpacerItem>

#include "jp_routesscreen/jp_routes.h"
#include "ui_jp_routesscreen.h"

JP_RoutesScreen::JP_RoutesScreen(QWidget *parent) : QWidget(parent), ui(new Ui::JP_RoutesScreen)
{
    ui->setupUi(this);
    // 设置 workspaceWidget 的阴影效果
    QGraphicsDropShadowEffect *workspaceShadow = new QGraphicsDropShadowEffect(this);
    workspaceShadow->setOffset(5, 5);               // 阴影的偏移量
    workspaceShadow->setColor(QColor(43, 43, 43));  // 阴影的颜色
    workspaceShadow->setBlurRadius(8);              // 阴影模糊
    ui->workspaceWidget->setGraphicsEffect(workspaceShadow);

    // 清除布局
    if(ui->scrollAreaWidgetContents->layout())
    {
        delete ui->scrollAreaWidgetContents->layout();  // 清除现有布局
    }
    QVBoxLayout *layout = new QVBoxLayout(ui->scrollAreaWidgetContents);
    layout->setContentsMargins(0, 0, 0, 0);                                                       // 设置边距为 0
    layout->setSpacing(0);                                                                        // 设置控件之间的间隙为 0
    ui->scrollAreaWidgetContents->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);  // 设置 scrollAreaWidgetContents 的大小策略

    TaskItem *item = new TaskItem(ui->scrollAreaWidgetContents);
    item->setFileIcon(":/balancetask_assets/balance_task_assets/icon_balance_task1_red.svg");
    item->setFileName("任务1");
    item->setFileDate("2025-03-14");
    item->setFileType("文件夹");
    item->setFileSize("1.2M");
    item->select();
    layout->addWidget(item);
    TaskItem *item2 = new TaskItem(ui->scrollAreaWidgetContents);
    item2->setFileIcon(":/balancetask_assets/balance_task_assets/icon_balance_task1_red.svg");
    item2->setFileName("任务2");
    item2->setFileDate("2025-03-14");
    item2->setFileType("文件夹");
    item2->setFileSize("1.2M");
    layout->addWidget(item2);

    // 添加垂直间隔
    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addItem(spacer);  // 添加垂直间隔

    ui->scrollAreaWidgetContents->setLayout(layout);    // 设置滚动区域的布局
    ui->workspaceScrollArea->setWidgetResizable(true);  // 允许滚动区域调整内容大小
}

JP_RoutesScreen::~JP_RoutesScreen()
{
    delete ui;
}

TaskItem::TaskItem(QWidget *parent) : QPushButton(parent)
{
    setStyleSheet(
        "QPushButton {"
        "border-bottom: 1px solid gray;"
        "border-top: 1px solid gray;"
        "border-radius: 0;"
        "padding: 0;"  // 设置按钮的内边距
        "}"

        "QLabel {"
        "background-color: transparent;"
        "}");
    // 设置按钮的大小策略
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    // 设置按钮的固定高度
    setFixedHeight(50);

    fileIcon = new QLabel(this);
    fileName = new QLabel(this);
    fileDate = new QLabel(this);
    fileType = new QLabel(this);
    fileSize = new QLabel(this);

    // 设置字体样式
    QFont font;
    font.setFamily("Microsoft YaHei");
    font.setPointSize(14);
    fileName->setFont(font);
    fileDate->setFont(font);
    fileType->setFont(font);
    fileSize->setFont(font);

    // 设置字体对齐方式
    fileName->setAlignment(Qt::AlignLeft);  // 左对齐
    fileDate->setAlignment(Qt::AlignLeft);  // 左对齐
    fileType->setAlignment(Qt::AlignLeft);  // 左对齐
    fileSize->setAlignment(Qt::AlignLeft);  // 左对齐

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(fileIcon);
    layout->addWidget(fileName);
    layout->addWidget(fileDate);
    layout->addWidget(fileType);
    layout->addWidget(fileSize);
    setLayout(layout);
}

TaskItem::~TaskItem()
{
}

void TaskItem::setFileIcon(const QString &iconPath)
{
    QPixmap pixmap(iconPath);
    pixmap = pixmap.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    fileIcon->setPixmap(pixmap);
}

void TaskItem::setFileName(const QString &name)
{
    fileName->setText(name);
}

void TaskItem::setFileDate(const QString &date)
{
    fileDate->setText(date);
}

void TaskItem::setFileType(const QString &type)
{
    fileType->setText(type);
}

void TaskItem::setFileSize(const QString &size)
{
    fileSize->setText(size);
}

void TaskItem::select()
{
    isSelected = true;
    updateStyle();
}

void TaskItem::deselect()
{
    isSelected = false;
    updateStyle();
}

void TaskItem::updateStyle()
{
    if(isSelected)
    {
        // 设置背景颜色，窗口边框，子控件边框不受影响
        setStyleSheet(
            "QPushButton {"
            "background-color: lightgray;"
            "border: none;"
            "border-bottom: 1px solid rgb(70, 70, 70);"
            "border-left: 10px solid rgb(70, 70, 70);"
            "border-radius: 0;"
            "}"

            "QLabel {"
            "background-color: transparent;"
            "border: none;"
            "}");
    } else
    {
        setStyleSheet(
            "QPushButton {"
            "background-color: rgb(228, 228, 228);"
            "border: none;"
            "border-bottom: 1px solid rgb(70, 70, 70);"
            "border-radius: 0;"
            "}"

            "QLabel {"
            "background-color: transparent;"
            "border: none;"
            "}");
    }
}

void TaskItem::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        select();  // 选中当前项
    }
    QPushButton::mousePressEvent(event);  // 调用父类的事件处理
}