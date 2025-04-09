#ifndef __NEWMACHINETEMPLATE_H
#define __NEWMACHINETEMPLATE_H
#include <QFrame>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

namespace Ui {
class NewMachineTemplateScreenUI;
}

class NewMachineTemplateScreen : public QWidget
{
    Q_OBJECT
public:
    explicit NewMachineTemplateScreen(QWidget *parent = nullptr);
    ~NewMachineTemplateScreen();

private:
    Ui::NewMachineTemplateScreenUI *ui;
    QScrollArea *templateListScrollArea;
};

class MachineTrainTemplate : public QWidget
{
    Q_OBJECT
public:
    explicit MachineTrainTemplate(QWidget *parent = nullptr);
    ~MachineTrainTemplate();

protected:
    QPushButton *templateButton;
    QPushButton *templateAddButton;
};

class MachineTemplate : public QWidget
{
    Q_OBJECT
public:
    MachineTemplate(QWidget* parent = nullptr);
    ~MachineTemplate();
    void setWidget(const QString& title, QWidget* widget);
    void expand();
    void collapse();
    void onPushButtonFoldClicked();

private:
    QPushButton* pushButtonFold;
    QWidget* measurePointWidget;
    QVBoxLayout* measurePointWidgetLayout;
    QLabel* labelMachineName;
    QLabel* labelExpanded; // 用于显示“已经展开”的标签
    QWidget* m_widgetPlane;
    bool m_bIsExpanded = false;
};

#endif  // __NEWMACHINETEMPLATE_H