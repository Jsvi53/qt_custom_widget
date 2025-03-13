#pragma once
#include <QWidget>
#include <QLabel>
#include <QPushButton>

namespace Ui {
class JP_SettingScreen;
}

class SettingItem;

class JP_SettingScreen : public QWidget
{
    Q_OBJECT

public:
    explicit JP_SettingScreen(QWidget *parent = nullptr);
    ~JP_SettingScreen();

private:
    Ui::JP_SettingScreen *ui;
};

class SettingItem : public QWidget
{
    Q_OBJECT

public:
    explicit SettingItem(QWidget *parent = nullptr) : QWidget(parent);
    ~SettingItem();

private slots:
    void on_inputButton_clicked();

private:
    QLabel *item;
    QLabel *itemName;
    QPushButton *inputButton;
};