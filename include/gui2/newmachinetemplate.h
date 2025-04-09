#ifndef __NEWMACHINETEMPLATE_H
#define __NEWMACHINETEMPLATE_H
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

namespace Ui {
class NewMachineTemplateScreenUI;
}

class MachineTemplate;

class NewMachineTemplateScreen : public QWidget
{
    Q_OBJECT
public:
    explicit NewMachineTemplateScreen(QWidget* parent = nullptr);
    ~NewMachineTemplateScreen();

private:
    Ui::NewMachineTemplateScreenUI* ui;
    QScrollArea*                    templateListScrollArea;
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

private:
    void listwidgetShowToggle();

    QWidget*     machineTitleContainer;
    QListWidget* spotListWidget;
    QPushButton* machineTtitleButton;
    QPushButton* addSpotButton;
    QVBoxLayout* thisMainLayout;
    bool        isExpanded{false};

};

#endif  // __NEWMACHINETEMPLATE_H