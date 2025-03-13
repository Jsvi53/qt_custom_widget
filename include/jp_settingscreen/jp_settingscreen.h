#pragma once
#include <QWidget>

namespace Ui {
class JP_SettingScreen;
}

class JP_SettingScreen : public QWidget
{
    Q_OBJECT

public:
    explicit JP_SettingScreen(QWidget *parent = nullptr);
    ~JP_SettingScreen();

private:
    Ui::JP_SettingScreen *ui;
};
