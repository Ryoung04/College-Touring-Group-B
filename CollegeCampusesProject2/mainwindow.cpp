#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "views/adminpanel.h"
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QComboBox>
#include <QTextStream>
#include <QPushButton>
#include <QToolBar>
#include <QCoreApplication>
#include <QPixmap>
#include <QPalette>
#include <QMenu>
#include <QAction>

MainWindow::MainWindow(DBManager* db, bool isAdmin, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , dbManager(db)
    , isAdmin(isAdmin)
{
    ui->setupUi(this);

    // Show/hide admin controls based on user type
    setupAdminControls();

    // Set background image
    QPixmap background(":/images/background.jpg");
    ui->homeTab->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Window, background.scaled(
        ui->homeTab->size(),
        Qt::KeepAspectRatioByExpanding,
        Qt::SmoothTransformation
    ));
    ui->homeTab->setPalette(palette);

    // Initialize database
    QString dbPath = QDir(QCoreApplication::applicationDirPath()).filePath("colleges.db");
    QFile::remove(dbPath);

    if (!dbManager->isOpen()) {
        qDebug() << "Failed to open database at:" << dbPath;
        return;
    }

    if (!dbManager->importCollegesFromCSV(":/data/data/colleges.csv")) {
        qDebug() << "Failed to import colleges data!";
    }
    
    if (!dbManager->importSouvenirsFromCSV(":/data/data/souvenirs.csv")) {
        qDebug() << "Failed to import souvenirs data!";
    }

    loadCampuses();
    setupSouvenirTab();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadCampuses()
{
    // Clear existing items
    ui->campusList->clear();
    ui->souvenirCampusCombo->clear();
    ui->startingCampusCombo->clear();

    // Add placeholders
    ui->souvenirCampusCombo->addItem("Select a campus to view souvenirs");
    ui->startingCampusCombo->addItem("Please select a campus");

    // Get campuses from database
    allCampuses = dbManager->getAllCampuses();
    
    // Add to lists
    for (const Campus& campus : allCampuses) {
        QString campusName = campus.getName();
        ui->campusList->addItem(campusName);
        ui->souvenirCampusCombo->addItem(campusName);
        ui->startingCampusCombo->addItem(campusName);
    }

    // Set current index to placeholder
    ui->souvenirCampusCombo->setCurrentIndex(0);
    ui->startingCampusCombo->setCurrentIndex(0);

    // Setup distances table
    ui->distancesTable->setColumnWidth(0, 200);  // Campus column
    ui->distancesTable->setColumnWidth(1, 120);  // Distance column
    ui->distancesTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Interactive);
    ui->distancesTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Interactive);
    ui->distancesTable->horizontalHeader()->setStretchLastSection(true);

    // Connect the starting campus combo box signal
    connect(ui->startingCampusCombo, &QComboBox::currentTextChanged,
            this, &MainWindow::updateDistancesTable);
}

void MainWindow::setupSouvenirTab()
{
    // Setup souvenir table
    ui->souvenirTable->setColumnCount(2);
    ui->souvenirTable->setHorizontalHeaderLabels({"Souvenir", "Price"});
    ui->souvenirTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Connect signals
    connect(ui->souvenirCampusCombo, &QComboBox::currentTextChanged,
            this, &MainWindow::onCampusSelected);

    // Show initial souvenirs if there are campuses
    if (ui->souvenirCampusCombo->count() > 0) {
        updateSouvenirDisplay(ui->souvenirCampusCombo->currentText());
    }
}

void MainWindow::showDistancesTab()
{
    ui->tabWidget->setCurrentIndex(0);  // Adjust index as needed
}

void MainWindow::showSouvenirsTab()
{
    ui->tabWidget->setCurrentIndex(1);  // Adjust index as needed
}

void MainWindow::showTripPlannerTab()
{
    ui->tabWidget->setCurrentIndex(2);  // Adjust index as needed
}

void MainWindow::onCampusSelected(const QString& campusName)
{
    updateSouvenirDisplay(campusName);
}

