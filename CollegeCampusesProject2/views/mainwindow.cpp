#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "adminpanel.h"
#include <QTimer>
#include <QMessageBox>
#include <QToolBar>
#include <QListWidget>
#include <QIcon>
#include <QPushButton>
#include <QShortcut>
#include "utils/animatedbackground.h"

MainWindow::MainWindow(DBManager* db, bool isAdmin, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , dbManager(nullptr)
    , isAdmin(isAdmin)
{
    // Set the database pointer before UI setup
    dbManager = db;
    
    if (!db) {
        QMessageBox::critical(this, "Error", "Invalid database connection");
        return;
    }

    ui->setupUi(this);
    setWindowTitle("College Campus Tour");
    
    // Verify database connection before loading data
    if (!dbManager->isOpen()) {
        QMessageBox::critical(this, "Error", "Database connection is not open");
        return;
    }
    
    // Create and set up animated background with darker colors
    AnimatedBackground* background = new AnimatedBackground(this);
    
    // Use a dark color scheme for the background
    background->setColors({
        QColor(10, 15, 30),      // Very Dark Blue/Black
        QColor(20, 30, 60),      // Dark Blue
        QColor(40, 50, 100),     // Medium Dark Blue
        QColor(60, 80, 140)      // Accent Blue
    });
    
    // This will make the background fill the entire main window
    background->resize(size());
    
    // Make sure it stays at the back
    background->lower();
    
    // Start the animation
    background->startAnimation();
    
    // Apply dark theme to the entire window
    setStyleSheet(
        "QMainWindow { background-color: transparent; }"
        "QWidget { color: #e0e0e0; }"
        "QLineEdit, QTextEdit, QComboBox, QSpinBox { background-color: rgba(25, 30, 50, 180); color: #e0e0e0; border: 1px solid #4080b0; border-radius: 3px; padding: 3px; }"
        "QPushButton { background-color: #1a3c5e; color: white; border: none; border-radius: 4px; padding: 6px; }"
        "QPushButton:hover { background-color: #2a5c8e; }"
        "QPushButton:pressed { background-color: #10304e; }"
        "QTableView, QListView, QTreeView { background-color: rgba(20, 25, 40, 220); alternate-background-color: rgba(25, 30, 50, 220); color: #e0e0e0; gridline-color: #30405e; }"
        "QHeaderView::section { background-color: #1a2e4c; color: #e0e0e0; padding: 4px; border: 1px solid #30405e; }"
        "QMenu { background-color: #1a2e4c; color: #e0e0e0; border: 1px solid #30405e; }"
        "QMenu::item:selected { background-color: #2a5c8e; }"
    );
    
    // Make central widget very dark but semi-transparent to show the background waves
    if (ui->centralwidget) {
        ui->centralwidget->setStyleSheet("QWidget#centralwidget { background-color: rgba(15, 20, 35, 120); }");
    }
    
    // Add dark styling to tabs to match the background
    ui->tabWidget->setStyleSheet(
        "QTabWidget::pane { border: 1px solid #30405e; background-color: rgba(20, 25, 40, 200); }"
        "QTabBar::tab { background-color: #1a2e4c; color: #e0e0e0; padding: 8px 16px; margin-right: 2px; }"
        "QTabBar::tab:selected { background-color: #2a5c8e; }"
        "QTabBar::tab:hover:!selected { background-color: #254670; }"
    );
    
    // Setup admin menu only if user is admin
    if (isAdmin) {
        QMenu* adminMenu = menuBar()->addMenu("&Admin");
        QAction* manageCollegesAction = new QAction("&Manage Colleges", this);
        connect(manageCollegesAction, &QAction::triggered, this, &MainWindow::on_actionManageColleges_triggered);
        adminMenu->addAction(manageCollegesAction);
    }
    
    // Initialize basic UI components
    if (ui->souvenirsTable) {
        ui->souvenirsTable->setColumnCount(2);
        ui->souvenirsTable->setHorizontalHeaderLabels({"Name", "Price"});
        if (ui->souvenirsTable->horizontalHeader()) {
            ui->souvenirsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        }
    }
    
    // Delay connecting signals until the window is shown
    QTimer::singleShot(100, this, [this]() {
        // Connect tab change signal
        if (ui->tabWidget) {
            connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::onTabChanged);
            ui->tabWidget->setCurrentIndex(0);
            
            // Load initial data with delay
            QTimer::singleShot(200, this, [this]() {
                // Load initial data
                updateAllComboBoxes();
                refreshColleges();
                refreshDistances();
                refreshSouvenirs();
            });
        }
    });

    // Setup UI connections
    setupUiConnections();
}

