#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    loginWindow = new LoginWindow(this);
    collegeDistanceWidget = new CollegeDistanceWidget(this);

    setCentralWidget(loginWindow);

    connect(loginWindow, &LoginWindow::loginSuccess, this, &MainWindow::onLoginSuccess);
    connect(collegeDistanceWidget, &CollegeDistanceWidget::logout, this, &MainWindow::onLogout);
}

MainWindow::~MainWindow()
{
}

void MainWindow::onLoginSuccess()
{
    setCentralWidget(collegeDistanceWidget);
}

void MainWindow::onLogout()
{
    loginWindow->clearFields();
    setCentralWidget(loginWindow);
}
