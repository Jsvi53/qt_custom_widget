#ifndef __NEWMACHINETEMPLATE_H
#define __NEWMACHINETEMPLATE_H
#include <QButtonGroup>
#include <QGroupBox>
#include <QLabel>
#include <QListWidget>
#include <QPalette>
#include <QPushButton>
#include <QScrollArea>
#include <QStackedWidget>
#include <QTimer>
#include <QVBoxLayout>
#include <QVector>
#include <QWidget>

namespace Ui {
class NewMachineTemplateScreenUI;
}

class MachineTemplate;
class CommonPropertyItem;
class MachineTrainPropertyWorkspace;
class CommonPropertyItem;
class MachineTrainPropertyWorkspace;
class ThreeButtons;

class NewMachineTemplateScreen : public QWidget
{
    Q_OBJECT
public:
    explicit NewMachineTemplateScreen(QWidget* parent = nullptr);
    ~NewMachineTemplateScreen();

private slots:
    void onCurrentRowChanged(int currentRow);

private:
    Ui::NewMachineTemplateScreenUI* ui;
    QScrollArea*                    templateListScrollArea;
    QStackedWidget*                 workspaceWidget;
    QTimer*                         screenTimer;
    ThreeButtons*                   threeButtons;
    ThreeButtons*                   twoButtons;
    GroupWidget*                    groupWidget;

    QMap<QString, QString> machineTrainIconPaths{{"button1_blue", ":/newtemplate/newtemplate_assets/icon_newtemplate_group_blue.png"},
                                                 {"button1_gray", ":/newtemplate/newtemplate_assets/icon_newtemplate_group_gray.png"},
                                                 {"button2_blue", ":/newtemplate/newtemplate_assets/icon_newtemplate_location_blue.png"},
                                                 {"button2_gray", ":/newtemplate/newtemplate_assets/icon_newtemplate_location_gray.png"}};
    QMap<QString, QString> machineIconPaths{{"button1_blue", ":/newtemplate/newtemplate_assets/icon_newtemplate_itemlist_blue.png"},
                                            {"button1_gray", ":/newtemplate/newtemplate_assets/icon_newtemplate_itemlist_gray.png"},
                                            {"button2_blue", ":/newtemplate/newtemplate_assets/icon_newtemplate_model_blue.png"},
                                            {"button2_gray", ":/newtemplate/newtemplate_assets/icon_newtemplate_model_gray.png"}};
    QMap<QString, QString> spotIconPaths{
        {"button1_blue", ":/commonIcon/commonicon_assets/icon_common_radiobutton_on_gray.png"}, {"button1_gray", ":/commonIcon/commonicon_assets/icon_common_radiobutton_off_gray.png"},
        {"button2_blue", ":/commonIcon/commonicon_assets/icon_common_radiobutton_on_gray.png"}, {"button2_gray", ":/commonIcon/commonicon_assets/icon_common_radiobutton_off_gray.png"},
        {"button3_blue", ":/commonIcon/commonicon_assets/icon_common_radiobutton_on_gray.png"}, {"button3_gray", ":/commonIcon/commonicon_assets/icon_common_radiobutton_off_gray.png"}};
};

class MachineTrainTemplate : public QWidget
{
    Q_OBJECT
public:
    explicit MachineTrainTemplate(QWidget* parent = nullptr);
    ~MachineTrainTemplate();
    void         setMachineTrainTemplateTitle(QString title);
    QPushButton* templateButton;

protected:
    QPushButton* templateAddButton;
};

class MachineTemplate : public QWidget
{
    Q_OBJECT

public:
    explicit MachineTemplate(QWidget* parent = nullptr);
    ~MachineTemplate();

    QPushButton* machineTtitleButton;
    QListWidget* spotListWidget;

    enum MeasureType { Speed, Vibration, Unknown };
    void addListItem(const QString& itemName, MeasureType Type);
    void setMachineTemplateTitle(QString title);

public slots:
    void on_collapseExpandButton_clicked();
    void checkListEmpty();

private:
    void         listwidgetShowToggle();
    void         __updateAddSpotButtonIcon(bool isempty);
    QWidget*     machineTitleContainer;
    QPushButton* collapseExpandButton;
    QPushButton* addSpotButton;
    QVBoxLayout* thisMainLayout;
    QTimer*      listCheckTimer;
    bool         isExpanded{false};
    bool         isListEmpty{false};
    QFont        font;
};

