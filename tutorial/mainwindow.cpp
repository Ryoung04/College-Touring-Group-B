#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMap>
#include <QMessageBox>

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
    QString username = ui->lineEditUsername->text();
    QString password = ui->lineEditPassword->text();

    // Store valid credentials in a QMap
    static const QMap<QString, QString> validCredentials = {
        {"oalbuquerque", "Password111"},
        {"reise", "Password222"},
        {"linsey", "Password333"},
        {"aaron", "Password444"},
        {"ruben", "Password555"},
        {"ferris", "Password666"}
    };

    if (validCredentials.contains(username) && validCredentials.value(username) == password)
    {
        QMessageBox::information(this, "Notification", "Login Success.");
        this->hide();

        MainPage *mainPage = new MainPage();
        mainPage->setAttribute(Qt::WA_DeleteOnClose); // Ensure it deletes itself when closed
        mainPage->show();
    }
    else
    {
        QMessageBox::warning(this, "Login Failed", "Please enter a valid username or password.");
    }
}

void MainWindow::on_pushButtonCancel_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Exit", "Are you sure you want to close the application?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes)
    {
        QApplication::quit();
    }
}
