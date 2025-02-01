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
        QMessageBox::information(this, "oalbuquerque", "Login Success.");
        this->hide();
        MainPage *mainpage = new MainPage();
        mainpage->show();
    }
    else
    {
        QMessageBox::information(this, "oalbuquerque", "Please enter valid username or password");
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

