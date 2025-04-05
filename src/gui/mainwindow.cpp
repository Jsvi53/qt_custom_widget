#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "setting_date_time.h"
#include "home_page.h"
#include "file_manage.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_stackedWidget = new QStackedWidget(this);
    setCentralWidget(m_stackedWidget);

    date_time_window = new setting_date_time();
    m_homePage = new home_page();
    m_file_manage = new file_manage();

    m_stackedWidget->addWidget(m_homePage);
    m_stackedWidget->addWidget(date_time_window);
    m_stackedWidget->addWidget(m_file_manage);

    // 连接按钮信号与槽（如果使用UI设计器拖放按钮，可直接用on_按钮对象名_clicked()自动连接）
    connect(m_homePage, &home_page::requestSwitchToSetPage, this, &MainWindow::Switch_date_time_clicked);
    connect(m_homePage, &home_page::requestSwitchToFile, this, &MainWindow::Switch_file_manage_clicked);


    connect(date_time_window, &setting_date_time::requestBackToHome, this, &MainWindow::switchToHomePage);
    connect(m_file_manage, &file_manage::requestBackToHome, this, &MainWindow::switchToHomePage);

    switchToHomePage();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Switch_date_time_clicked()
{
    m_stackedWidget->setCurrentWidget(date_time_window);
}

void MainWindow::Switch_file_manage_clicked()
{
    m_stackedWidget->setCurrentWidget(m_file_manage);
}

void MainWindow::switchToHomePage()
{
    m_stackedWidget->setCurrentWidget(m_homePage);
}



