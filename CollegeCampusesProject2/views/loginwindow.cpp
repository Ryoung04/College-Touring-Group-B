#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>
#include <QUuid>
#include <QDebug>
#include "homewindow.h"
#include "mainwindow.h"
#include <QFile>
#include <QApplication>
#include <QTimer>
#include "../utils/custombackground.h"
#include <QInputDialog>
#include "utils/animatedbackground.h"

LoginWindow::LoginWindow(DBManager* db, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
    , dbManager(db)
    , mainWindow(nullptr)
{
    ui->setupUi(this);
    setWindowTitle("College Campus Tour - Login");
    
    // Create and set up animated background with darker colors
    AnimatedBackground* background = new AnimatedBackground(this);
    
    // Use a dark color scheme for the background
    background->setColors({
        QColor(10, 15, 30),      // Very Dark Blue/Black
        QColor(20, 30, 60),      // Dark Blue
        QColor(40, 50, 100),     // Medium Dark Blue
        QColor(60, 80, 140)      // Accent Blue
    });
    
    // This will make the background fill the entire window
    background->resize(size());
    
    // Make sure it stays at the back
    background->lower();
    
    // Start the animation
    background->startAnimation();
    
    // Apply dark mode styling to the entire window
    setStyleSheet(
        "QMainWindow { background-color: transparent; }"
        "QLineEdit { background-color: rgba(25, 30, 50, 180); color: #e0e0e0; border: 1px solid #4080b0; border-radius: 5px; padding: 5px; }"
        "QPushButton { background-color: #1a3c5e; color: white; border: none; border-radius: 5px; padding: 8px; }"
        "QPushButton:hover { background-color: #2a5c8e; }"
        "QPushButton:pressed { background-color: #10304e; }"
    );
    
    // Make central widget very dark but semi-transparent to show the background waves
    if (centralWidget()) {
        centralWidget()->setStyleSheet("background-color: rgba(15, 20, 35, 120); border-radius: 12px;");
    }
    
    // Set label styles to light colors for dark mode
    QString labelStyle = "QLabel { color: #e0e0e0; font-weight: bold; }";
    ui->usernameLabel->setStyleSheet(labelStyle);
    ui->passwordLabel->setStyleSheet(labelStyle);
    
    // Set title in light color with larger font
    if (ui->titleLabel) {
        ui->titleLabel->setStyleSheet("QLabel { color: #ffffff; font-size: 18pt; font-weight: bold; }");
    }
    
    // Connect Enter key in text fields to trigger login
    connect(ui->passwordLineEdit, &QLineEdit::returnPressed, this, &LoginWindow::on_loginButton_clicked);
    connect(ui->usernameLineEdit, &QLineEdit::returnPressed, this, [this]() {
        if (!ui->passwordLineEdit->text().isEmpty()) {
            on_loginButton_clicked();
        } else {
            ui->passwordLineEdit->setFocus();
        }
    });

    // Connect window close event
    connect(this, &LoginWindow::destroyed, [this]() {
        // When this window is destroyed, find the background and reparent it
        QList<CustomBackground*> backgrounds = findChildren<CustomBackground*>();
        if (!backgrounds.isEmpty()) {
            backgrounds.first()->setParent(nullptr);
        }
    });
}

LoginWindow::~LoginWindow()
{
    delete ui;
    if (mainWindow) {
        delete mainWindow;
    }
}

void LoginWindow::onMainWindowClosed()
{
    if (mainWindow) {
        mainWindow->deleteLater();
        mainWindow = nullptr;
    }
    this->show();
}

void LoginWindow::on_loginButton_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Login Failed", "Please enter both username and password.");
        return;
    }
    
    // Check if the credentials are valid and determine if user is admin
    bool isAdmin = false;
    bool validCredentials = dbManager->validateCredentials(username, password, &isAdmin);
    
    if (validCredentials) {
        // Display appropriate dashboard based on user role
        showDashboard(username, isAdmin);
    } else {
        QMessageBox::warning(this, "Login Failed", "Invalid username or password.");
    }
}

void LoginWindow::on_guestButton_clicked()
{
    // Continue as guest - no username/password required
    HomeWindow* homeWindow = new HomeWindow(dbManager);
    homeWindow->show();
    this->hide(); // Hide instead of accept() since this is a QMainWindow
}

void LoginWindow::on_registerButton_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Registration Failed", "Please enter both username and password.");
        return;
    }
    
    // Check if username already exists
    if (dbManager->userExists(username)) {
        QMessageBox::warning(this, "Registration Failed", "Username already exists. Please choose another.");
        return;
    }
    
    // Register the new user (always as a regular user, not admin)
    if (dbManager->addUser(username, password, false)) {
        QMessageBox::information(this, "Registration Successful", 
                               "You've been registered successfully! You can now log in.");
        // Clear the fields after successful registration
        ui->usernameLineEdit->clear();
        ui->passwordLineEdit->clear();
    } else {
        QMessageBox::warning(this, "Registration Failed", "An error occurred during registration.");
    }
}

void LoginWindow::showDashboard(const QString &username, bool isAdmin)
{
    // Use the username parameter to avoid the warning
    qDebug() << "Showing dashboard for user:" << username << "Admin:" << isAdmin;
    
    // Create the MainWindow
    MainWindow *mainWindow = new MainWindow(dbManager, isAdmin);
    mainWindow->show();
    
    // Close the login window
    this->close();
}

void LoginWindow::resizeEvent(QResizeEvent* event)
{
    // Call QMainWindow's resizeEvent, not QDialog's
    QMainWindow::resizeEvent(event);
    
    // Make sure the background widget also resizes
    QList<AnimatedBackground*> backgrounds = findChildren<AnimatedBackground*>();
    if (!backgrounds.isEmpty()) {
        backgrounds.first()->resize(size());
    }
} 