#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonLogin_clicked()
{
    QString Username = ui->lineEditUsername->text();
    QString Password = ui->lineEditPassword->text();
    if (Username == "oalbuquerque" && Password == "Password123")
    {
        QMessageBox::information(this, "Notification", "Login Success.");
        this->hide();
        MainPage *mainpage = new MainPage();
        mainpage->show();
    }
    if (Username == "aaron" && Password == "Password222")
    {
        QMessageBox::information(this, "Notification", "Login Success.");
        this->hide();
        MainPage *mainpage = new MainPage();
        mainpage->show();
    }
    if (Username == "linsey" && Password == "Password333")
    {
        QMessageBox::information(this, "Notification", "Login Success.");
        this->hide();
        MainPage *mainpage = new MainPage();
        mainpage->show();
    }
    if (Username == "reise" && Password == "Password444")
    {
        QMessageBox::information(this, "Notification", "Login Success.");
        this->hide();
        MainPage *mainpage = new MainPage();
        mainpage->show();
    }
    if (Username == "ferris" && Password == "Password555")
    {
        QMessageBox::information(this, "Notification", "Login Success.");
        this->hide();
        MainPage *mainpage = new MainPage();
        mainpage->show();
    }
    if (Username == "ruben" && Password == "Password666")
    {
        QMessageBox::information(this, "Notification", "Login Success.");
        this->hide();
        MainPage *mainpage = new MainPage();
        mainpage->show();
    }
    else
    {
        QMessageBox::information(this, Username, "Please enter valid username or password");
    }
}


void MainWindow::on_pushButtonCancel_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "oalbuquerque", "Are you sure you wante to close the application?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        QApplication::quit();
    }
}

