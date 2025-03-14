/***
 * @Date: 2025-03-14 09:07:33
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-14 14:40:25
 * @FilePath: \qt_custom_widget\src\jp_filemanagerscreen\jp_filemanager.cpp
 */
#include <QHBoxLayout>
#include <QSpacerItem>

#include "jp_filemanagerscreen/jp_filemanager.h"
#include "ui_jp_filemanager.h"

// 文件管理界面类
JP_FileManager::JP_FileManager(QWidget *parent) : QWidget(parent), ui(new Ui::JP_FileManager)
{
    ui->setupUi(this);

    // 设置文件管理界面的布局，使用垂直布局，顶着父窗口的上下左右边界
    if(ui->scrollAreaWidgetContents->layout())
    {
        delete ui->scrollAreaWidgetContents->layout();  // 清除现有布局
    }
    QVBoxLayout *layout = new QVBoxLayout(ui->scrollAreaWidgetContents);
    layout->setContentsMargins(0, 0, 0, 0);  // 设置边距为 0
    layout->setSpacing(0);                   // 设置控件之间的间隙为 0

    // 设置 scrollAreaWidgetContents 的大小策略
    ui->scrollAreaWidgetContents->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // 添加文件项
    for(int i = 0; i < 30; i++)
    {
        FileItem *item = new FileItem(ui->scrollAreaWidgetContents);
        item->setFileIcon(":/filemanager_assets/icon_filemanager_motor_50.png");
        item->setFileName("文件" + QString::number(i + 1));
        item->setFileDate("2025-03-14");
        item->setFileType("文件夹");
        item->setFileSize("1.2M");
        layout->addWidget(item);  // 将 FileItem 添加到布局中
    }
    // 添加垂直间隔
    QSpacerItem *vSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    layout->addItem(vSpacer);  // 添加垂直间隔

    // 设置滚动区域的布局
    ui->scrollAreaWidgetContents->setLayout(layout);
    ui->workspaceScrollArea->setWidgetResizable(true);  // 允许滚动区域调整内容大小
}

JP_FileManager::~JP_FileManager()
{
    delete ui;
}

// 文件项
FileItem::FileItem(QWidget *parent) : QPushButton(parent)
{
    // 设置按钮的样式
    // setStyleSheet("QPushButton {border-bottom: 1px solid gray; border-top: 1px solid gray; }");
    setStyleSheet(
        "QPushButton {"
        "border-bottom: 1px solid gray;"
        "border-top: 1px solid gray;"
        "border-radius: 0;"
        "padding: 0;"  // 设置按钮的内边距
        "}"
        // "QPushButton:hover {"
        // "background-color: lightgray;"
        // "}"
        // "QPushButton:hover QLabel {"
        // "background-color: lightgray;"  // 设置悬停时QLabel的背景颜色
        // "}"
        );
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
    font.setPointSize(12);
    fileName->setFont(font);
    fileDate->setFont(font);
    fileType->setFont(font);
    fileSize->setFont(font);
    // 设置字体颜色
    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::black);
    fileName->setPalette(palette);
    fileDate->setPalette(palette);
    fileType->setPalette(palette);
    fileSize->setPalette(palette);
    // 设置字体对齐方式
    fileName->setAlignment(Qt::AlignLeft);   // 左对齐
    fileDate->setAlignment(Qt::AlignRight);  // 右对齐
    fileType->setAlignment(Qt::AlignRight);
    fileSize->setAlignment(Qt::AlignLeft);

    // 设置文件项的布局
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(fileIcon, 5, Qt::AlignLeft);
    layout->addWidget(fileName, 70, Qt::AlignLeft);
    layout->addWidget(fileDate, 15, Qt::AlignRight);
    layout->addWidget(fileType, 16, Qt::AlignRight);
    layout->addWidget(fileSize, 21, Qt::AlignRight);
    setLayout(layout);
}

FileItem::~FileItem()
{
}

// 设置文件项的图标
void FileItem::setFileIcon(const QString &iconPath)
{
    // 为图标资源文件qrc添加前缀
    fileIcon->setPixmap(QPixmap(iconPath).scaled(20, 20));
}

// 设置文件项的文件名
void FileItem::setFileName(const QString &name)
{
    fileName->setText(name);
}

// 设置文件项的文件日期
void FileItem::setFileDate(const QString &date)
{
    fileDate->setText(date);
}

// 设置文件项的文件类型
void FileItem::setFileType(const QString &type)
{
    fileType->setText(type);
}

// 设置文件项的文件大小
void FileItem::setFileSize(const QString &size)
{
    fileSize->setText(size);
}

// #include "jp_filemanager.moc"