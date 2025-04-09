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
    templateListScrollArea                     = new QScrollArea(ui->machineNaviContainerWidget);
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
    scrollAreaLayout->setAlignment(Qt::AlignTop);

    MachineTemplate* machineTemplate = new MachineTemplate(ui->varWorkSpaceWidget);
    if(ui->varWorkSpaceWidget->layout())
    {
        delete ui->varWorkSpaceWidget->layout();
    }
    scrollAreaLayout->addWidget(machineTemplate);
    scrollAreaLayout->addStretch();  // 添加伸缩项以填充剩余空间
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
    setFixedHeight(50);
    QVBoxLayout* MachineTemplateLayout = new QVBoxLayout(this);
    MachineTemplateLayout->setContentsMargins(0, 0, 0, 0);

    // 设置按钮
    machineTemplateButton = new QPushButton(QString("新机器"), this);
    machineTemplateButton->setFixedHeight(50);
    machineTemplateButton->setIcon(QIcon(":/newtemplate/newtemplate_assets/icon_newtemplate_machine_blue.svg"));
    machineTemplateButton->setIconSize(QSize(25, 25));
    QFont font = machineTemplateButton->font();
    font.setFamily("Microsoft YaHei");
    font.setPointSize(14);
    machineTemplateButton->setFont(font);  // font设置微软雅黑14号
    machineTemplateButton->setStyleSheet("QPushButton {text-align: left; padding-left: 50px; color: white; border:none;}");

    measurePointScrollContainer = new QScrollArea(this);
    measurePointScrollContainer->setStyleSheet("background-color: rgb(127, 127, 127); border: none;");
    measurePointScrollContainer->setWidgetResizable(true);
    measurePointScrollContainer->setFrameShape(QFrame::NoFrame);

    measurePointLayout = new QVBoxLayout(measurePointScrollContainer);
    measurePointLayout->setContentsMargins(0, 0, 0, 0);
    connect(machineTemplateButton, &QPushButton::clicked, this, &MachineTemplate::onPushButtonFoldClicked);
    MachineTemplateLayout->addWidget(machineTemplateButton);
    MachineTemplateLayout->addWidget(measurePointScrollContainer);
}

MachineTemplate::~MachineTemplate()
{
    // 清理资源
    delete labelExpanded;
    delete m_widgetPlane;
}

void MachineTemplate::expand()
{
    measurePointScrollContainer->show();
    IsExpanded = true;
    machineTemplateButton->setText("展开机组");

    // 如果还没有创建“已经展开”的标签，则创建并添加
    if (!labelExpanded)
    {
        labelExpanded = new QLabel("已经展开", this);
        labelExpanded->setFixedHeight(150);
        measurePointLayout->addWidget(labelExpanded);
    }
}

void MachineTemplate::collapse()
{
    measurePointScrollContainer->hide();
    IsExpanded = false;
    machineTemplateButton->setText("折叠机组");
}

void MachineTemplate::onPushButtonFoldClicked()
{
    if(IsExpanded)
    {
        collapse();
    } else
    {
        expand();
    }
}