void MainWindow::updateSouvenirDisplay(const QString& campusName)
{
    qDebug() << "Updating souvenirs for campus:" << campusName;

    // Clear existing items
    ui->souvenirTable->setRowCount(0);

    // Get souvenirs from database
    QVector<QPair<QString, double>> souvenirs = dbManager->getSouvenirs(campusName);
    
    ui->souvenirTable->setRowCount(souvenirs.size());
    for (int i = 0; i < souvenirs.size(); ++i) {
        ui->souvenirTable->setItem(i, 0, new QTableWidgetItem(souvenirs[i].first));
        ui->souvenirTable->setItem(i, 1, new QTableWidgetItem(
            QString("$%1").arg(souvenirs[i].second, 0, 'f', 2)));
    }

    qDebug() << "Found" << souvenirs.size() << "souvenirs for" << campusName;
}

void MainWindow::updateDistancesTable(const QString& startingCampus)
{
    // Skip update if placeholder is selected
    if (startingCampus.isEmpty() || startingCampus == "Please select a campus") {
        ui->distancesTable->clearContents();
        ui->distancesTable->setRowCount(0);
        return;
    }

    ui->distancesTable->clearContents();
    ui->distancesTable->setRowCount(0);

    // Get all distances from the starting campus
    for (const Campus& campus : allCampuses) {
        QString destinationCampus = campus.getName();
        if (destinationCampus != startingCampus) {
            double distance = dbManager->getDistance(startingCampus, destinationCampus);
            
            if (distance >= 0) {  // Only show valid distances
                int row = ui->distancesTable->rowCount();
                ui->distancesTable->insertRow(row);
                
                // Set campus name
                ui->distancesTable->setItem(row, 0, 
                    new QTableWidgetItem(destinationCampus));
                
                // Set distance with 1 decimal place
                ui->distancesTable->setItem(row, 1, 
                    new QTableWidgetItem(QString::number(distance, 'f', 1)));
            }
        }
    }

    // Sort the table by distance
    ui->distancesTable->sortByColumn(1, Qt::AscendingOrder);
}

void MainWindow::on_addToTripButton_clicked()
{
    // Get selected items
    QList<QListWidgetItem*> items = ui->campusList->selectedItems();
    
    // Add each selected item to the trip list if not already there
    for (QListWidgetItem* item : items) {
        QString campusName = item->text();
        // Check if campus is already in trip
        QList<QListWidgetItem*> matches = ui->selectedCampusList->findItems(campusName, Qt::MatchExactly);
        if (matches.isEmpty()) {
            ui->selectedCampusList->addItem(new QListWidgetItem(campusName));
            // Set background color to indicate selection
            item->setBackground(QColor(135, 206, 250));  // Light sky blue
            item->setFlags(item->flags() & ~Qt::ItemIsSelectable);  // Make item non-selectable while in trip
        }
    }
}

void MainWindow::on_removeFromTripButton_clicked()
{
    // Get selected items from trip list
    QList<QListWidgetItem*> items = ui->selectedCampusList->selectedItems();
    
    // Remove each selected item
    for (QListWidgetItem* item : items) {
        QString campusName = item->text();
        
        // Find and unhighlight the corresponding item in campusList
        QList<QListWidgetItem*> matches = ui->campusList->findItems(campusName, Qt::MatchExactly);
        for (QListWidgetItem* match : matches) {
            match->setBackground(QBrush());  // Reset background
            match->setFlags(match->flags() | Qt::ItemIsSelectable);  // Make item selectable again
        }
        
        delete ui->selectedCampusList->takeItem(ui->selectedCampusList->row(item));
    }
}

void MainWindow::on_optimizeRouteButton_clicked()
{
    // Get all campuses in the trip
    QVector<QString> tripCampuses;
    for (int i = 0; i < ui->selectedCampusList->count(); i++) {
        tripCampuses.append(ui->selectedCampusList->item(i)->text());
    }

    if (tripCampuses.size() < 2) {
        QMessageBox::warning(this, "Optimization Error", 
                           "Please select at least 2 campuses for optimization.");
        return;
    }

    // Find the optimal route
    QVector<QString> optimizedRoute = findOptimalRoute(tripCampuses);

    if (optimizedRoute.isEmpty()) {
        QMessageBox::warning(this, "Optimization Error", 
                           "Could not optimize the route. Please try again.");
        return;
    }

    // Clear and repopulate the selected list with optimized route
    ui->selectedCampusList->clear();
    for (const QString& campus : optimizedRoute) {
        ui->selectedCampusList->addItem(new QListWidgetItem(campus));
    }

    // Calculate and display total distance
    double totalDistance = calculateTotalDistance(optimizedRoute);
    if (totalDistance >= 0) {
        ui->totalDistanceLabel->setText(QString("Total Distance: %1 miles")
                                      .arg(totalDistance, 0, 'f', 1));
    }
}

