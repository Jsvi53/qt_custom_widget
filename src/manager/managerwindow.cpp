#include "manager/managerwindow.h"
#include "schenckmain/schenckmain.h"
#include <QVBoxLayout>

WindowManager::WindowManager(QWidget *parent) : QWidget(parent) {
    stackedWidget = new QStackedWidget(this);
    schenckMain = new SchenckMain(this);
    stackedWidget->addWidget(schenckMain);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(stackedWidget);
    setLayout(layout);

    connect(schenckMain, &SchenckMain::showSubInterface, this, &WindowManager::showSubInterface);
}

WindowManager::~WindowManager() {
    delete schenckMain;
    delete stackedWidget;
}

void WindowManager::showMainInterface() {
    stackedWidget->setCurrentIndex(0);
}

void WindowManager::showSubInterface() {
    stackedWidget->setCurrentIndex(1);
}
