#ifndef __NEWMACHINETEMPLATE_H
#define __NEWMACHINETEMPLATE_H
#include <QButtonGroup>
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

class NewMachineTemplateScreen : public QWidget
{
    Q_OBJECT
public:
    explicit NewMachineTemplateScreen(QWidget* parent = nullptr);
    ~NewMachineTemplateScreen();

private:
    Ui::NewMachineTemplateScreenUI* ui;
    QScrollArea*                    templateListScrollArea;
    QStackedWidget*                 workspaceWidget;
};

class MachineTrainTemplate : public QWidget
{
    Q_OBJECT
public:
    explicit MachineTrainTemplate(QWidget* parent = nullptr);
    ~MachineTrainTemplate();

protected:
    QPushButton* templateButton;
    QPushButton* templateAddButton;
};

class MachineTemplate : public QWidget
{
    Q_OBJECT

public:
    explicit MachineTemplate(QWidget* parent = nullptr);
    ~MachineTemplate();
    enum MeasureType { Speed, Vibration, Unknown };
    void addListItem(const QString& itemName, MeasureType Type);

public slots:
    void on_collapseExpandButton_clicked();
    void checkListEmpty();

private:
    void         listwidgetShowToggle();
    void         __updateAddSpotButtonIcon(bool isempty);
    QWidget*     machineTitleContainer;
    QListWidget* spotListWidget;
    QPushButton* collapseExpandButton;
    QPushButton* machineTtitleButton;
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

    void setTitle(const QString& title);
    void setProperty(const QString& property);
    void setIcon(const QString& iconPath);
    void addListItem(const QString& itemName);
    void addListItem(const QString& itemName, const QString& itemIconPath);
    void addListItems(const QVector<QString>& itemNames);
    void addListItems(const QVector<QString>& itemNames, const QVector<QString>& itemIconPaths);

public slots:
    void on_iconButton_clicked();
    void listCheck();
    void updateItemIcon(QListWidgetItem* current, QListWidgetItem* previous);

private:
    void         listwidgetShowToggle();
    QWidget*     titleContainer;
    QWidget*     titleSubContainer;
    QPushButton* iconButton;
    QLabel*      titleLabel;
    QLabel*      propertyLabel;
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

private:
    QLabel*             titleLabel;
    QWidget*            contentContainer;
    CommonPropertyItem* name;
    CommonPropertyItem* type;
    CommonPropertyItem* direction;
    CommonPropertyItem* power;
    CommonPropertyItem* speed;
    CommonPropertyItem* referenceshaft;
    CommonPropertyItem* base;
};

#endif  // __NEWMACHINETEMPLATE_H