void MainWindow::setupUiConnections()
{
    if (!ui) return;
    
    // Connect refresh buttons for each tab
    if (ui->refreshDistancesButton) {
        connect(ui->refreshDistancesButton, &QPushButton::clicked, this, &MainWindow::refreshDistances);
    }
    
    if (ui->refreshSouvenirsButton) {
        connect(ui->refreshSouvenirsButton, &QPushButton::clicked, this, &MainWindow::refreshSouvenirs);
    }
    
    // Setup trip planner connections
    setupTripPlanner();
    
    // Connect UI signals to slots
    QAction* exitAction = findChild<QAction*>("actionExit");
    if (exitAction) {
        connect(exitAction, &QAction::triggered, this, &QMainWindow::close);
    }
    
    QAction* aboutAction = findChild<QAction*>("actionAbout");
    if (aboutAction) {
        connect(aboutAction, &QAction::triggered, this, [this]() {
            QMessageBox::about(this, "About College Campus Tour",
                "College Campus Tour Application\n\n"
                "A comprehensive application for planning college campus tours,\n"
                "viewing campus information, and exploring souvenirs available at each location.");
        });
    }
    
    // Connect the college combo box to refresh souvenirs
    if (ui->collegeComboBox) {
        connect(ui->collegeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, [this](int index) {
            if (index > 0) { // Skip "Select a college" item
                refreshSouvenirs();
            }
        });
    }
}

void MainWindow::refreshAllData()
{
    qDebug() << "Performing full data refresh";
    
    // Force database reload
    if (dbManager) {
        dbManager->reloadDatabase();
    }
    
    // Refresh all UI components
    updateAllComboBoxes();
    refreshColleges();
    refreshSouvenirs();
    refreshDistances();
    
    // Force UI update
    update();
    if (ui && ui->tabWidget && ui->tabWidget->currentWidget()) {
        ui->tabWidget->currentWidget()->update();
    }
    
    qDebug() << "Full data refresh completed";
}

void MainWindow::on_actionManageColleges_triggered()
{
    if (!dbManager) return;
    
    AdminPanel* adminPanel = new AdminPanel(dbManager, this);
    
    // Simplified connections that call our comprehensive refresh
    connect(adminPanel, &AdminPanel::collegesChanged, this, &MainWindow::refreshAllData, Qt::DirectConnection);
    connect(adminPanel, &AdminPanel::souvenirsChanged, this, &MainWindow::refreshAllData, Qt::DirectConnection);
    connect(adminPanel, &AdminPanel::distancesChanged, this, &MainWindow::refreshAllData, Qt::DirectConnection);
    connect(adminPanel, &QDialog::finished, this, &MainWindow::refreshAllData, Qt::DirectConnection);
    
    adminPanel->exec();
    
    // One more refresh after dialog is fully closed
    QTimer::singleShot(100, this, &MainWindow::refreshAllData);
    
    delete adminPanel;
}

void MainWindow::showDistancesTab()
{
    if (ui->tabWidget) {
        for (int i = 0; i < ui->tabWidget->count(); i++) {
            if (ui->tabWidget->tabText(i).toLower().contains("distance")) {
                ui->tabWidget->setCurrentIndex(i);
                break;
            }
        }
    }
}

void MainWindow::showSouvenirsTab()
{
    if (ui->tabWidget) {
        for (int i = 0; i < ui->tabWidget->count(); i++) {
            if (ui->tabWidget->tabText(i).toLower().contains("souvenir")) {
                ui->tabWidget->setCurrentIndex(i);
                break;
            }
        }
    }
}

void MainWindow::showTripPlannerTab()
{
    if (ui->tabWidget) {
        for (int i = 0; i < ui->tabWidget->count(); i++) {
            if (ui->tabWidget->tabText(i).toLower().contains("trip")) {
                ui->tabWidget->setCurrentIndex(i);
                break;
            }
        }
    }
}

