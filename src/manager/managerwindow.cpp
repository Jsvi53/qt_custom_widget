#include "manager/managerwindow.h"
#include "schenckmain/schenckmain.h"
#include "test/test.h"
#include <QVBoxLayout>

WindowManager::WindowManager(QWidget *parent) : QWidget(parent) {
    stackedWidget = new QStackedWidget(this);

    schenckMain = new SchenckMain(this);
    test = new Test(this);

    stackedWidget->addWidget(schenckMain);
    stackedWidget->addWidget(test);
    stackedWidget->setCurrentIndex(0);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(stackedWidget);
    setLayout(layout);

    connect(schenckMain, &SchenckMain::showSubInterface, this, &WindowManager::showSubInterface);
}

WindowManager::~WindowManager() {
    delete schenckMain;
    delete test;
    delete stackedWidget;
}

void WindowManager::showMainInterface() {
    stackedWidget->setCurrentIndex(0);
}

void WindowManager::showSubInterface() {
    stackedWidget->setCurrentIndex(1);
}