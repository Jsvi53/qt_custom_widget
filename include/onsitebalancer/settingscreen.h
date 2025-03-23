/***
 * @Date: 2025-03-13 20:09:59
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-14 21:36:56
 * @FilePath: \qt_custom_widget\include\jp_settingscreen\jp_settingscreen.h
 */
#pragma once
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QWidget>

namespace Ui {
class SettingScreen;
}

// 命名空间采用单词首字母
namespace Ss {
class SettingScreen;
class SettingItem;
}  // namespace Ss

class Ss::SettingScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SettingScreen(QWidget *parent = nullptr);
    ~SettingScreen();

    void showEvent(QShowEvent *event) override;

    QPushButton *getButton(const QString &name) const;

signals:
    void backRequested();

private:
    Ui::SettingScreen *ui;
    SettingItem       *userName;
    SettingItem       *companyName;
    SettingItem       *department;
    SettingItem       *streetAddress1;
    SettingItem       *streetAddress2;
    SettingItem       *postalCode;
    SettingItem       *city;
    SettingItem       *province;
    SettingItem       *state;
};

// 左侧用户设置项
class Ss::SettingItem : public QWidget
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

private:
    // 更新标签内容
    void         updateContentDisplay();
    QPushButton *inputButton;
    QString      realContent;  // 真实内容
    bool         contentVisible;
};