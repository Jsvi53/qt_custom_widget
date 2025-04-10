#ifndef __NEWMACHINETEMPLATE_H
#define __NEWMACHINETEMPLATE_H
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QScrollArea>
#include <QStackedWidget>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>
#include <QVector>

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

public slots:
    void on_machineTtitleButton_clicked();
    void checkListEmpty();

private:
    void         listwidgetShowToggle();
    void         __updateAddSpotButtonIcon();
    QWidget*     machineTitleContainer;
    QListWidget* spotListWidget;
    QPushButton* machineTtitleButton;
    QPushButton* addSpotButton;
    QVBoxLayout* thisMainLayout;
    QTimer*      listCheckTimer;
    bool         isExpanded{false};
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
    bool         isListEmpty{true};
    bool         isExpanded{false};
    bool         isListNeeded{false};
    QFont        font;

};

class MachineTrainPropertyWorkspace : public QWidget
{
    Q_OBJECT
public:
    explicit MachineTrainPropertyWorkspace(QWidget* parent = nullptr);
    ~MachineTrainPropertyWorkspace();

private:
    QLabel*             titleLabel;
    CommonPropertyItem* name;
    CommonPropertyItem* type;
    CommonPropertyItem* direction;
    CommonPropertyItem* power;
    CommonPropertyItem* speed;
    CommonPropertyItem* referenceshaft;
    CommonPropertyItem* base;
};

#endif  // __NEWMACHINETEMPLATE_H