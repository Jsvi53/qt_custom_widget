#include "test_qmlmerge.h"

Test_qmlMerge::Test_qmlMerge(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);                            // 创建布局
    layout->setContentsMargins(0, 0, 0, 0);                                 // 设置布局的边距
    layout->setSpacing(0);                                                  // 设置布局的间距
    quickWidget = new QQuickWidget(this);                                   // 创建 QQuickWidget
    quickWidget = new QQuickWidget(QUrl("qrc:/qmlwidget/test.qml"), this);  // 创建 QQuickWidget，并设置父窗口为当前窗口
    quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);         // 设置 QML 内容随窗口调整大小
    layout->addWidget(quickWidget);                                         // 将 QQuickWidget 添加到布局中
    setLayout(layout);                                                      // 设置布局
}

Test_qmlMerge::~Test_qmlMerge()
{
}