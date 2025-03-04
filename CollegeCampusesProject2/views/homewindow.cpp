#include "homewindow.h"
#include "ui_homewindow.h"
#include "mainwindow.h"
#include <QTextStream>
#include <QDebug>

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
    if (mainWindow) {
        mainWindow->deleteLater();
        mainWindow = nullptr;
    }
}

void HomeWindow::displayCollegeDistances(const QString& startCollege, QSet<QString>& visited, QString& output, int depth) {
    visited.insert(startCollege);
    
    // Add indentation based on recursion depth
    QString indent = QString("  ").repeated(depth);
    
    // Get all connected colleges
    QVector<Campus> allCampuses = dbManager->getAllCampuses();
    for (const Campus& campus : allCampuses) {
        QString targetCollege = campus.getName();
        if (!visited.contains(targetCollege)) {
            double distance = dbManager->getDistance(startCollege, targetCollege);
            if (distance > 0) {
                output += indent + QString("%1 -> %2: %3 miles\n")
                    .arg(startCollege)
                    .arg(targetCollege)
                    .arg(distance);
                
                // Recursively display distances from the target college
                displayCollegeDistances(targetCollege, visited, output, depth + 1);
            }
        }
    }
}

void HomeWindow::on_distancesButton_clicked()
{
    if (!mainWindow) {
        mainWindow = new MainWindow(dbManager, false);
        
        // Use a direct connection to the destroyed signal instead
        connect(mainWindow, &QObject::destroyed, this, [this]() {
            mainWindow = nullptr;
            show();
        });
    }
    
    // Get all colleges
    QVector<Campus> campuses = dbManager->getAllCampuses();
    if (campuses.isEmpty()) {
        qDebug() << "No colleges found in database";
        return;
    }
    
    // Start recursive display from the first college
    QString output;
    QSet<QString> visited;
    displayCollegeDistances(campuses[0].getName(), visited, output);
    
    // Display the results in the main window
    mainWindow->showDistancesTab();
    mainWindow->displayDistances(output);  // You'll need to add this method to MainWindow
    mainWindow->show();
    hide();
}

void HomeWindow::on_souvenirsButton_clicked()
{
    if (!mainWindow) {
        mainWindow = new MainWindow(dbManager, false);
        
        // Use a direct connection to the destroyed signal instead
        connect(mainWindow, &QObject::destroyed, this, [this]() {
            mainWindow = nullptr;
            show();
        });
    }
    mainWindow->showSouvenirsTab();
    mainWindow->show();
    hide();
}

void HomeWindow::on_tripPlannerButton_clicked()
{
    if (!mainWindow) {
        mainWindow = new MainWindow(dbManager, false);
        
        // Use a direct connection to the destroyed signal instead
        connect(mainWindow, &QObject::destroyed, this, [this]() {
            mainWindow = nullptr;
            show();
        });
    }
    mainWindow->showTripPlannerTab();
    mainWindow->show();
    hide();
}

// Add this method to handle when MainWindow is closed
void HomeWindow::onMainWindowClosed()
{
    if (mainWindow) {
        mainWindow->deleteLater();
        mainWindow = nullptr;
    }
    show();
} 