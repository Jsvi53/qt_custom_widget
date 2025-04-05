#include <QDebug>

#include "mainwidget.h"

// mainwidget.cpp
MainWidget::MainWidget(QWidget *parent)
    : QStackedWidget(parent),
      managerScreen(new FileManagerScreen()),  // 正确初始化
      balanceMeasureScreen(new BalanceMeasureScreen())
{
    setFixedSize(1280, 800);
    addWidget(managerScreen);
    addWidget(balanceMeasureScreen);
    setCurrentIndex(0);

    connect(managerScreen, &FileManagerScreen::clicked, this, &MainWidget::onPushButtonPressed);
    connect(balanceMeasureScreen, &BalanceMeasureScreen::backButtonClicked, this, [this]() { setCurrentIndex(0); });
}

void MainWidget::onPushButtonPressed()
{
    setCurrentIndex(1);
}

MainWidget::~MainWidget()
{
}