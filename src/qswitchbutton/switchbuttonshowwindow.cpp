#include "qswitchbutton/switchbuttonshowwindow.h"
#include "ui_switchbuttonshowwindow.h"
#include <QDebug>

SwitchButtonShowWindow::SwitchButtonShowWindow(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SwitchButtonShowWindow)
{
    ui->setupUi(this);

    // 初始化 m_switchButton
    m_switchButton = new SwitchButton(this);

    // 设置 SwitchButton 的位置和大小
    m_switchButton->setGeometry(50, 50, 100, 30); // 根据需要调整位置和大小

    // 连接 SwitchButton 的信号和槽（可选）
    connect(m_switchButton, &SwitchButton::toggled, [](bool checked) {
        qDebug() << "SwitchButton toggled:" << checked;
    });
}

SwitchButtonShowWindow::~SwitchButtonShowWindow()
{
    delete ui;
    delete m_switchButton;
}