void MainWindow::displayDistances(const QString& distances)
{
    QTextEdit* distancesTextEdit = findChild<QTextEdit*>("distancesTextEdit");
    if (distancesTextEdit) {
        distancesTextEdit->setText(distances);
    } else {
        qDebug() << "Could not find distancesTextEdit widget";
    }
}

void MainWindow::onTabChanged(int index)
{
    if (!ui || !ui->tabWidget || index < 0 || index >= ui->tabWidget->count()) {
        qDebug() << "Invalid tab index or UI not ready";
        return;
    }
    
    QString tabName = ui->tabWidget->tabText(index).toLower();
    qDebug() << "Tab changed to:" << tabName;
    
    // Always update all combo boxes first to ensure they have latest data
    updateAllComboBoxes();
    
    // Use a timer to delay the specific tab refresh
    QTimer::singleShot(0, this, [this, tabName]() {
        if (!ui || !ui->tabWidget) return;
        
        if (tabName.contains("distance")) {
            refreshDistances();
        } else if (tabName.contains("souvenir")) {
            refreshSouvenirs();
        } else if (tabName.contains("trip")) {
            refreshColleges();
            
            // With the simplified UI, we don't need to handle startCollegeCombo anymore
            // Just refresh the trip planner lists
            loadAllColleges();
        }
        
        // Force immediate visual refresh only if UI is still valid
        if (ui && ui->tabWidget && ui->tabWidget->currentWidget()) {
            update();
            ui->tabWidget->currentWidget()->update();
        }
    });
}

void MainWindow::refreshColleges()
{
    if (!dbManager) return;
    qDebug() << "Refreshing colleges data";
    updateAllComboBoxes();
}

void MainWindow::refreshSouvenirs()
{
    qDebug() << "Refreshing souvenirs...";
    if (!dbManager || !ui) return;

    QComboBox* collegeCombo = ui->collegeComboBox;
    QTableWidget* souvenirsTable = ui->souvenirsTable;
    
    if (!collegeCombo || !souvenirsTable) {
        qDebug() << "Could not find collegeComboBox or souvenirsTable";
        return;
    }
    
    // Make the table non-editable
    souvenirsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    QString selectedCollege = collegeCombo->currentText();
    if (selectedCollege.isEmpty() || selectedCollege == "Select a college") {
        souvenirsTable->setRowCount(0);
        return;
    }
    
    QVector<QPair<QString, double>> souvenirs = dbManager->getSouvenirs(selectedCollege);
    souvenirsTable->setRowCount(souvenirs.size());
    
    for (int i = 0; i < souvenirs.size(); ++i) {
        QTableWidgetItem* nameItem = new QTableWidgetItem(souvenirs.at(i).first);
        QTableWidgetItem* priceItem = new QTableWidgetItem(
            QString::number(souvenirs.at(i).second, 'f', 2));
        
        // Ensure items are not editable by setting appropriate flags
        nameItem->setFlags(nameItem->flags() & ~Qt::ItemIsEditable);
        priceItem->setFlags(priceItem->flags() & ~Qt::ItemIsEditable);
        
        souvenirsTable->setItem(i, 0, nameItem);
        souvenirsTable->setItem(i, 1, priceItem);
    }
    
    souvenirsTable->sortItems(0);
}

void MainWindow::refreshDistances()
{
    if (!dbManager) return;
    
    qDebug() << "Refreshing distances data";
    
    // Refresh distances display
    if (QTextEdit* distancesText = findChild<QTextEdit*>("distancesTextEdit")) {
        QString output;
        QTextStream stream(&output);
        
        QVector<Campus> campuses = dbManager->getAllCampuses();
        for (int i = 0; i < campuses.size(); ++i) {
            const Campus& from = campuses.at(i);
            stream << "From " << from.getName() << ":\n";
            for (int j = 0; j < campuses.size(); ++j) {
                const Campus& to = campuses.at(j);
                if (from.getName() != to.getName()) {
                    double distance = dbManager->getDistance(from.getName(), to.getName());
                    stream << "  To " << to.getName() << ": " << distance << " miles\n";
                }
            }
            stream << "\n";
        }
        
        distancesText->setText(output);
    }
    
    // Also refresh any distance-related combo boxes in trip planner
    refreshColleges();  // This will update college selection boxes
}

