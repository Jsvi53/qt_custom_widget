#include <QBoxLayout>
#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QRadioButton>
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
    screenTimer  = new QTimer(this);
    threeButtons = new ThreeButtons(ui->menuWidget, machineTrainIconPaths, 2);
    threeButtons->setGeometry(555, 0, 50, 50);
    twoButtons = new ThreeButtons(ui->menuWidget, machineTrainIconPaths, 2);
    twoButtons->setGeometry(555, 0, 50, 50);
    threeButtons->hide();

    MachineTrainTemplate* machinetraintemplate = new MachineTrainTemplate(ui->machineNaviContainerWidget);
    templateListScrollArea                     = new QScrollArea(ui->machineNaviContainerWidget);
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

    MachineTemplate* machinetemplate = new MachineTemplate(templateListScrollArea);
    machinetemplate->addListItem("速度测量点", MachineTemplate::Speed);
    machinetemplate->addListItem("振动测量点", MachineTemplate::Vibration);
    scrollAreaLayout->addWidget(machinetemplate);
    templateListScrollArea->setLayout(scrollAreaLayout);

    // 添加工作区域控件
    workspaceWidget = new QStackedWidget(ui->varWorkSpaceWidget);
    workspaceWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QVBoxLayout* workAreaLayout = new QVBoxLayout(ui->varWorkSpaceWidget);
    workAreaLayout->setContentsMargins(0, 0, 0, 0);
    workAreaLayout->setSpacing(0);
    workAreaLayout->addWidget(workspaceWidget);
    ui->varWorkSpaceWidget->setLayout(workAreaLayout);
    MachineTrainPropertyWorkspace* machineTrainPropertyWorkspace = new MachineTrainPropertyWorkspace(workspaceWidget);
    workspaceWidget->addWidget(machineTrainPropertyWorkspace);
    workspaceWidget->setCurrentIndex(0);

    MachinePropertyWidget* machinePropertyWidget = new MachinePropertyWidget(workspaceWidget);
    workspaceWidget->addWidget(machinePropertyWidget);

    SpeedMeasureSpotPropertyWidget* speedMeasureSpotPropertyWidget = new SpeedMeasureSpotPropertyWidget(workspaceWidget);
    workspaceWidget->addWidget(speedMeasureSpotPropertyWidget);

    VibrationMeasureSpotPropertyWidget* vibrationMeasureSpotPropertyWidget = new VibrationMeasureSpotPropertyWidget(workspaceWidget);
    workspaceWidget->addWidget(vibrationMeasureSpotPropertyWidget);

    groupWidget = new GroupWidget(workspaceWidget);
    workspaceWidget->addWidget(groupWidget);


    // 切换工作区域
    connect(twoButtons->buttons[1], &QPushButton::clicked, this, [=]() { workspaceWidget->setCurrentIndex(4); threeButtons->show(); twoButtons->hide(); });
    connect(machinetraintemplate->templateButton, &QPushButton::clicked, this, [=]() { workspaceWidget->setCurrentIndex(0); twoButtons->show(); threeButtons->hide(); });
    connect(machinetemplate->machineTtitleButton, &QPushButton::clicked, this, [=]() { workspaceWidget->setCurrentIndex(1); });

    // 切换测量点工作区域
    connect(machinetemplate->spotListWidget, &QListWidget::currentRowChanged, this, &NewMachineTemplateScreen::onCurrentRowChanged);
    // 同步标题
    connect(screenTimer, &QTimer::timeout, this, [=]() {
        if(machineTrainPropertyWorkspace->name->getTitleLabel()->text().isEmpty())
        {
            machineTrainPropertyWorkspace->name->getTitleLabel()->setText("新建机组模板");
            machinetraintemplate->setMachineTrainTemplateTitle("新建机组模板");

        } else
        {
            QString title = machineTrainPropertyWorkspace->name->getTitleLabel()->text();
            machinetraintemplate->setMachineTrainTemplateTitle(title);
        }

        if(machinePropertyWidget->name->getTitleLabel()->text().isEmpty())
        {
            machinePropertyWidget->name->getTitleLabel()->setText("新建机器模板");
            machinetemplate->setMachineTemplateTitle("新建机器模板");
        } else
        {
            QString title = machinePropertyWidget->name->getTitleLabel()->text();
            machinetemplate->setMachineTemplateTitle(title);
        }
    });
    screenTimer->start(500);
}