class CommonPropertyItem : public QWidget
{
    Q_OBJECT
public:
    explicit CommonPropertyItem(QWidget* parent = nullptr, bool listNeeded = false);
    ~CommonPropertyItem();

    QPushButton* iconButton;
    void         setTitle(const QString& title);
    void         setProperty(const QString& property);
    void         setIcon(const QString& iconPath);
    void         addListItem(const QString& itemName);
    void         addListItem(const QString& itemName, const QString& itemIconPath);
    void         addListItems(const QVector<QString>& itemNames);
    void         addListItems(const QVector<QString>& itemNames, const QVector<QString>& itemIconPaths);
    QLabel*      getTitleLabel() const;
    QLabel*      propertyLabel;

public slots:
    void on_iconButton_clicked();
    void listCheck();
    void updateItemIcon(QListWidgetItem* current, QListWidgetItem* previous);

private:
    void         listwidgetShowToggle();
    QWidget*     titleContainer;
    QWidget*     titleSubContainer;
    QLabel*      titleLabel;
    QListWidget* propertyListWidget;
    QVBoxLayout* thisMainLayout;
    QTimer*      listCheckTimer;
    bool         isListEmpty{false};
    bool         isExpanded{false};
    bool         isListNeeded{false};
    QFont        font;
    QPalette     palette;
};

class MachineTrainPropertyWorkspace : public QScrollArea
{
    Q_OBJECT
public:
    explicit MachineTrainPropertyWorkspace(QWidget* parent = nullptr);
    ~MachineTrainPropertyWorkspace();

    CommonPropertyItem* name;

private:
    QLabel*             titleLabel;
    QWidget*            contentContainer;
    CommonPropertyItem* type;
    CommonPropertyItem* direction;
    CommonPropertyItem* power;
    CommonPropertyItem* speed;
    CommonPropertyItem* referenceshaft;
    CommonPropertyItem* base;
};

class GroupWidget : public QScrollArea
{
    Q_OBJECT
public:
    explicit GroupWidget(QWidget* parent = nullptr);
    ~GroupWidget();
    CommonPropertyItem* addGroup();

private:
    CommonPropertyItem*                addGroupButton;
    QVBoxLayout*                       thisMainLayout;
    QMap<QString, CommonPropertyItem&> groupItemMap;
};

class MachinePropertyWidget : public QScrollArea
{
    Q_OBJECT
public:
    explicit MachinePropertyWidget(QWidget* parent = nullptr);
    ~MachinePropertyWidget();

    CommonPropertyItem* name;

private:
    QLabel*  titleLabel;
    QWidget* contentContainer;

    CommonPropertyItem* type;
    CommonPropertyItem* power;
    CommonPropertyItem* speed;

    // TODO: 添加覆盖机组功率
};

class CommonMeasureSpotWidget : public QScrollArea
{
    Q_OBJECT
public:
    explicit CommonMeasureSpotWidget(QWidget* parent = nullptr);
    ~CommonMeasureSpotWidget();

    CommonPropertyItem* name;

protected:
    QLabel*             titleLabel;
    QWidget*            contentContainer;
    CommonPropertyItem* type;
    CommonPropertyItem* direction;
    CommonPropertyItem* speed;
};

class SpeedMeasureSpotPropertyWidget : public CommonMeasureSpotWidget
{
    Q_OBJECT
public:
    explicit SpeedMeasureSpotPropertyWidget(QWidget* parent = nullptr);
    ~SpeedMeasureSpotPropertyWidget();
    CommonPropertyItem* measureMode;
};

class VibrationMeasureSpotPropertyWidget : public CommonMeasureSpotWidget
{
    Q_OBJECT
public:
    explicit VibrationMeasureSpotPropertyWidget(QWidget* parent = nullptr);
    ~VibrationMeasureSpotPropertyWidget();
};

// 三个互斥按钮类
class ThreeButtons : public QGroupBox
{
    Q_OBJECT

public:
    explicit ThreeButtons(QWidget* parent = nullptr, const QMap<QString, QString>& iconPaths = QMap<QString, QString>(), int buttonCount = 3);
    ~ThreeButtons();

    QList<QPushButton*> buttons;
    void                changeButtonIcon(const QMap<QString, QString>& iconPaths);

private:
    QMap<QString, QString> iconPaths;
    QButtonGroup*          buttonGroup;

    void setupButtons(int buttonCount);
    void updateIcons();
};

// TODO: 未能实现在线添加功能和相应的界面切换

#endif  // __NEWMACHINETEMPLATE_H