void MainWindow::updateAllComboBoxes()
{
    if (!dbManager || !ui) return;
    
    qDebug() << "Updating all combo boxes";
    const QVector<Campus> campuses = dbManager->getAllCampuses();
    
    // Update collegeComboBox
    if (ui->collegeComboBox) {
        QComboBox* combo = ui->collegeComboBox;
        QString currentText = combo->currentText();
        combo->blockSignals(true);
        combo->clear();
        combo->addItem("Select a college");
        
        for (const Campus& campus : campuses) {
            combo->addItem(campus.getName());
        }
        
        int index = combo->findText(currentText);
        combo->setCurrentIndex(index != -1 ? index : 0);
        combo->blockSignals(false);
        qDebug() << "Updated collegeComboBox with" << combo->count() << "items";
    }
    
    // The startCollegeCombo has been removed in the UI simplification
    // so we don't need to update it anymore
}

void MainWindow::setupTripPlanner()
{
    if (!ui->allCollegesList || !ui->tripCollegesList) return;
    
    // Connect buttons for trip management
    connect(ui->addToTripButton, &QPushButton::clicked, this, &MainWindow::addToTrip);
    connect(ui->removeFromTripButton, &QPushButton::clicked, this, &MainWindow::removeFromTrip);
    connect(ui->moveUpButton, &QPushButton::clicked, this, &MainWindow::moveCollegeUp);
    connect(ui->moveDownButton, &QPushButton::clicked, this, &MainWindow::moveCollegeDown);
    connect(ui->optimizeRouteButton, &QPushButton::clicked, this, &MainWindow::optimizeRoute);
    
    // Connect the Reset Trip button that's now in the UI file
    connect(ui->resetTripButton, &QPushButton::clicked, this, &MainWindow::resetTrip);
    
    // Allow double-click to add colleges to trip
    connect(ui->allCollegesList, &QListWidget::itemDoubleClicked, this, [this](QListWidgetItem* item) {
        QList<QListWidgetItem*> items;
        items.append(item);
        addCollegesToTrip(items);
    });
    
    // Allow double-click to remove colleges from trip
    connect(ui->tripCollegesList, &QListWidget::itemDoubleClicked, this, [this](QListWidgetItem* item) {
        QList<QListWidgetItem*> items;
        items.append(item);
        removeCollegesFromTrip(items);
    });
    
    // REMOVE the Trip Actions section that's showing at the bottom 
    QWidget* tripActionsGroup = ui->tripPlannerTab->findChild<QWidget*>("tripActionsGroupBox");
    if (tripActionsGroup) {
        tripActionsGroup->hide();
        tripActionsGroup->setEnabled(false);
        tripActionsGroup->setMaximumSize(0, 0);
        
        // Try to find its parent layout and remove it from there
        QLayout* actionsParentLayout = tripActionsGroup->parentWidget()->layout();
        if (actionsParentLayout) {
            actionsParentLayout->removeWidget(tripActionsGroup);
        }
    }
    
    // Load all colleges and update highlighting
    loadAllColleges();
    updateTripCollegeHighlighting();
}

void MainWindow::loadAllColleges()
{
    if (!ui->allCollegesList || !dbManager) return;
    
    ui->allCollegesList->clear();
    
    // Get all campuses from the database
    QVector<Campus> campuses = dbManager->getAllCampuses();
    
    // Create a sorted list of college names for better organization
    QStringList sortedCollegeNames;
    for (const Campus& campus : campuses) {
        sortedCollegeNames << campus.getName();
    }
    
    // Sort the college names alphabetically
    sortedCollegeNames.sort(Qt::CaseInsensitive);
    
    // Add the sorted colleges to the list with sequential display IDs
    for (int i = 0; i < sortedCollegeNames.size(); i++) {
        // Set the display ID as the item's data (Role: Qt::UserRole)
        QListWidgetItem* item = new QListWidgetItem(sortedCollegeNames[i]);
        item->setData(Qt::UserRole, i + 1); // Sequential ID starting from 1
        ui->allCollegesList->addItem(item);
    }
    
    // Update highlighting after loading colleges
    updateTripCollegeHighlighting();
    
    qDebug() << "Loaded" << sortedCollegeNames.size() << "colleges in alphabetical order with sequential IDs";
}

