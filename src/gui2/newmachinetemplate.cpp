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

    QVBoxLayout* scrollAreaLayout = new QVBoxLayout(templateListScrollArea);
    scrollAreaLayout->setContentsMargins(0, 0, 0, 0);
    scrollAreaLayout->setAlignment(Qt::AlignTop);

    for(int i = 0; i < 50; i ++)
    {
        MachineTemplate* machinetemplate = new MachineTemplate(templateListScrollArea);
        scrollAreaLayout->addWidget(machinetemplate);
    }
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
    machineTitleContainer = new QWidget(this);
    spotListWidget = new QListWidget(this);
    machineTtitleButton = new QPushButton("新建机器模板", this);
    addSpotButton      = new QPushButton("+", this);
    machineTitleContainer->setFixedHeight(50);

    QVBoxLayout* thisMainLayout = new QVBoxLayout(this);
    thisMainLayout->setContentsMargins(0, 0, 0, 0);
    thisMainLayout->setSpacing(0);
    thisMainLayout->setAlignment(Qt::AlignTop);
    thisMainLayout->addWidget(machineTitleContainer);
    thisMainLayout->addWidget(spotListWidget);

    machineTtitleButton->setFixedSize(250, 50);
    addSpotButton->setFixedSize(25, 25);
    machineTtitleButton->setIcon(QIcon(":/newtemplate/newtemplate_assets/icon_newtemplate_machine_blue.svg"));
    machineTtitleButton->setIconSize(QSize(25, 25));
    setLayout(thisMainLayout);

    // font设置
    QFont font = machineTtitleButton->font();
    font.setFamily("Microsoft YaHei");
    font.setPointSize(14);
    machineTtitleButton->setFont(font);
    font.setPointSize(18);
    addSpotButton->setFont(font);

    // 填充和对齐
    machineTtitleButton->setStyleSheet("QPushButton { text-align: left; padding-left: 50px; border:none;}");
    // 字体颜色白色，背景色rgb(41, 187, 220)，加粗,字体居中
    addSpotButton->setStyleSheet("QPushButton { background-color: rgb(18, 150, 219); color: white; border-radius: 3px; font-weight: bold; text-align: center; border:none;}");

    // 垂直布局
    QHBoxLayout* containerLayout = new QHBoxLayout(machineTitleContainer);
    containerLayout->setContentsMargins(0, 0, 20, 0);
    containerLayout->setSpacing(0);
    containerLayout->addWidget(machineTtitleButton);
    containerLayout->addWidget(addSpotButton);

    // 设置QListWidget的样式
    spotListWidget->setStyleSheet("QListWidget { background-color: rgb(127, 127, 127); border: none;}");
    for(int i = 1; i < 50; i++)
    {
        spotListWidget->addItem("机组模板" + QString::number(i));
    }

    machineTitleContainer->setLayout(containerLayout);
    spotListWidget->hide();
    connect(machineTtitleButton, &QPushButton::clicked, this, &MachineTemplate::on_machineTtitleButton_clicked);


}


MachineTemplate::~MachineTemplate()
{

}


void MachineTemplate::listwidgetShowToggle()
{
    if(isExpanded)
    {
        spotListWidget->show();
    }
    else
    {
        spotListWidget->hide();
    }
    isExpanded = !isExpanded;
}

void MachineTemplate::on_machineTtitleButton_clicked()
{
    listwidgetShowToggle();
}