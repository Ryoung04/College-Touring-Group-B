#pragma once

#include <QMainWindow>
#include "loginwindow.h"
#include "collegedistancewidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onLoginSuccess();
    void onLogout();

private:
    LoginWindow* loginWindow;
    CollegeDistanceWidget* collegeDistanceWidget;
};
