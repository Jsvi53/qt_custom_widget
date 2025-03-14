/*** 
 * @Date: 2025-03-14 08:00:14
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-14 08:16:46
 * @FilePath: \qt_custom_widget\include\jp_settingscreen\jp_settingscreen.h
 */
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

// 设置项
class SettingItem : public QWidget
{
    Q_OBJECT

public:
    explicit SettingItem(QWidget *parent = nullptr);
    ~SettingItem();

private slots:
    void on_inputButton_clicked();

private:
    QLabel *item;
    QLabel *itemName;
    QPushButton *inputButton;
};