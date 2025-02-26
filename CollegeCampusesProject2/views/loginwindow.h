#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include "../utils/csvhandler.h"
#include "../utils/dbmanager.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(DBManager* db, QWidget *parent = nullptr);
    ~LoginWindow();

signals:
    void loginSuccessful();
    void adminLoginSuccessful();

private slots:
    void on_loginButton_clicked();
    void on_registerButton_clicked();

private:
    Ui::LoginWindow *ui;
    CSVHandler csvHandler;
    DBManager* dbManager;
};

#endif // LOGINWINDOW_H 