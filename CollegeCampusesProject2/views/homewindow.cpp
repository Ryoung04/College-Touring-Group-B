#include "homewindow.h"
#include "ui_homewindow.h"
#include "loginwindow.h"
#include "mainwindow.h"
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>

HomeWindow::HomeWindow(DBManager* dbManager, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HomeWindow)
    , m_dbManager(dbManager)
{
    ui->setupUi(this);
    
    setupUI();
    loadColleges();
}

HomeWindow::~HomeWindow()
{
    delete ui;
}

void HomeWindow::setupUI()
{
    // Center the window on the screen
    this->setWindowTitle("College Tour Home");
    
    // Connect buttons - using the names from the UI file
    connect(ui->souvenirsButton, &QPushButton::clicked, this, &HomeWindow::on_souvenirsButton_clicked);
    connect(ui->tripPlannerButton, &QPushButton::clicked, this, &HomeWindow::on_tripPlannerButton_clicked);
    connect(ui->logoutButton, &QPushButton::clicked, this, &HomeWindow::on_logoutButton_clicked);
    connect(ui->distancesButton, &QPushButton::clicked, this, &HomeWindow::on_distancesButton_clicked);
}

void HomeWindow::loadColleges()
{
    // Load the list of colleges from the database
    QVector<Campus> campuses = m_dbManager->getAllCampuses();
    
    // Populate the colleges list - using the proper widget name from UI
    ui->collegeList->clear();
    for (const Campus& campus : campuses) {
        ui->collegeList->addItem(campus.getName());
    }
}

// This method is likely not used, but we keep it to match the header
void HomeWindow::on_viewSouvenirsButton_clicked()
{
    // Redirect to the actual implementation
    on_souvenirsButton_clicked();
}

void HomeWindow::on_planTripButton_clicked()
{
    // Redirect to the actual implementation
    on_tripPlannerButton_clicked();
}

void HomeWindow::on_logoutButton_clicked()
{
    // Show the login window again
    LoginWindow* loginWindow = new LoginWindow(m_dbManager, parentWidget());
    loginWindow->show();
    
    // Close this window
    this->close();
}

void HomeWindow::displayCollegeDistances(const QString& startCollege, QSet<QString>& visited, QString& output, int depth)
{
    visited.insert(startCollege);
    
    // Add indentation based on recursion depth
    QString indent = QString("  ").repeated(depth);
    
    // Get all connected colleges
    QVector<Campus> allCampuses = m_dbManager->getAllCampuses();
    for (const Campus& campus : allCampuses) {
        QString targetCollege = campus.getName();
        if (!visited.contains(targetCollege)) {
            double distance = m_dbManager->getDistance(startCollege, targetCollege);
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
    // Get all colleges
    QVector<Campus> campuses = m_dbManager->getAllCampuses();
    if (campuses.isEmpty()) {
        qDebug() << "No colleges found in database";
        return;
    }
    
    // Start recursive display from the first college
    QString output;
    QSet<QString> visited;
    displayCollegeDistances(campuses[0].getName(), visited, output);
    
    // Display the results in the main window
    mainWindow = new MainWindow(m_dbManager, this);
    mainWindow->show();
    
    // Hide this window
    hide();
}

void HomeWindow::on_souvenirsButton_clicked()
{
    // Check if a college is selected
    if (ui->collegeList->currentItem() == nullptr) {
        QMessageBox::warning(this, "No College Selected", "Please select a college to view souvenirs.");
        return;
    }
    
    QString collegeName = ui->collegeList->currentItem()->text();
    
    // Open the main window
    mainWindow = new MainWindow(m_dbManager, this);
    mainWindow->show();
    
    // Hide this window
    this->hide();
}

void HomeWindow::on_tripPlannerButton_clicked()
{
    // Open the main window with the trip planner tab selected
    mainWindow = new MainWindow(m_dbManager, this);
    mainWindow->show();
    
    // Hide this window
    this->hide();
}

void HomeWindow::onMainWindowClosed()
{
    if (mainWindow) {
        mainWindow->deleteLater();
        mainWindow = nullptr;
    }
    show();
} 