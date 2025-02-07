#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mainPage(nullptr)  // Initialize pointer
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonLogin_clicked()
{
    QString username = ui->lineEditUsername->text();
    QString password = ui->lineEditPassword->text();

    // List of valid credentials
    QMap<QString, QString> validCredentials = {
        {"oalbuquerque", "Password123"},
        {"aaron", "Password222"},
        {"linsey", "Password333"},
        {"reise", "Password444"},
        {"ferris", "Password555"},
        {"ruben", "Password666"}
    };

    if (validCredentials.contains(username) && validCredentials[username] == password)
    {
        QMessageBox::information(this, "Notification", "Login Success.");
        this->hide();

        if (!mainPage) {
            mainPage = new MainPage(this);  // Create only one instance
        }
        mainPage->show();
    }
    else
    {
        QMessageBox::warning(this, "Login Failed", "Please enter a valid username or password.");
    }
}

void MainWindow::on_pushButtonCancel_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Exit", "Are you sure you want to close the application?", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        QApplication::quit();
    }
}