// New method to update highlighting of colleges that are in the trip
void MainWindow::updateTripCollegeHighlighting()
{
    if (!ui->allCollegesList || !ui->tripCollegesList) return;
    
    // Create a set of colleges in the trip for quick lookup
    QSet<QString> collegesInTrip;
    for (int i = 0; i < ui->tripCollegesList->count(); i++) {
        collegesInTrip.insert(ui->tripCollegesList->item(i)->text());
    }
    
    // Update the highlighting in the all colleges list
    for (int i = 0; i < ui->allCollegesList->count(); i++) {
        QListWidgetItem* item = ui->allCollegesList->item(i);
        if (collegesInTrip.contains(item->text())) {
            // Highlight colleges that are already in the trip
            item->setBackground(QColor(60, 100, 160, 100)); // Semi-transparent highlight color
            item->setForeground(QColor(220, 220, 220)); // Light text for contrast
        } else {
            // Reset highlighting for colleges not in the trip
            item->setBackground(QColor(0, 0, 0, 0)); // Transparent
            item->setForeground(QColor(224, 224, 224)); // Default text color
        }
    }
}

void MainWindow::addToTrip()
{
    if (!ui->allCollegesList || !ui->tripCollegesList) return;
    
    QList<QListWidgetItem*> selectedItems = ui->allCollegesList->selectedItems();
    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, "Trip Planning", "Please select a college to add to your trip.");
        return;
    }
    
    addCollegesToTrip(selectedItems);
}

void MainWindow::addCollegesToTrip(const QList<QListWidgetItem*>& items)
{
    if (!ui->allCollegesList || !ui->tripCollegesList) return;
    
    bool addedAny = false;
    
    for (QListWidgetItem* item : items) {
        QString collegeName = item->text();
        
        // Check if the college is already in the trip
        bool alreadyAdded = false;
        for (int i = 0; i < ui->tripCollegesList->count(); i++) {
            if (ui->tripCollegesList->item(i)->text() == collegeName) {
                alreadyAdded = true;
                break;
            }
        }
        
        if (!alreadyAdded) {
            ui->tripCollegesList->addItem(collegeName);
            addedAny = true;
        }
    }
    
    // Update highlighting to show which colleges are in the trip
    updateTripCollegeHighlighting();
    
    // Calculate the route if we have at least one college and we added something new
    if (addedAny && ui->tripCollegesList->count() > 0) {
        calculateRoute();
    }
}

void MainWindow::removeFromTrip()
{
    if (!ui->tripCollegesList) return;
    
    QList<QListWidgetItem*> selectedItems = ui->tripCollegesList->selectedItems();
    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, "Trip Planning", "Please select a college to remove from your trip.");
        return;
    }
    
    removeCollegesFromTrip(selectedItems);
}

void MainWindow::removeCollegesFromTrip(const QList<QListWidgetItem*>& items)
{
    if (!ui->tripCollegesList) return;
    
    for (QListWidgetItem* item : items) {
        delete ui->tripCollegesList->takeItem(ui->tripCollegesList->row(item));
    }
    
    // Update highlighting after removing colleges
    updateTripCollegeHighlighting();
    
    // Update the trip details
    calculateRoute();
}

void MainWindow::moveCollegeUp()
{
    if (!ui->tripCollegesList) return;
    
    int currentRow = ui->tripCollegesList->currentRow();
    if (currentRow <= 0) return;
    
    QListWidgetItem* item = ui->tripCollegesList->takeItem(currentRow);
    ui->tripCollegesList->insertItem(currentRow - 1, item);
    ui->tripCollegesList->setCurrentRow(currentRow - 1);
    
    // Recalculate the route
    calculateRoute();
}

void MainWindow::moveCollegeDown()
{
    if (!ui->tripCollegesList) return;
    
    int currentRow = ui->tripCollegesList->currentRow();
    if (currentRow < 0 || currentRow >= ui->tripCollegesList->count() - 1) return;
    
    QListWidgetItem* item = ui->tripCollegesList->takeItem(currentRow);
    ui->tripCollegesList->insertItem(currentRow + 1, item);
    ui->tripCollegesList->setCurrentRow(currentRow + 1);
    
    // Recalculate the route
    calculateRoute();
}

