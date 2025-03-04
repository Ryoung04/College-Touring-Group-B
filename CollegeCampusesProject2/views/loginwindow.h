#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "../utils/csvhandler.h"
#include "../utils/dbmanager.h"
#include "mainwindow.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(DBManager *dbManager, QWidget *parent = nullptr);
    ~LoginWindow();

signals:
    void loginSuccessful();
    void adminLoginSuccessful();

private slots:
    void on_loginButton_clicked();
    void on_guestButton_clicked();
    void onMainWindowClosed();
    void on_registerButton_clicked();

private:
    Ui::LoginWindow *ui;
    CSVHandler csvHandler;
    DBManager *dbManager;
    MainWindow* mainWindow;
    void setupCustomBackground();
    
    // Helper method to show users/admin dashboard based on role
    void showDashboard(const QString &username, bool isAdmin);

protected:
    void resizeEvent(QResizeEvent* event) override;
};

#endif // LOGINWINDOW_H 