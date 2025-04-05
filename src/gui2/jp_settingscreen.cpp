#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>
#include <QIcon>
#include <QInputDialog>
#include <QString>
#include <QVBoxLayout>

#include "jp_settingscreen.h"
#include "ui_jp_settingscreen.h"

JP_SettingScreen::JP_SettingScreen(QWidget *parent) : QWidget(parent), ui(new Ui::JP_SettingScreen)
{
    ui->setupUi(this);

    // 设置Setting Button的阴影效果
    QGraphicsDropShadowEffect *base_navigationbarshadow = new QGraphicsDropShadowEffect(this);
    base_navigationbarshadow->setOffset(0, 5);               // 阴影的偏移量
    base_navigationbarshadow->setColor(QColor(43, 43, 43));  // 阴影的颜色
    base_navigationbarshadow->setBlurRadius(10);             // 阴影圆角的大小
    ui->base_navigationbar->setGraphicsEffect(base_navigationbarshadow);

    // 设置 setting_taskbar 的阴影效果
    QGraphicsDropShadowEffect *taskbarShadow = new QGraphicsDropShadowEffect(this);
    taskbarShadow->setOffset(5, 5);               // 阴影的偏移量
    taskbarShadow->setColor(QColor(43, 43, 43));  // 阴影的颜色
    taskbarShadow->setBlurRadius(8);              // 阴影模糊半径
    ui->setting_taskbar->setGraphicsEffect(taskbarShadow);

    // 设置scrollAreaWidgetContents 的阴影效果
    QGraphicsDropShadowEffect *scrollAreaWidgetShadow = new QGraphicsDropShadowEffect(this);
    scrollAreaWidgetShadow->setOffset(5, 5);               // 阴影的偏移量
    scrollAreaWidgetShadow->setColor(QColor(43, 43, 43));  // 阴影的颜色
    scrollAreaWidgetShadow->setBlurRadius(8);              // 阴影模糊半径
    ui->scrollArea->setGraphicsEffect(scrollAreaWidgetShadow);

    // 创建 SettingItem 控件，将父对象设置为 ui->scrollAreaWidgetContents
    userName       = new SettingItem(ui->scrollAreaWidgetContents);
    companyName    = new SettingItem(ui->scrollAreaWidgetContents);
    department     = new SettingItem(ui->scrollAreaWidgetContents);
    streetAddress1 = new SettingItem(ui->scrollAreaWidgetContents);
    streetAddress2 = new SettingItem(ui->scrollAreaWidgetContents);
    postalCode     = new SettingItem(ui->scrollAreaWidgetContents);
    city           = new SettingItem(ui->scrollAreaWidgetContents);
    province       = new SettingItem(ui->scrollAreaWidgetContents);
    state          = new SettingItem(ui->scrollAreaWidgetContents);

    // 设置初始文本
    userName->itemName->setText(QString("用户名"));
    userName->setContentVisible(false);
    companyName->itemName->setText(QString("公司名称"));
    department->itemName->setText(QString("部门"));
    streetAddress1->itemName->setText(QString("街道地址1"));
    streetAddress2->itemName->setText(QString("街道地址2"));
    postalCode->itemName->setText(QString("邮政编码"));
    city->itemName->setText(QString("城市"));
    province->itemName->setText(QString("州/省"));
    state->itemName->setText(QString("国家/地区"));

    // 获取 setting_workspace 中的布局
    QVBoxLayout *layout = qobject_cast<QVBoxLayout *>(ui->scrollAreaWidgetContents->layout());
    if(!layout)
    {
        layout = new QVBoxLayout(ui->scrollAreaWidgetContents);  // 设置布局到 scrollAreaWidgetContents
        ui->scrollAreaWidgetContents->setLayout(layout);
    }

    layout->setSpacing(0);  // 添加控件到布局
    layout->addWidget(userName);
    layout->addWidget(companyName);
    layout->addWidget(department);
    layout->addWidget(streetAddress1);
    layout->addWidget(streetAddress2);
    layout->addWidget(postalCode);
    layout->addWidget(city);
    layout->addWidget(province);
    layout->addWidget(state);
}

