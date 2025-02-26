#include "homewindow.h"
#include "ui_homewindow.h"

HomeWindow::HomeWindow(DBManager* db, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HomeWindow)
    , dbManager(db)
    , mainWindow(nullptr)
{
    ui->setupUi(this);
}

HomeWindow::~HomeWindow()
{
    delete ui;
    if (mainWindow) delete mainWindow;
}

void HomeWindow::on_distancesButton_clicked()
{
    if (!mainWindow) {
        mainWindow = new MainWindow(dbManager, this);
        connect(mainWindow, &MainWindow::returnToHome, this, &HomeWindow::show);
    }
    mainWindow->showDistancesTab();
    mainWindow->show();
    hide();
}

void HomeWindow::on_souvenirsButton_clicked()
{
    if (!mainWindow) {
        mainWindow = new MainWindow(dbManager, this);
        connect(mainWindow, &MainWindow::returnToHome, this, &HomeWindow::show);
    }
    mainWindow->showSouvenirsTab();
    mainWindow->show();
    hide();
}

void HomeWindow::on_tripPlannerButton_clicked()
{
    if (!mainWindow) {
        mainWindow = new MainWindow(dbManager, this);
        connect(mainWindow, &MainWindow::returnToHome, this, &HomeWindow::show);
    }
    mainWindow->showTripPlannerTab();
    mainWindow->show();
    hide();
} 