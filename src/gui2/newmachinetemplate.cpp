#include <QBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QSpacerItem>
#include <QVBoxLayout>

#include "newmachinetemplate.h"
#include "thememanager.h"
#include "ui_newmachinetemplatescreenui.h"

NewMachineTemplateScreen::NewMachineTemplateScreen(QWidget* parent) : QWidget(parent), ui(new Ui::NewMachineTemplateScreenUI)
{
    ui->setupUi(this);
    auto& themeMgr = ThemeManager::instance();
    themeMgr.registerWidget(ui->WorkSpace, "workarea");

    MachineTrainTemplate* machinetraintemplate = new MachineTrainTemplate(ui->machineNaviContainerWidget);
    templateListScrollArea = new QScrollArea(ui->machineNaviContainerWidget);
    templateListScrollArea->setStyleSheet("background-color: rgb(127, 127, 127); border: none;");
    templateListScrollArea->setWidgetResizable(true);
    templateListScrollArea->setFrameShape(QFrame::NoFrame);

    if(ui->machineNaviContainerWidget->layout())
    {
        delete ui->machineNaviContainerWidget->layout();
    }

    QVBoxLayout* layout = new QVBoxLayout(ui->machineNaviContainerWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(machinetraintemplate);
    layout->addWidget(templateListScrollArea);
    ui->machineNaviContainerWidget->setLayout(layout);

    // 添加templateListScrollArea的布局
    QVBoxLayout* scrollAreaLayout = new QVBoxLayout(templateListScrollArea);
    scrollAreaLayout->setContentsMargins(0, 0, 0, 0);
    scrollAreaLayout->setSpacing(0);
    scrollAreaLayout->setAlignment(Qt::AlignTop);

    MachineTemplate * machineTemplate = new MachineTemplate(ui->varWorkSpaceWidget);
    if(ui->varWorkSpaceWidget->layout())
    {
        delete ui->varWorkSpaceWidget->layout();
    }
    scrollAreaLayout->addWidget(machineTemplate);
    scrollAreaLayout->addStretch(); // 添加伸缩项以填充剩余空间
    templateListScrollArea->setLayout(scrollAreaLayout);
}

NewMachineTemplateScreen::~NewMachineTemplateScreen()
{
    delete ui;
}

MachineTrainTemplate::MachineTrainTemplate(QWidget* parent) : QWidget(parent)
{
    setFixedSize(257, 50);
    templateButton    = new QPushButton("新建机组模板", this);
    templateAddButton = new QPushButton("+", this);
    templateButton->setFixedSize(250, 50);
    templateAddButton->setFixedSize(25, 25);
    templateButton->setIcon(QIcon(":/newtemplate/newtemplate_assets/icon_newtemplate_machinetrain_blue.png"));
    templateButton->setIconSize(QSize(25, 25));

    // font设置 微软雅黑 14号
    QFont font = templateButton->font();
    font.setFamily("Microsoft YaHei");
    font.setPointSize(14);
    templateButton->setFont(font);
    font.setPointSize(18);
    templateAddButton->setFont(font);

    // 填充和对齐
    templateButton->setStyleSheet("QPushButton { text-align: left; padding-left: 5px; border:none;}");
    // 字体颜色白色，背景色rgb(41, 187, 220)，加粗,字体居中
    templateAddButton->setStyleSheet("QPushButton { background-color: rgb(18, 150, 219); color: white; border-radius: 3px; font-weight: bold; text-align: center; border:none;}");
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 20, 0);  // 设置布局的边距为0
    layout->setSpacing(0);                    // 设置布局的间距为0
    layout->addWidget(templateButton);
    layout->addWidget(templateAddButton);
    setLayout(layout);
}

MachineTrainTemplate::~MachineTrainTemplate()
{
}

MachineTemplate::MachineTemplate(QWidget* parent) : QWidget(parent)
{
    QVBoxLayout* verticalLayout = new QVBoxLayout(this);
    verticalLayout->setContentsMargins(0, 0, 0, 0);  // 设置布局的边距为0
    pushButtonFold = new QPushButton(this);
    measurePointWidget = new QWidget(this);
    measurePointWidgetLayout = new QVBoxLayout(measurePointWidget);
    measurePointWidgetLayout->setContentsMargins(0, 0, 0, 0);  // 设置布局的边距为0
    labelMachineName = new QLabel(this);
    labelMachineName->setText("名称");
    QHBoxLayout* layout = new QHBoxLayout(pushButtonFold);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addStretch(1);
    layout->addWidget(labelMachineName);
    connect(pushButtonFold, &QPushButton::clicked, this, &MachineTemplate::onPushButtonFoldClicked);
    verticalLayout->addWidget(pushButtonFold);
    verticalLayout->addWidget(measurePointWidget);
}

MachineTemplate::~MachineTemplate()
{
    // 清理资源
    delete labelExpanded;
    delete m_widgetPlane;
}

void MachineTemplate::expand()
{
    measurePointWidget->show();
    m_bIsExpanded = true;
    labelMachineName->setText("展开机组");

    // 如果还没有创建“已经展开”的标签，则创建并添加
    if (!labelExpanded)
    {
        labelExpanded = new QLabel("已经展开", this);
        measurePointWidgetLayout->addWidget(labelExpanded);
    }
}

void MachineTemplate::collapse()
{
    measurePointWidget->hide();
    m_bIsExpanded = false;
    labelMachineName->setText("折叠机组");

    // 如果存在“已经展开”的标签，则移除
    if (labelExpanded)
    {
        measurePointWidgetLayout->removeWidget(labelExpanded);
        labelExpanded->deleteLater();
        labelExpanded = nullptr;
    }
}

void MachineTemplate::onPushButtonFoldClicked()
{
    if (m_bIsExpanded)
    {
        collapse();
    }
    else
    {
        expand();
    }
}

void MachineTemplate::setWidget(const QString& title, QWidget* widget)
{
    if (m_widgetPlane)
    {
        measurePointWidgetLayout->removeWidget(m_widgetPlane);
        m_widgetPlane->deleteLater();
        m_widgetPlane = nullptr;
    }
    pushButtonFold->setText(title);
    measurePointWidgetLayout->addWidget(widget);
    m_widgetPlane = widget;
}