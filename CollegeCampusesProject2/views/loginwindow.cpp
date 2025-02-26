#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>
#include <QUuid>
#include <QDebug>
#include "homewindow.h"
#include "mainwindow.h"
#include <QFile>

LoginWindow::LoginWindow(DBManager* db, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginWindow)
    , dbManager(db)
{
    ui->setupUi(this);
    setWindowTitle("College Campus Tour - Login");

    // Delete existing users.csv file if it exists
    QFile::remove(CSVHandler::USER_FILE);

    // Create fresh users.csv with only admin
    QVector<User> users;
    QString adminId = QUuid::createUuid().toString(QUuid::WithoutBraces);
    QString hashedPassword = CSVHandler::hashPassword("admin123");
    User adminUser(adminId, "admin", hashedPassword, true);
    users.append(adminUser);
    CSVHandler::writeUsers(CSVHandler::USER_FILE, users);
    qDebug() << "Reset users file with admin only";
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_loginButton_clicked()
{
    QString username = ui->usernameInput->text();
    QString password = ui->passwordInput->text();

    qDebug() << "Login attempt for user:" << username;

    // Read users from CSV
    QVector<User> users = CSVHandler::readUsers(CSVHandler::USER_FILE);
    QString hashedPassword = CSVHandler::hashPassword(password);

    qDebug() << "Found" << users.size() << "users in database";

    for (const User& user : users) {
        qDebug() << "Checking user:" << user.getUsername() 
                 << "isAdmin:" << user.getIsAdmin();
        
        if (user.getUsername() == username && user.getPassword() == hashedPassword) {
            qDebug() << "Login successful for user:" << username;
            
            // Create and show appropriate window based on user type
            if (user.getIsAdmin()) {
                qDebug() << "Admin login detected";
                MainWindow* mainWindow = new MainWindow(dbManager, true);  // Add isAdmin parameter
                mainWindow->show();
            } else {
                MainWindow* mainWindow = new MainWindow(dbManager, false);
                mainWindow->show();
            }
            accept();
            return;
        }
    }

    qDebug() << "Login failed for user:" << username;
    QMessageBox::warning(this, "Login Failed", "Invalid username or password");
}

void LoginWindow::on_registerButton_clicked()
{
    QString username = ui->usernameInput->text();
    QString password = ui->passwordInput->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Registration Error", "Please enter both username and password.");
        return;
    }

    // Read existing users to check for duplicates
    QVector<User> users = CSVHandler::readUsers(CSVHandler::USER_FILE);
    for (const User& user : users) {
        if (user.getUsername() == username) {
            QMessageBox::warning(this, "Registration Error", "Username already exists.");
            return;
        }
    }

    // Create new user
    QString userId = QUuid::createUuid().toString(QUuid::WithoutBraces);
    QString hashedPassword = CSVHandler::hashPassword(password);
    User newUser(userId, username, hashedPassword, false);
    
    users.append(newUser);
    
    if (CSVHandler::writeUsers(CSVHandler::USER_FILE, users)) {
        QMessageBox::information(this, "Registration Success", "Account created successfully. You can now login.");
    } else {
        QMessageBox::critical(this, "Registration Error", "Failed to create account. Please try again.");
    }
} 