NewMachineTemplateScreen::~NewMachineTemplateScreen()
{
    delete ui;
}

void NewMachineTemplateScreen::onCurrentRowChanged(int currentRow)
{
    if(currentRow == 0)
    {
        workspaceWidget->setCurrentIndex(2);
    } else if(currentRow == 1)
    {
        workspaceWidget->setCurrentIndex(3);
    }
}

MachineTrainTemplate::MachineTrainTemplate(QWidget* parent) : QWidget(parent)
{
    setFixedSize(257, 50);

    templateButton    = new QPushButton("新建机组模板", this);
    templateAddButton = new QPushButton(this);
    templateButton->setFixedSize(250, 50);
    templateAddButton->setFixedSize(30, 30);
    templateButton->setIcon(QIcon(":/newtemplate/newtemplate_assets/icon_newtemplate_machinetrain_blue.png"));
    templateButton->setIconSize(QSize(20, 20));
    templateAddButton->setIcon(QIcon(":/newtemplate/newtemplate_assets/icon_newtemplate_plus_white.png"));
    templateAddButton->setIconSize(QSize(20, 20));

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

void MachineTrainTemplate::setMachineTrainTemplateTitle(QString title)
{
    templateButton->setText(title);
}

MachineTemplate::MachineTemplate(QWidget* parent) : QWidget(parent)
{
    setFixedWidth(257);
    setStyleSheet("border: none;");
    machineTitleContainer = new QWidget(this);
    addSpotButton         = new QPushButton(this);
    spotListWidget        = new QListWidget(this);
    machineTtitleButton   = new QPushButton("新建机器模板", machineTitleContainer);
    collapseExpandButton  = new QPushButton(machineTitleContainer);

    QVBoxLayout* thisMainLayout = new QVBoxLayout(this);
    thisMainLayout->setContentsMargins(0, 0, 0, 0);
    thisMainLayout->setSpacing(0);
    thisMainLayout->setAlignment(Qt::AlignTop);
    thisMainLayout->addWidget(machineTitleContainer);
    thisMainLayout->addWidget(spotListWidget);

    collapseExpandButton->setFixedSize(35, 50);
    if(!isExpanded && !isListEmpty)
    {
        collapseExpandButton->setIcon(QIcon(":/arrow/arrow_assets/left.png"));
    }
    addSpotButton->setIconSize(QSize(20, 20));

    machineTtitleButton->setFixedSize(250, 50);
    machineTtitleButton->setIcon(QIcon(":/newtemplate/newtemplate_assets/icon_newtemplate_machine_blue.svg"));
    machineTtitleButton->setIconSize(QSize(25, 25));
    setLayout(thisMainLayout);

    addSpotButton->setFixedSize(30, 30);
    addSpotButton->setIconSize(QSize(20, 20));

    // font设置
    QFont font = machineTtitleButton->font();
    font.setFamily("Microsoft YaHei");
    font.setPointSize(14);
    machineTtitleButton->setFont(font);

    // 填充和对齐
    machineTtitleButton->setStyleSheet("QPushButton { text-align: left; border:none;}");
    // 字体颜色白色，背景色rgb(41, 187, 220)，加粗,字体居中
    addSpotButton->setStyleSheet("QPushButton { background-color: rgb(18, 150, 219); color: white; border-radius: 3px; font-weight: bold; text-align: center; border:none;}");

    // 垂直布局
    QHBoxLayout* containerLayout = new QHBoxLayout(machineTitleContainer);
    containerLayout->setContentsMargins(0, 0, 20, 0);
    containerLayout->setSpacing(0);
    containerLayout->addWidget(collapseExpandButton);
    containerLayout->addWidget(machineTtitleButton);
    containerLayout->addWidget(addSpotButton);

    // spotListWidget设置
    spotListWidget->setStyleSheet("QListWidget{padding: 0; padding-left: 50px; margin: 0;}");
    spotListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    spotListWidget->setIconSize(QSize(25, 25));
    machineTitleContainer->setFixedHeight(50);
    font.setPointSize(14);

    // spotListWidget设置
    spotListWidget->setStyleSheet("QListWidget{padding: 0; padding-left: 50px; margin: 0;}");
    spotListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    spotListWidget->setIconSize(QSize(25, 25));
    machineTitleContainer->setFixedHeight(50);
    font.setPointSize(14);
    machineTitleContainer->setLayout(containerLayout);
    spotListWidget->hide();

    // 初始化定时器
    listCheckTimer = new QTimer(this);
    connect(listCheckTimer, &QTimer::timeout, this, &MachineTemplate::checkListEmpty);
    listCheckTimer->start(500);  // 每1000ms检查一次
    connect(collapseExpandButton, &QPushButton::clicked, this, &MachineTemplate::on_collapseExpandButton_clicked);
}

MachineTemplate::~MachineTemplate()
{
}

void MachineTemplate::listwidgetShowToggle()
{
    if(!isExpanded && !isListEmpty)
    {
        collapseExpandButton->setIcon(QIcon(":/arrow/arrow_assets/down.png"));
        spotListWidget->show();
        isExpanded = !isExpanded;
        return;
    }

    if(isExpanded && !isListEmpty)
    {
        collapseExpandButton->setIcon(QIcon(":/arrow/arrow_assets/left.png"));
        spotListWidget->hide();
        isExpanded = !isExpanded;
        return;
    }
}

void MachineTemplate::on_collapseExpandButton_clicked()
{
    listwidgetShowToggle();
}

// 更新添加按钮图标
void MachineTemplate::__updateAddSpotButtonIcon(bool isempty)
{
    if(isListEmpty)
    {
        addSpotButton->setIcon(QIcon(":/newtemplate/newtemplate_assets/icon_newtemplate_plus_white.png"));
        addSpotButton->setIconSize(QSize(20, 20));
    } else
    {
        addSpotButton->setIcon(QIcon(":/newtemplate/newtemplate_assets/icon_newtemplate_copy_white.png"));
        addSpotButton->setIconSize(QSize(20, 20));
    }
}

void MachineTemplate::checkListEmpty()
{
    spotListWidget->count() == 0 ? isListEmpty = true : isListEmpty = false;
    __updateAddSpotButtonIcon(isListEmpty);
}

void MachineTemplate::addListItem(const QString& itemName, MeasureType Type)
{
    QListWidgetItem* item = new QListWidgetItem(itemName);
    switch(Type)
    {
        case Speed:
            item->setIcon(QIcon(":/home/home_assets/icon_speed_template.svg"));
            break;
        case Vibration:
            item->setIcon(QIcon(":/balancesetup/balancingsetup_assets/icon_balancesetup_triangle.svg"));
            break;
        default:
            break;
    }

    item->setText(itemName);
    font.setPointSize(14);
    item->setFont(font);
    item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    spotListWidget->addItem(item);
}

void MachineTemplate::setMachineTemplateTitle(QString title)
{
    machineTtitleButton->setText(title);
}

CommonPropertyItem::CommonPropertyItem(QWidget* parent, bool listNeeded) : QWidget(parent), isListNeeded(listNeeded)
{
    // 创建控件
    titleContainer     = new QWidget(this);
    titleSubContainer  = new QWidget(titleContainer);
    iconButton         = new QPushButton(titleContainer);
    titleLabel         = new QLabel(titleContainer);
    propertyLabel      = new QLabel(titleContainer);
    propertyListWidget = new QListWidget(this);

    // 设置控件属性
    titleContainer->setFixedHeight(80);
    iconButton->setFixedSize(80, 80);
    iconButton->setIconSize(QSize(20, 20));

    if(!isListNeeded || isListEmpty)
    {
        iconButton->setIcon(QIcon(":/commonIcon/commonicon_assets/icon_common_assets_gray.png"));
    } else
    {
        iconButton->setIcon(QIcon(":/arrow/arrow_assets/left.png"));
    }

    titleLabel->setFixedHeight(50);
    propertyLabel->setFixedHeight(30);
    propertyListWidget->setStyleSheet(
        "QListWidget{padding: 0; padding-left: 50px; margin: 0;}"
        "QListWidget::item { height: 80px;}");
    propertyListWidget->setFixedHeight(300);
    propertyListWidget->setIconSize(QSize(20, 20));
    propertyListWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    propertyListWidget->hide();

    // 设置字体
    font.setFamily("Microsoft YaHei");
    font.setPointSize(12);
    font.setItalic(true);
    palette.setColor(QPalette::WindowText, Qt::darkGray);
    propertyLabel->setFont(font);
    propertyLabel->setPalette(palette);
    font.setPointSize(14);
    font.setItalic(false);
    titleLabel->setFont(font);

    // 布局设置
    thisMainLayout = new QVBoxLayout(this);
    thisMainLayout->setContentsMargins(0, 0, 0, 0);
    thisMainLayout->setSpacing(0);
    thisMainLayout->addWidget(titleContainer);
    thisMainLayout->addWidget(propertyListWidget);

    thisMainLayout->setAlignment(Qt::AlignTop);
    setLayout(thisMainLayout);

    QHBoxLayout* titleLayout = new QHBoxLayout(titleContainer);
    titleLayout->setContentsMargins(0, 0, 0, 0);
    titleLayout->setSpacing(0);
    titleLayout->addWidget(iconButton);
    titleLayout->addWidget(titleSubContainer);
    titleLayout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    titleContainer->setLayout(titleLayout);

    QVBoxLayout* titleSubLayout = new QVBoxLayout(titleSubContainer);
    titleSubLayout->setContentsMargins(0, 0, 0, 0);
    titleSubLayout->setSpacing(0);
    titleSubLayout->addWidget(titleLabel);
    titleSubLayout->addWidget(propertyLabel);
    titleSubLayout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    titleSubContainer->setLayout(titleSubLayout);

    listCheckTimer = new QTimer(this);
    connect(listCheckTimer, &QTimer::timeout, this, &CommonPropertyItem::listCheck);
    listCheckTimer->start(500);
    connect(iconButton, &QPushButton::clicked, this, &CommonPropertyItem::on_iconButton_clicked);
    connect(propertyListWidget, &QListWidget::currentItemChanged, this, &CommonPropertyItem::updateItemIcon);
}

CommonPropertyItem::~CommonPropertyItem()
{
}

void CommonPropertyItem::listwidgetShowToggle()
{
    if(isExpanded && isListNeeded)
    {
        iconButton->setIcon(QIcon(":/arrow/arrow_assets/left.png"));
        propertyListWidget->hide();
        isExpanded = !isExpanded;
        return;
    }

    if(!isExpanded && isListNeeded)
    {
        iconButton->setIcon(QIcon(":/arrow/arrow_assets/down.png"));
        propertyListWidget->show();
        isExpanded = !isExpanded;
        return;
    }
}

void CommonPropertyItem::on_iconButton_clicked()
{
    if(isListEmpty && isListNeeded)
    {
        iconButton->setIcon(QIcon());  // 取消iconButton的图标
        return;
    }

    if(!isListEmpty && isListNeeded)
    {
        listwidgetShowToggle();
        return;
    }
}

void CommonPropertyItem::listCheck()
{
    if(propertyListWidget->count() == 0 && isListNeeded)
    {
        isListEmpty = true;
        return;
    }

    if(propertyListWidget->count() != 0 && isListNeeded)
    {
        isListEmpty = false;
        return;
    }
}

void CommonPropertyItem::setTitle(const QString& title)
{
    titleLabel->setText(title);
}

void CommonPropertyItem::setProperty(const QString& property)
{
    propertyLabel->setText(property);
}

void CommonPropertyItem::addListItems(const QVector<QString>& itemNames)
{
    propertyListWidget->clear();
    for(const auto& itemName : itemNames)
    {
        QListWidgetItem* item = new QListWidgetItem(itemName);
        item->setIcon(QIcon(":/commonIcon/commonicon_assets/icon_common_radiobutton_off_gray.png"));
        item->setFont(font);
        propertyListWidget->addItem(item);
    }
    isListEmpty = false;
}

void CommonPropertyItem::updateItemIcon(QListWidgetItem* current, QListWidgetItem* previous)
{
    if(current)
    {
        current->setIcon(QIcon(":/commonIcon/commonicon_assets/icon_common_radiobutton_on_gray.png"));
        propertyLabel->setText(current->text());
    }

    if(previous)
    {
        previous->setIcon(QIcon(":/commonIcon/commonicon_assets/icon_common_radiobutton_off_gray.png"));
    }
}

QLabel* CommonPropertyItem::getTitleLabel() const
{
    return propertyLabel;
}

MachineTrainPropertyWorkspace::MachineTrainPropertyWorkspace(QWidget* parent) : QScrollArea(parent)
{
    // 设置大小策略
    setStyleSheet("border-radius: 0px; border: none;");
    setWidgetResizable(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    // 创建控件
    titleLabel = new QLabel("    资产信息", this);
    titleLabel->setFont(QFont("Microsoft YaHei", 12));
    contentContainer = new QWidget();
    setWidget(contentContainer);

    name           = new CommonPropertyItem(this);
    type           = new CommonPropertyItem(this, true);
    direction      = new CommonPropertyItem(this, true);
    power          = new CommonPropertyItem(this);
    speed          = new CommonPropertyItem(this);
    referenceshaft = new CommonPropertyItem(this, true);
    base           = new CommonPropertyItem(this, true);

    // 设置控件属性
    titleLabel->setFixedHeight(50);
    name->setTitle("名称");
    type->setTitle("类型");
    QVector<QString> typeList = {"设备机组", "生产线", "汽轮机"};
    type->addListItems(typeList);

    direction->setTitle("方向");
    QVector<QString> directionList = {"水平", "垂直", "轴向"};
    direction->addListItems(directionList);

    power->setTitle("功率");
    speed->setTitle("速度");

    referenceshaft->setTitle("参考轴");
    referenceshaft->addListItems(QVector<QString>({"新加机器测试"}));

    base->setTitle("基础");
    QVector<QString> baseList = {"柔性", "刚性"};
    base->addListItems(baseList);

    QVBoxLayout* mainLayout = new QVBoxLayout(contentContainer);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(name);
    mainLayout->addWidget(type);
    mainLayout->addWidget(direction);
    mainLayout->addWidget(power);
    mainLayout->addWidget(speed);
    mainLayout->addWidget(referenceshaft);
    mainLayout->addWidget(base);
    contentContainer->setLayout(mainLayout);
}

MachineTrainPropertyWorkspace::~MachineTrainPropertyWorkspace()
{
}

GroupWidget::GroupWidget(QWidget* parent) : QScrollArea(parent)
{
    // 设置大小策略
    setStyleSheet("border-radius: 0px; border: none;");
    setWidgetResizable(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    addGroupButton = new CommonPropertyItem(this, false);
    addGroupButton->iconButton->setStyleSheet(
        "QPushButton {background-color:rgb(18, 150, 219);"
        "border:none; "
        "icon: url(::/newtemplate/newtemplate_assets/icon_newtemplate_plus_white.png);}");

    thisMainLayout = new QVBoxLayout(this);
    thisMainLayout->setContentsMargins(0, 0, 0, 0);
    thisMainLayout->setSpacing(0);
    thisMainLayout->setAlignment(Qt::AlignTop);

    thisMainLayout->addWidget(addGroupButton);
    setLayout(thisMainLayout);

    connect(addGroupButton->iconButton, &QPushButton::clicked, this, [=]() {
        CommonPropertyItem* groupItem = addGroup();
        groupItemMap.insert(groupItem->getTitleLabel()->text(), groupItem);
    });
}

CommonPropertyItem* GroupWidget::addGroup()
{
    int n = this->children().count();
    CommonPropertyItem* groupItem = new CommonPropertyItem(this);
    groupItem->setTitle(QString("机组%1").arg(n - 1));
    groupItem->iconButton->setIcon(QIcon(":/newtemplate/newtemplate_assets/icon_newtemplate_spot_orange.svg"));
    thisMainLayout->addWidget(groupItem);
    setLayout(thisMainLayout);
    return groupItem;
}

GroupWidget::~GroupWidget()
{
}

MachinePropertyWidget::MachinePropertyWidget(QWidget* parent) : QScrollArea(parent)
{
    // 设置大小策略
    setStyleSheet("border-radius: 0px; border: none;");
    setWidgetResizable(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    // 创建控件
    titleLabel = new QLabel("    机器信息", this);
    titleLabel->setFont(QFont("Microsoft YaHei", 12));
    contentContainer = new QWidget();
    setWidget(contentContainer);

    name  = new CommonPropertyItem(this);
    type  = new CommonPropertyItem(this, true);
    power = new CommonPropertyItem(this);
    speed = new CommonPropertyItem(this);

    // 设置控件属性
    titleLabel->setFixedHeight(50);
    name->setTitle("名称");
    type->setTitle("类型");
    QVector<QString> typeList = {"设备机组", "生产线", "汽轮机"};
    type->addListItems(typeList);

    power->setTitle("功率");
    speed->setTitle("速度");

    QVBoxLayout* mainLayout = new QVBoxLayout(contentContainer);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(name);
    mainLayout->addWidget(type);
    mainLayout->addWidget(power);
    mainLayout->addWidget(speed);

    contentContainer->setLayout(mainLayout);
}

MachinePropertyWidget::~MachinePropertyWidget()
{
}

CommonMeasureSpotWidget::CommonMeasureSpotWidget(QWidget* parent) : QScrollArea(parent)
{
}
CommonMeasureSpotWidget::~CommonMeasureSpotWidget()
{
}

SpeedMeasureSpotPropertyWidget::SpeedMeasureSpotPropertyWidget(QWidget* parent) : CommonMeasureSpotWidget(parent)
{
    // 设置大小策略
    setStyleSheet("border-radius: 0px; border: none;");
    setWidgetResizable(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    // 创建控件
    titleLabel = new QLabel("    点位信息", this);
    titleLabel->setFont(QFont("Microsoft YaHei", 12));
    contentContainer = new QWidget();
    setWidget(contentContainer);

    name        = new CommonPropertyItem(this);
    type        = new CommonPropertyItem(this, true);
    direction   = new CommonPropertyItem(this, true);
    speed       = new CommonPropertyItem(this);
    measureMode = new CommonPropertyItem(this, true);

    // 设置控件属性
    titleLabel->setFixedHeight(50);
    name->setTitle("名称");
    type->setTitle("类型");
    QVector<QString> typeList = {"振动", "速度", "温度", "手动输入", "位移"};
    type->addListItems(typeList);

    direction->setTitle("方向");
    QVector<QString> directionList = {"NDE-H", "NDE-V", "NDE-A", "DE-H", "DE-V", "DE-A", "未定义"};
    direction->addListItems(directionList);

    speed->setTitle("速度");

    measureMode->setTitle("测量模式");
    QVector<QString> measureModeList = {"绝对", "相对"};
    measureMode->addListItems(measureModeList);

    QVBoxLayout* mainLayout = new QVBoxLayout(contentContainer);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(name);
    mainLayout->addWidget(type);
    mainLayout->addWidget(direction);
    mainLayout->addWidget(measureMode);
    mainLayout->addWidget(speed);
    contentContainer->setLayout(mainLayout);
}

SpeedMeasureSpotPropertyWidget::~SpeedMeasureSpotPropertyWidget()
{
}

VibrationMeasureSpotPropertyWidget ::VibrationMeasureSpotPropertyWidget(QWidget* parent) : CommonMeasureSpotWidget(parent)
{
    // 设置大小策略
    setStyleSheet("border-radius: 0px; border: none;");
    setWidgetResizable(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    // 创建控件
    titleLabel = new QLabel("    点位信息", this);
    titleLabel->setFont(QFont("Microsoft YaHei", 12));
    contentContainer = new QWidget();
    setWidget(contentContainer);

    name      = new CommonPropertyItem(this);
    type      = new CommonPropertyItem(this, true);
    direction = new CommonPropertyItem(this, true);
    speed     = new CommonPropertyItem(this);

    // 设置控件属性
    titleLabel->setFixedHeight(50);
    name->setTitle("名称");
    type->setTitle("类型");
    QVector<QString> typeList = {"振动", "速度", "温度", "手动输入", "位移"};
    type->addListItems(typeList);

    direction->setTitle("方向");
    QVector<QString> directionList = {"NDE-H", "NDE-V", "NDE-A", "DE-H", "DE-V", "DE-A", "未定义"};
    direction->addListItems(directionList);

    speed->setTitle("速度");
    QVBoxLayout* mainLayout = new QVBoxLayout(contentContainer);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(name);
    mainLayout->addWidget(type);
    mainLayout->addWidget(direction);
    mainLayout->addWidget(speed);
    contentContainer->setLayout(mainLayout);
}

VibrationMeasureSpotPropertyWidget::~VibrationMeasureSpotPropertyWidget()
{
}

ThreeButtons::ThreeButtons(QWidget* parent, const QMap<QString, QString>& iconPaths, int buttonCount) : QGroupBox(parent), iconPaths(iconPaths)
{
    setStyleSheet("QPushButton {background-color:transparent; border:none;}");
    setFixedSize(150, 50);

    setupButtons(buttonCount);

    // 设置布局
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);                 // 设置布局的边距为0
    layout->setSpacing(0);                                  // 设置布局的间距为0
    layout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);  // 设置布局的对齐方式

    for(QPushButton* button : buttons)
    {
        layout->addWidget(button);
    }

    setLayout(layout);

    // 连接按钮点击信号到槽函数, 选中不同按钮时，改变其他按钮的图标
    connect(buttonGroup, QOverload<int>::of(&QButtonGroup::buttonClicked), this, [this](int id) { updateIcons(); });
}

ThreeButtons::~ThreeButtons()
{
}

void ThreeButtons::changeButtonIcon(const QMap<QString, QString>& iconPaths)
{
    this->iconPaths = iconPaths;
    updateIcons();
}

void ThreeButtons::setupButtons(int buttonCount)
{
    buttonGroup = new QButtonGroup(this);

    for(int i = 1; i <= buttonCount; ++i)
    {
        QString buttonName  = "button" + QString::number(i);
        QString iconKey     = buttonName + "_blue";
        QString grayIconKey = buttonName + "_gray";

        QPushButton* button = new QPushButton(this);
        button->setIcon(QIcon(iconPaths[grayIconKey]));  // 默认设置为灰色图标
        button->setIconSize(QSize(30, 30));
        button->setFixedSize(50, 50);
        button->setCheckable(true);
        buttonGroup->addButton(button, i - 1);

        buttons.append(button);
    }

    if(!buttons.isEmpty())
    {
        buttons.first()->setChecked(true);                           // 默认选中第一个按钮
        buttons.first()->setIcon(QIcon(iconPaths["button1_blue"]));  // 将第一个按钮设置为蓝色图标
    }
}

void ThreeButtons::updateIcons()
{
    int selectedId = buttonGroup->checkedId();
    for(int i = 0; i < buttons.size(); ++i)
    {
        QString buttonName  = "button" + QString::number(i + 1);
        QString iconKey     = buttonName + "_blue";
        QString grayIconKey = buttonName + "_gray";

        if(i == selectedId)
        {
            buttons[i]->setIcon(QIcon(iconPaths[iconKey]));  // 选中的按钮设置为蓝色图标
        } else
        {
            buttons[i]->setIcon(QIcon(iconPaths[grayIconKey]));  // 其他按钮设置为灰色图标
        }
    }
}