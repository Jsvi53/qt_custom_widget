#include <QGraphicsDropShadowEffect>
#include <QSpacerItem>

#include "filemanagerscreen.h"
#include "ui_filemanagerscreenui.h"


FileManagerScreen::FileManagerScreen(QWidget *parent) : QWidget(parent), ui(new Ui::FileManagerScreenUI)
{
    ui->setupUi(this);
    // 设置 filemanager_memeryArea 的阴影效果
    QGraphicsDropShadowEffect *memoryAreaShadow = new QGraphicsDropShadowEffect(this);
    memoryAreaShadow->setOffset(5, 5);
    memoryAreaShadow->setColor(QColor(43, 43, 43));
    memoryAreaShadow->setBlurRadius(8);
    ui->filemanager_memeryArea->setGraphicsEffect(memoryAreaShadow);

    // 设置 workspaceWidget 的阴影效果
    QGraphicsDropShadowEffect *workspaceShadow = new QGraphicsDropShadowEffect(this);
    workspaceShadow->setOffset(5, 5);
    workspaceShadow->setColor(QColor(43, 43, 43));
    workspaceShadow->setBlurRadius(8);
    ui->workspaceWidget->setGraphicsEffect(workspaceShadow);

    QVBoxLayout *layout = new QVBoxLayout(ui->scrollAreaWidgetContents);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    ui->scrollAreaWidgetContents->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    FileItem *item = new FileItem(ui->scrollAreaWidgetContents);
    item->setFileIcon(":/filemanager_assets/filemanager_assets/icon_filemanager_motor_50.png");
    item->setFileName("文件1");
    item->setFileDate("2025-03-14");
    item->setFileType("MT");
    item->setFileSize("1.2M");
    layout->addWidget(item);  // 将 FileItem 添加到布局中

    connect(item, &QPushButton::clicked, this, &FileManagerScreen::buttonPressed);


    QSpacerItem *vSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);       // 添加垂直间隔
    layout->addItem(vSpacer);

    ui->scrollAreaWidgetContents->setLayout(layout);  // 设置滚动区域的布局
}

void FileManagerScreen::buttonPressed()
{
    emit clicked();
}

FileManagerScreen::~FileManagerScreen()
{
    delete ui;
}

// 文件项
FileItem::FileItem(QWidget *parent) : QPushButton(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);  // 设置按钮的大小策略
    setFixedHeight(50);
    // 设置按钮的样式
    setStyleSheet(
        "QPushButton {"
        "border-bottom: 1px solid gray;"
        "border-top: 1px solid gray;"
        "border-radius: 0;"
        "padding: 0;"  // 设置按钮的内边距
        "}"

        "QPushButton:hover {"
        "background-color: lightgray;"
        "}"

        "QLabel {"
        "background-color: transparent;"  // 设置QLabel的背景颜色为透明
        "}"

        "QPushButton:hover QLabel#{"    // # 带不带后面的字符都能解决，标签灰色问题
        "background-color: lightgray;"  // 设置悬停时QLabel的背景颜色
        "}");

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
    fileName->setAlignment(Qt::AlignLeft);   // 左对齐
    fileDate->setAlignment(Qt::AlignRight);  // 右对齐
    fileType->setAlignment(Qt::AlignRight);
    fileSize->setAlignment(Qt::AlignLeft);

    // 设置文件项的布局
    QHBoxLayout *layout = new QHBoxLayout(this);
    QSpacerItem *hSpacer = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);  // 添加水平间隔
    layout->addWidget(fileIcon, 5, Qt::AlignLeft);
    layout->addWidget(fileName, 72, Qt::AlignLeft);
    layout->addWidget(fileDate, 11, Qt::AlignRight);
    layout->addWidget(fileType, 14, Qt::AlignRight);
    layout->addWidget(fileSize, 24, Qt::AlignRight);
    layout->addSpacerItem(hSpacer);  // 添加水平间隔
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