void MainWindow::calculateRoute()
{
    if (!ui->tripResultsText || !ui->tripCollegesList || !dbManager) return;
    
    int numColleges = ui->tripCollegesList->count();
    if (numColleges == 0) {
        ui->tripResultsText->clear();
        return;
    }
    
    // Get the ordered list of colleges
    QStringList orderedRoute;
    for (int i = 0; i < numColleges; i++) {
        orderedRoute << ui->tripCollegesList->item(i)->text();
    }
    
    // Calculate distances for the ordered route
    double totalDistance = 0;
    QString routeText = "Trip Route:\n\n";
    
    routeText += "1. " + orderedRoute[0] + " (Starting Point)\n";
    
    for (int i = 1; i < orderedRoute.size(); i++) {
        QString from = orderedRoute[i-1];
        QString to = orderedRoute[i];
        double distance = dbManager->getDistance(from, to);
        totalDistance += distance;
        
        routeText += QString("%1. %2 (Distance from previous: %3 miles)\n")
                    .arg(i + 1)
                    .arg(to)
                    .arg(distance);
    }
    
    routeText += QString("\nTotal Distance: %1 miles").arg(totalDistance);
    ui->tripResultsText->setText(routeText);
}

void MainWindow::optimizeRoute()
{
    if (!ui->tripCollegesList || !dbManager) return;
    
    int numColleges = ui->tripCollegesList->count();
    if (numColleges <= 2) {
        // No need to optimize with 0, 1, or 2 colleges
        return;
    }
    
    // Get all colleges in the current trip
    QStringList colleges;
    for (int i = 0; i < numColleges; i++) {
        colleges << ui->tripCollegesList->item(i)->text();
    }
    
    // Keep the starting college (first in the list) fixed
    QString startCollege = colleges[0];
    QStringList collegesForOptimization = colleges.mid(1);
    
    // Create a distance matrix for optimization
    QVector<QVector<double>> distances(collegesForOptimization.size(), QVector<double>(collegesForOptimization.size()));
    
    // Fill the distance matrix
    for (int i = 0; i < collegesForOptimization.size(); i++) {
        for (int j = 0; j < collegesForOptimization.size(); j++) {
            if (i != j) {
                distances[i][j] = dbManager->getDistance(collegesForOptimization[i], collegesForOptimization[j]);
            } else {
                distances[i][j] = 0;
            }
        }
    }
    
    // Nearest neighbor algorithm for optimization
    QVector<int> optimizedRoute;
    QVector<bool> visited(collegesForOptimization.size(), false);
    
    // Start from the starting college
    QString current = startCollege;
    
    // Find the optimal order
    while (optimizedRoute.size() < collegesForOptimization.size()) {
        int nearest = -1;
        double minDist = std::numeric_limits<double>::max();
        
        for (int i = 0; i < collegesForOptimization.size(); i++) {
            if (!visited[i]) {
                double d = dbManager->getDistance(current, collegesForOptimization[i]);
                if (d < minDist) {
                    minDist = d;
                    nearest = i;
                }
            }
        }
        
        if (nearest != -1) {
            optimizedRoute.append(nearest);
            visited[nearest] = true;
            current = collegesForOptimization[nearest];
        }
    }
    
    // Rebuild the trip with the optimized route
    // Keep the first college (starting point) and reorder the rest
    ui->tripCollegesList->clear();
    ui->tripCollegesList->addItem(startCollege);
    
    for (int index : optimizedRoute) {
        ui->tripCollegesList->addItem(collegesForOptimization[index]);
    }
    
    // Recalculate the route
    calculateRoute();
    
    QMessageBox::information(this, "Route Optimized", 
                          "Your route has been optimized to minimize total distance.");
}

void MainWindow::resetTrip()
{
    if (!ui->tripCollegesList || !ui->tripResultsText) return;
    
    ui->tripCollegesList->clear();
    ui->tripResultsText->clear();
    
    // Refresh the all colleges list too
    loadAllColleges();
    
    // Make sure highlighting is updated
    updateTripCollegeHighlighting();
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    
    // Make sure the background widget also resizes
    QList<AnimatedBackground*> backgrounds = findChildren<AnimatedBackground*>();
    if (!backgrounds.isEmpty()) {
        backgrounds.first()->resize(size());
    }
}

// Change the destructor to not emit any signals
MainWindow::~MainWindow()
{
    // No signal emission
    delete ui;
} 