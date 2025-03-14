#pragma once
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QWidget>

namespace Ui
{
    class JP_SettingScreen;
}

class SettingItem; // 前置声明

class JP_SettingScreen : public QWidget
{
    Q_OBJECT

public:
    explicit JP_SettingScreen(QWidget *parent = nullptr);
    ~JP_SettingScreen();

private:
    Ui::JP_SettingScreen *ui;
    SettingItem *userName;
    SettingItem *companyName;
    SettingItem *department;
    SettingItem *streetAddress1;
    SettingItem *streetAddress2;
    SettingItem *postalCode;
    SettingItem *city;
    SettingItem *province;
    SettingItem *state;
};

// 左侧用户设置项
class SettingItem : public QWidget
{
    Q_OBJECT

public:
    explicit SettingItem(QWidget *parent = nullptr);
    ~SettingItem();

    // 设置内容
    void setContent(const QString &content);

    // 设置内容是否可见
    void setContentVisible(bool visible);

    // 获取内容是否可见
    bool isContentVisible() const;

    QLabel *item;
    QLabel *itemName;


private slots:
    void on_inputButton_clicked();

private:
    // 更新标签内容
    void updateContentDisplay();
    QPushButton *inputButton;
    QString realContent; // 真实内容
    bool contentVisible;
};