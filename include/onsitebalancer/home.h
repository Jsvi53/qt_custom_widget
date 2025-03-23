#pragma once
#include <QPushButton>
#include <QWidget>


namespace Ui {
class HomeScreen;
}

namespace Hs {
class HomeScreen;
}

class Hs::HomeScreen : public QWidget
{
    Q_OBJECT
public:
    explicit HomeScreen(QWidget *parent = nullptr);
    ~HomeScreen();

    // 枚举类型标记按钮
    enum ButtonType {
        SettingButton,

    };  // 未来可以不断扩充

    // 提供getter接口，返回指定控件指针
    QPushButton *getButton(ButtonType buttonType) const;
    QPushButton *getButton(const QString &name) const;


private:
    Ui::HomeScreen *ui;
};