QVector<QString> MainWindow::findOptimalRoute(const QVector<QString>& campuses)
{
    if (campuses.isEmpty()) return QVector<QString>();

    QVector<QString> route;
    QVector<bool> visited(campuses.size(), false);
    
    // Start with the first campus
    route.append(campuses[0]);
    visited[0] = true;
    
    // Find nearest neighbor for each subsequent campus
    while (route.size() < campuses.size()) {
        QString lastCampus = route.last();
        double minDistance = std::numeric_limits<double>::max();
        int nextIndex = -1;
        
        // Find the nearest unvisited campus
        for (int i = 0; i < campuses.size(); i++) {
            if (!visited[i]) {
                double distance = dbManager->getDistance(lastCampus, campuses[i]);
                if (distance > 0 && distance < minDistance) {
                    minDistance = distance;
                    nextIndex = i;
                }
            }
        }
        
        if (nextIndex == -1) break;  // No valid next campus found
        
        route.append(campuses[nextIndex]);
        visited[nextIndex] = true;
    }
    
    return route;
}

void MainWindow::on_calculateDistanceButton_clicked()
{
    // Get all campuses in the trip
    QVector<QString> tripCampuses;
    for (int i = 0; i < ui->selectedCampusList->count(); i++) {
        tripCampuses.append(ui->selectedCampusList->item(i)->text());
    }

    if (tripCampuses.size() < 2) {
        QMessageBox::warning(this, "Distance Calculation", 
                           "Please select at least 2 campuses to calculate distance.");
        return;
    }

    // Calculate total distance
    double totalDistance = calculateTotalDistance(tripCampuses);
    
    if (totalDistance >= 0) {
        ui->totalDistanceLabel->setText(QString("Total Distance: %1 miles")
                                      .arg(totalDistance, 0, 'f', 1));
        
        // Show detailed breakdown in a message box
        QString details = "Distance Breakdown:\n\n";
        for (int i = 0; i < tripCampuses.size() - 1; i++) {
            double segmentDistance = dbManager->getDistance(tripCampuses[i], tripCampuses[i + 1]);
            details += QString("%1 → %2: %3 miles\n")
                      .arg(tripCampuses[i])
                      .arg(tripCampuses[i + 1])
                      .arg(segmentDistance, 0, 'f', 1);
        }
        
        QMessageBox::information(this, "Trip Distance Details", details);
    } else {
        QMessageBox::warning(this, "Distance Calculation Error",
                           "Could not calculate distance for some segments of the trip.");
    }
}

double MainWindow::calculateTotalDistance(const QVector<QString>& route)
{
    double totalDistance = 0;
    
    for (int i = 0; i < route.size() - 1; i++) {
        double distance = dbManager->getDistance(route[i], route[i + 1]);
        if (distance < 0) return -1;  // Invalid distance found
        totalDistance += distance;
    }
    
    return totalDistance;
}

// Add navigation slots
void MainWindow::on_goToDistancesButton_clicked()
{
    ui->tabWidget->setCurrentIndex(3);  // Change to 3 for Distances tab
}

void MainWindow::on_goToSouvenirsButton_clicked()
{
    ui->tabWidget->setCurrentIndex(2);  // Keep as 2 for Souvenirs tab
}

void MainWindow::on_goToTripPlannerButton_clicked()
{
    ui->tabWidget->setCurrentIndex(1);  // Change to 1 for Trip Planner tab
}

void MainWindow::setupAdminControls()
{
    // Add an Admin menu if user is admin
    if (isAdmin) {
        QMenu* adminMenu = menuBar()->addMenu("Admin");
        
        QAction* manageInfoAction = new QAction("Manage College Information", this);
        connect(manageInfoAction, &QAction::triggered, this, [this]() {
            // Open admin panel
            AdminPanel* adminPanel = new AdminPanel(dbManager, this);
            adminPanel->exec();
        });
        
        adminMenu->addAction(manageInfoAction);
    }
}