JP_SettingScreen::~JP_SettingScreen()
{
    delete ui;
}

SettingItem::SettingItem(QWidget *parent) : QWidget(parent), contentVisible(false)
{
    setStyleSheet(
        "QWidget {"
        "border-bottom: 1px solid gray;"
        "border-top: 1px solid gray;"
        "border-radius: 0;"
        "padding: 0px;"  // 无内边距
        "}");

    // 创建控件
    inputButton = new QPushButton(this);
    itemName    = new QLabel("Item Name", this);
    item        = new QLabel("Item Content", this);

    // 设置按钮图标
    QIcon icon(":/setting_assets/setting_assets/icon_setting_pen_48.png");
    if(icon.isNull())
    {
        qDebug() << "图标加载失败！";
    }
    inputButton->setIcon(icon);
    inputButton->setIconSize(QSize(20, 20));
    inputButton->setText("");  // 清空按钮文本

    // 设置itemName、item大小
    itemName->setMinimumSize(QSize(800, 20));  // 设置 itemName 的最小大小
    item->setMinimumSize(QSize(800, 20));      // 设置 item 的最小大小
    inputButton->setMinimumSize(QSize(40, 40));

    // 设置字体
    QFont font("Microsoft YaHei", 14);  // 微软雅黑字体，12px
    itemName->setFont(font);            // 设置 itemName 的字体
    font.setPointSize(12);              // 设置字体大小
    item->setFont(font);                // 设置 item 的字体

    // 修改按钮样式表
    inputButton->setStyleSheet(
        "QPushButton {"
        " border: none;"  // 无边框
        "padding: 0px;"   // 无内边距
        "}");

    setContent("");            // 设置默认内容
    setContentVisible(false);  // 默认隐藏内容

    // 创建布局
    QHBoxLayout *mainLayout  = new QHBoxLayout(this);  // 主布局（水平）
    QVBoxLayout *rightLayout = new QVBoxLayout();      // 右侧布局（垂直）
    mainLayout->setContentsMargins(0, 0, 0, 0);        // 设置边距为 0
    mainLayout->setSpacing(0);                         // 设置控件之间的间隙为 0
    rightLayout->setContentsMargins(0, 0, 0, 0);       // 设置边距为 0
    rightLayout->setSpacing(0);                        // 设置控件之间的间隙为 0

    // 将控件添加到布局
    mainLayout->addWidget(inputButton, 5);   // 左侧按钮
    rightLayout->addWidget(itemName);        // 右侧上方标签
    rightLayout->addWidget(item);            // 右侧下方标签
    mainLayout->addLayout(rightLayout, 93);  // 将右侧布局添加到主布局
    setLayout(mainLayout);                   // 设置布局

    // 连接按钮的点击事件
    connect(inputButton, &QPushButton::clicked, this, &SettingItem::on_inputButton_clicked);
}

SettingItem::~SettingItem()
{
    // 不需要手动删除控件，Qt 的对象树机制会自动管理
}

// 设置内容
void SettingItem::setContent(const QString &content)
{
    realContent = content;   // 保存真实内容
    updateContentDisplay();  // 更新显示
}

// 设置内容是否可见
void SettingItem::setContentVisible(bool visible)
{
    contentVisible = visible;
    updateContentDisplay();  // 更新显示
}

// 获取内容是否可见
bool SettingItem::isContentVisible() const
{
    return contentVisible;
}

// 更新标签内容
void SettingItem::updateContentDisplay()
{
    if(contentVisible)
    {
        item->setText(realContent);  // 显示真实内容
    } else
    {
        item->setText(QString("*").repeated(realContent.length()));  // 用 * 替换真实内容
    }
}

// 唤起键盘输入
void SettingItem::on_inputButton_clicked()
{
}