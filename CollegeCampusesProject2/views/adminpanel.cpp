#include "adminpanel.h"
#include "ui_adminpanel.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QHeaderView>
#include "addcollegedialog.h"
#include <QUuid>
#include <QCryptographicHash>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSqlRecord>
#include <QLabel>
#include <QDialog>
#include <QTableWidget>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QDoubleValidator>

AdminPanel::AdminPanel(DBManager* db, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AdminPanel)
    , dbManager(db)
    , hasUnsavedChanges(false)
{
    ui->setupUi(this);
    setWindowTitle("Admin Panel");
    
    // Set a larger size for the dialog
    resize(900, 600);
    
    setupTables();

    // Add the SQL terminal setup
    setupSqlTerminal();

    // Connect tab widget signal
    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &AdminPanel::on_tabWidget_currentChanged);

    // Initialize buttons for the default tab
    on_tabWidget_currentChanged(ui->tabWidget->currentIndex());
    
    // Load users data when showing the admin panel
    loadUsers();
    
    // Update souvenir combo box
    updateSouvenirComboBox();
}

AdminPanel::~AdminPanel()
{
    delete ui;
}

void AdminPanel::setupTables()
{
    // Setup users table
    if (ui->usersTableView) {
        ui->usersTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->usersTableView->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->usersTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->usersTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        
        // Find and update the User Tab button if it exists
        if (ui->userTabButton) {
            ui->userTabButton->setText("Apply");
            
            // Disconnect any existing connections
            disconnect(ui->userTabButton, nullptr, this, nullptr);
            
            // Connect to a new slot for applying changes
            connect(ui->userTabButton, &QPushButton::clicked, this, &AdminPanel::applyUserChanges);
        }
    }
    
    // Setup colleges table
    if (ui->collegesTable) {
        ui->collegesTable->setColumnCount(2);
        ui->collegesTable->setHorizontalHeaderLabels({"ID", "Name"});
        ui->collegesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->collegesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->collegesTable->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->collegesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
    
    // Setup distances table
    if (ui->distancesTable) {
        ui->distancesTable->setColumnCount(3);
        ui->distancesTable->setHorizontalHeaderLabels({"From", "To", "Distance"});
        ui->distancesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->distancesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->distancesTable->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->distancesTable->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);
        
        // Add buttons to the distances tab
        QWidget* distancesTab = ui->tabWidget->widget(2); // Distances tab is index 2
        QVBoxLayout* layout = nullptr;
        
        // Check if there's already a layout
        if (distancesTab->layout()) {
            layout = qobject_cast<QVBoxLayout*>(distancesTab->layout());
        } else {
            // Create a new layout if there isn't one
            layout = new QVBoxLayout(distancesTab);
            // Add the distances table to the layout
            layout->addWidget(ui->distancesTable);
        }
        
        // Create a horizontal layout for the buttons
        QHBoxLayout* buttonLayout = new QHBoxLayout();
        
        // Create buttons
        QPushButton* applyButton = new QPushButton("Apply");
        QPushButton* cancelButton = new QPushButton("Cancel");
        QPushButton* closeButton = new QPushButton("Close");
        
        // Add buttons to the horizontal layout
        buttonLayout->addWidget(applyButton);
        buttonLayout->addWidget(cancelButton);
        buttonLayout->addWidget(closeButton);
        
        // Add the button layout to the main layout
        layout->addLayout(buttonLayout);
        
        // Connect buttons to slots
        connect(applyButton, &QPushButton::clicked, this, &AdminPanel::applyDistanceChanges);
        connect(cancelButton, &QPushButton::clicked, this, &AdminPanel::cancelDistanceChanges);
        connect(closeButton, &QPushButton::clicked, this, &AdminPanel::closeDistancesTab);
    }
    
    // Setup souvenirs table
    if (ui->souvenirsTable) {
        ui->souvenirsTable->setColumnCount(2);
        ui->souvenirsTable->setHorizontalHeaderLabels({"Name", "Price"});
        ui->souvenirsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->souvenirsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->souvenirsTable->setEditTriggers(QTableWidget::DoubleClicked | QTableWidget::EditKeyPressed);
        
        // Only make the price column editable
        connect(ui->souvenirsTable, &QTableWidget::itemChanged, this, [this](QTableWidgetItem* item) {
            if (item->column() == 1) { // Price column
                bool ok;
                double newPrice = item->text().toDouble(&ok);
                if (!ok || newPrice < 0) {
                    QMessageBox::warning(this, "Invalid Input", "Please enter a valid positive number");
                    loadSouvenirs(ui->souvenirCollegeCombo->currentText()); // Reset the table
                    return;
                }
                hasUnsavedChanges = true;
            } else {
                // Don't allow editing of Name column
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            }
        });
    }
}

void AdminPanel::closeEvent(QCloseEvent* event)
{
    if (hasUnsavedChanges) {
        int result = QMessageBox::question(this, "Unsaved Changes", 
                                         "You have unsaved changes. Do you want to save before closing?", 
                                         QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        
        if (result == QMessageBox::Yes) {
            // Save changes
            event->accept();
        } else if (result == QMessageBox::No) {
            event->accept();
        } else {
            // Cancel was clicked, do nothing
            event->ignore();
        }
    } else {
        event->accept();
    }
}

void AdminPanel::reject()
{
    if (hasUnsavedChanges) {
        int result = QMessageBox::question(this, "Unsaved Changes", 
                                         "You have unsaved changes. Do you want to save before closing?", 
                                         QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        
        if (result == QMessageBox::Yes) {
            // Save changes
            QDialog::accept();
        } else if (result == QMessageBox::No) {
            QDialog::reject();
        } else {
            // Cancel was clicked, do nothing
            return;
        }
    } else {
        QDialog::reject();
    }
}

void AdminPanel::on_tabWidget_currentChanged(int index)
{
    qDebug() << "Tab changed to index:" << index;
    
    // Load data based on the selected tab
    if (index == 0) { // Users tab
        loadUsers();
    } else if (index == 1) { // Souvenirs tab
        updateSouvenirComboBox();
    } else if (index == 2) { // Distances tab
        loadDistances();
    } else if (index == 3) { // Colleges tab
        loadColleges();
    } else if (index == 4) { // SQL Terminal tab
        // No need to load data for the SQL Terminal tab
    }
}

void AdminPanel::loadUsers()
{
    qDebug() << "Loading users...";
    
    // Create a model for the users table
    if (!userModel) {
        userModel = new QSqlQueryModel(this);
    }
    
    // Set up the query to get all users
    QSqlQuery query(dbManager->getDB());
    query.exec("SELECT id, username, is_admin FROM users ORDER BY username");
    
    // Set the query for the model
    userModel->setQuery(std::move(query));
    
    // Set headers
    userModel->setHeaderData(0, Qt::Horizontal, "ID");
    userModel->setHeaderData(1, Qt::Horizontal, "Username");
    userModel->setHeaderData(2, Qt::Horizontal, "Admin");
    
    // Set the model for the table view
    ui->usersTableView->setModel(userModel);
    
    // Adjust column widths
    ui->usersTableView->setColumnWidth(0, 50);  // ID column
    ui->usersTableView->setColumnWidth(1, 200); // Username column
    ui->usersTableView->setColumnWidth(2, 50);  // Admin column
    
    qDebug() << "Users loaded successfully. Row count:" << userModel->rowCount();
}

void AdminPanel::loadColleges()
{
    QVector<Campus> campuses = dbManager->getAllCampuses();
    ui->collegesTable->setRowCount(campuses.size());
    
    for (int i = 0; i < campuses.size(); ++i) {
        ui->collegesTable->setItem(i, 0, new QTableWidgetItem(QString::number(campuses[i].getId())));
        ui->collegesTable->setItem(i, 1, new QTableWidgetItem(campuses[i].getName()));
    }
}

void AdminPanel::loadDistances()
{
    qDebug() << "Loading distances...";
    
    // Get all campuses
    QVector<Campus> allCampuses = dbManager->getAllCampuses();
    qDebug() << "Found" << allCampuses.size() << "campuses";
    
    // Block signals while updating
    ui->distancesTable->blockSignals(true);
    
    int numCampuses = allCampuses.size();
    int totalRows = numCampuses * (numCampuses - 1);
    ui->distancesTable->setRowCount(totalRows);
    
    qDebug() << "Setting up" << totalRows << "distance rows";
    
    int currentRow = 0;
    for (const Campus& from : allCampuses) {
        for (const Campus& to : allCampuses) {
            if (from.getName() != to.getName()) {
                QTableWidgetItem* fromItem = new QTableWidgetItem(from.getName());
                QTableWidgetItem* toItem = new QTableWidgetItem(to.getName());
                
                // Get distance
                double distance = dbManager->getDistance(from.getName(), to.getName());
                qDebug() << "Distance from" << from.getName() << "to" << to.getName() << ":" << distance;
                
                QTableWidgetItem* distanceItem = new QTableWidgetItem(QString::number(distance));
                
                // Make only the from and to columns non-editable, but allow distance to be edited
                fromItem->setFlags(fromItem->flags() & ~Qt::ItemIsEditable);
                toItem->setFlags(toItem->flags() & ~Qt::ItemIsEditable);
                // Distance column is editable by default
                
                ui->distancesTable->setItem(currentRow, 0, fromItem);
                ui->distancesTable->setItem(currentRow, 1, toItem);
                ui->distancesTable->setItem(currentRow, 2, distanceItem);
                
                currentRow++;
            }
        }
    }
    
    // Connect to itemChanged signal to track changes
    connect(ui->distancesTable, &QTableWidget::itemChanged, this, &AdminPanel::onDistanceChanged);
    
    ui->distancesTable->blockSignals(false);
    qDebug() << "Distances loaded successfully";
}

void AdminPanel::loadSouvenirs(const QString& collegeName)
{
    if (collegeName == "Select a college") {
        ui->souvenirsTable->clearContents();
        ui->souvenirsTable->setRowCount(0);
        return;
    }

    // Block signals while updating
    ui->souvenirsTable->blockSignals(true);
    
    QVector<QPair<QString, double>> souvenirs = dbManager->getSouvenirs(collegeName);
    ui->souvenirsTable->setRowCount(souvenirs.size());

    // Change column count back to 2 (Name and Price)
    ui->souvenirsTable->setColumnCount(2);
    ui->souvenirsTable->setHorizontalHeaderLabels({"Name", "Price"});

    for (int i = 0; i < souvenirs.size(); ++i) {
        QTableWidgetItem* nameItem = new QTableWidgetItem(souvenirs[i].first);
        nameItem->setFlags(nameItem->flags() & ~Qt::ItemIsEditable);
        
        QTableWidgetItem* priceItem = new QTableWidgetItem(
            QString::number(souvenirs[i].second, 'f', 2));
        
        ui->souvenirsTable->setItem(i, 0, nameItem);
        ui->souvenirsTable->setItem(i, 1, priceItem);
    }

    ui->souvenirsTable->blockSignals(false);
}

void AdminPanel::on_souvenirCollegeCombo_currentTextChanged(const QString &collegeName)
{
    if (!collegeName.isEmpty() && collegeName != "Select a college") {
        loadSouvenirs(collegeName);
    }
}

void AdminPanel::on_addUserButton_clicked()
{
    qDebug() << "Add User button clicked";
    
    bool ok;
    QString username = QInputDialog::getText(this, "Add User", "Username:", QLineEdit::Normal, "", &ok);
    if (!ok || username.isEmpty()) {
        qDebug() << "User canceled or entered empty username";
        return;
    }
    
    qDebug() << "Username entered:" << username;
    
    // Check if username already exists
    if (dbManager->userExists(username)) {
        qDebug() << "Username already exists:" << username;
        QMessageBox::warning(this, "Add User", "Username already exists!");
        return;
    }
    
    QString password = QInputDialog::getText(this, "Add User", "Password:", QLineEdit::Password, "", &ok);
    if (!ok || password.isEmpty()) {
        qDebug() << "User canceled or entered empty password";
        return;
    }
    
    qDebug() << "Password entered (length):" << password.length();
    
    bool isAdmin = QMessageBox::question(this, "Add User", "Make this user an admin?", 
                                        QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes;
    
    qDebug() << "Is admin:" << isAdmin;
    qDebug() << "Attempting to add user to database...";
    
    // Create a query to get the next available ID
    QSqlQuery getMaxIdQuery(dbManager->getDB());
    getMaxIdQuery.exec("SELECT MAX(id) FROM users");
    int nextId = 1; // Default if no users exist
    
    if (getMaxIdQuery.next() && !getMaxIdQuery.value(0).isNull()) {
        nextId = getMaxIdQuery.value(0).toInt() + 1;
    }
    
    // Hash the password
    QString passwordHash = QString(QCryptographicHash::hash(
        password.toUtf8(), QCryptographicHash::Sha256).toHex());
    
    // Directly create the query for adding a user
    QSqlQuery query(dbManager->getDB());
    query.prepare("INSERT INTO users (id, username, password, is_admin) VALUES (?, ?, ?, ?)");
    query.addBindValue(nextId);
    query.addBindValue(username);
    query.addBindValue(passwordHash);
    query.addBindValue(isAdmin ? 1 : 0);
    
    bool success = query.exec();
    
    if (success) {
        QMessageBox::information(this, "Add User", "User added successfully!");
        loadUsers(); // Refresh the users list
    } else {
        qDebug() << "SQL Error:" << query.lastError().text();
        QMessageBox::critical(this, "Add User", "Failed to add user! Check the debug log for details.");
    }
}

void AdminPanel::on_editUserButton_clicked()
{
    // Get the selected user
    QModelIndex currentIndex = ui->usersTableView->currentIndex();
    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "Edit User", "Please select a user to edit.");
        return;
    }
    
    // Get the user ID and username from the model
    int row = currentIndex.row();
    DBManager::UserInfo selectedUser;
    selectedUser.id = userModel->index(row, 0).data().toString();
    selectedUser.username = userModel->index(row, 1).data().toString();
    selectedUser.isAdmin = userModel->index(row, 2).data().toBool();
    
    // Check if this is the original admin user
    if (dbManager->isOriginalAdmin(userModel->index(row, 0).data().toString())) {
        QMessageBox::warning(this, "Edit User", "Cannot edit the original admin user!");
        return;
    }
    
    // Get new username
    bool ok;
    QString newUsername = QInputDialog::getText(this, "Edit User", 
                                              "New Username:", QLineEdit::Normal, 
                                              selectedUser.username, &ok);
    if (!ok) return;
    
    // Get new password (optional)
    QString newPassword = QInputDialog::getText(this, "Edit User", 
                                              "New Password (leave empty to keep current):", 
                                              QLineEdit::Password, "", &ok);
    if (!ok) return;
    
    // Get admin status
    bool isAdmin = QMessageBox::question(this, "Edit User", "Make this user an admin?", 
                                       QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes;
    
    // Update the user
    if (dbManager->updateUser(selectedUser.id, newUsername, newPassword, isAdmin)) {
        QMessageBox::information(this, "Edit User", "User updated successfully!");
        loadUsers(); // Refresh the users list
    } else {
        QMessageBox::critical(this, "Edit User", "Failed to update user!");
    }
}

void AdminPanel::on_deleteUserButton_clicked()
{
    // Get the selected user
    QModelIndex currentIndex = ui->usersTableView->currentIndex();
    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "Delete User", "Please select a user to delete.");
        return;
    }
    
    // Get the user ID and username from the model
    int row = currentIndex.row();
    DBManager::UserInfo selectedUser;
    selectedUser.id = userModel->index(row, 0).data().toString();
    selectedUser.username = userModel->index(row, 1).data().toString();
    
    // Check if this is the original admin user
    if (dbManager->isOriginalAdmin(userModel->index(row, 0).data().toString())) {
        QMessageBox::warning(this, "Delete User", "Cannot delete the original admin user!");
        return;
    }
    
    // Confirm deletion
    if (QMessageBox::question(this, "Delete User", 
                            QString("Are you sure you want to delete user '%1'?").arg(selectedUser.username), 
                            QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes) {
        return;
    }
    
    // Delete the user
    if (dbManager->deleteUser(selectedUser.id)) {
        QMessageBox::information(this, "Delete User", "User deleted successfully!");
        loadUsers(); // Refresh the users list
    } else {
        QMessageBox::critical(this, "Delete User", "Failed to delete user!");
    }
}

void AdminPanel::on_userTabButton_clicked()
{
    ui->tabWidget->setCurrentIndex(0); // Switch to the Users tab
}

void AdminPanel::on_addCollegeButton_clicked()
{
    // Get all existing colleges first
    QVector<Campus> existingColleges = dbManager->getAllCampuses();
    
    // Create a dialog for collecting the new college information
    QDialog addCollegeDialog(this);
    addCollegeDialog.setWindowTitle("Add New College");
    addCollegeDialog.setMinimumWidth(500);
    
    // Create the form layout
    QVBoxLayout* mainLayout = new QVBoxLayout(&addCollegeDialog);
    QFormLayout* formLayout = new QFormLayout();
    
    // Add college name field
    QLineEdit* nameEdit = new QLineEdit(&addCollegeDialog);
    formLayout->addRow("College Name:", nameEdit);
    
    // Add a separator
    QFrame* line = new QFrame(&addCollegeDialog);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    
    // Add a label for the distances section
    QLabel* distancesLabel = new QLabel("Distances to other colleges (miles):", &addCollegeDialog);
    distancesLabel->setAlignment(Qt::AlignLeft);
    distancesLabel->setStyleSheet("font-weight: bold; margin-top: 10px;");
    
    // Create a table for the distances
    QTableWidget* distancesTable = new QTableWidget(&addCollegeDialog);
    distancesTable->setColumnCount(2);
    distancesTable->setHorizontalHeaderLabels({"College", "Distance (miles)"});
    distancesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    distancesTable->setRowCount(existingColleges.size());
    
    // Add rows for each existing college
    for (int i = 0; i < existingColleges.size(); i++) {
        QTableWidgetItem* collegeItem = new QTableWidgetItem(existingColleges[i].getName());
        collegeItem->setFlags(collegeItem->flags() & ~Qt::ItemIsEditable); // Make college name read-only
        distancesTable->setItem(i, 0, collegeItem);
        
        // Add a double validator for the distance
        QLineEdit* distanceEdit = new QLineEdit();
        distanceEdit->setValidator(new QDoubleValidator(0, 10000, 2, distanceEdit));
        distanceEdit->setPlaceholderText("Enter distance");
        distancesTable->setCellWidget(i, 1, distanceEdit);
    }
    
    // Add buttons
    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &addCollegeDialog);
    
    // Add widgets to layouts
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(line);
    mainLayout->addWidget(distancesLabel);
    mainLayout->addWidget(distancesTable);
    mainLayout->addWidget(buttonBox);
    
    // Connect buttons
    connect(buttonBox, &QDialogButtonBox::accepted, &addCollegeDialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &addCollegeDialog, &QDialog::reject);
    
    // Show the dialog and process the result
    if (addCollegeDialog.exec() == QDialog::Accepted) {
        QString collegeName = nameEdit->text().trimmed();
        
        // Validate the college name
        if (collegeName.isEmpty()) {
            QMessageBox::warning(this, "Add College", "College name cannot be empty.");
            return;
        }
        
        // Check if college already exists
        if (dbManager->campusExists(collegeName)) {
            QMessageBox::warning(this, "Add College", "A college with this name already exists.");
            return;
        }
        
        // Collect the distances
        QMap<QString, double> distances;
        bool allDistancesValid = true;
        
        for (int i = 0; i < existingColleges.size(); i++) {
            QString existingCollegeName = existingColleges[i].getName();
            QLineEdit* distanceEdit = qobject_cast<QLineEdit*>(distancesTable->cellWidget(i, 1));
            
            if (distanceEdit && !distanceEdit->text().isEmpty()) {
                bool ok;
                double distance = distanceEdit->text().toDouble(&ok);
                
                if (ok && distance >= 0) {
                    distances[existingCollegeName] = distance;
                } else {
                    allDistancesValid = false;
                    QMessageBox::warning(this, "Add College", 
                                      "Invalid distance value for " + existingCollegeName + ". Please enter a valid number.");
                    break;
                }
            } else {
                allDistancesValid = false;
                QMessageBox::warning(this, "Add College", 
                                   "Please enter a distance for " + existingCollegeName + ".");
                break;
            }
        }
        
        // If all distances are valid, add the college and its distances
        if (allDistancesValid) {
            // First, add the college
            if (dbManager->addCampus(collegeName)) {
                // Then add all the distances
                bool allDistancesAdded = true;
                
                for (auto it = distances.begin(); it != distances.end(); ++it) {
                    QString targetCollegeName = it.key();
                    double distance = it.value();
                    
                    // Add distance in both directions (symmetric)
                    if (!dbManager->addDistance(collegeName, targetCollegeName, distance) ||
                        !dbManager->addDistance(targetCollegeName, collegeName, distance)) {
                        allDistancesAdded = false;
                        QMessageBox::warning(this, "Add College", 
                                          "Failed to add distance between " + collegeName + " and " + targetCollegeName + ".");
                        break;
                    }
                }
                
                if (allDistancesAdded) {
                    QMessageBox::information(this, "Add College", 
                                          "College '" + collegeName + "' and all distances were added successfully.");
                    
                    // Refresh the colleges table
                    loadColleges();
                    
                    // Emit signal that colleges have changed
                    emit collegesChanged();
                    emit distancesChanged();
                }
            } else {
                QMessageBox::warning(this, "Add College", "Failed to add college '" + collegeName + "'.");
            }
        }
    }
}

void AdminPanel::on_editCollegeButton_clicked()
{
    auto selected = ui->collegesTable->selectedItems();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select a college to edit");
        return;
    }

    int row = selected.first()->row();
    int id = ui->collegesTable->item(row, 0)->text().toInt();
    QString currentName = ui->collegesTable->item(row, 1)->text();
    
    bool ok;
    QString newName = QInputDialog::getText(this, "Edit College",
                                          "College Name:", QLineEdit::Normal,
                                          currentName, &ok);
    if (!ok || newName.isEmpty()) return;

    if (dbManager->updateCollege(id, newName)) {
        QMessageBox::information(this, "Success", "College updated successfully");
        loadColleges();
        updateSouvenirComboBox();
        emit collegesChanged(); // Signal MainWindow to refresh
    } else {
        QMessageBox::warning(this, "Error", "Failed to update college");
    }
}

void AdminPanel::on_deleteCollegeButton_clicked()
{
    auto selected = ui->collegesTable->selectedItems();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select a college to delete");
        return;
    }

    int row = selected.first()->row();
    int id = ui->collegesTable->item(row, 0)->text().toInt();
    QString name = ui->collegesTable->item(row, 1)->text();
    
    if (QMessageBox::question(this, "Confirm Delete",
                            QString("Are you sure you want to delete %1?\nThis will also delete all associated distances and souvenirs.").arg(name))
        == QMessageBox::Yes) {
        if (dbManager->deleteCollege(id)) {
            QMessageBox::information(this, "Success", "College deleted successfully");
            loadColleges();
            loadDistances();
            updateSouvenirComboBox();
            emit collegesChanged(); // Signal MainWindow to refresh
            emit distancesChanged(); // Since distances were also affected
        } else {
            QMessageBox::warning(this, "Error", "Failed to delete college");
        }
    }
}

void AdminPanel::on_addSouvenirButton_clicked()
{
    QString collegeName = ui->souvenirCollegeCombo->currentText();
    if (collegeName == "Select a college") {
        QMessageBox::warning(this, "Error", "Please select a college first");
        return;
    }

    bool ok;
    QString name = QInputDialog::getText(this, "Add Souvenir", 
                                       "Souvenir Name:", QLineEdit::Normal, 
                                       "", &ok);
    if (!ok || name.isEmpty()) return;

    double price = QInputDialog::getDouble(this, "Add Souvenir",
                                         "Price:", 0.00, 0.00, 10000.00, 2, &ok);
    if (!ok) return;

    if (dbManager->addSouvenir(collegeName, name, price)) {
        loadSouvenirs(collegeName);
        emit souvenirsChanged(); // Signal MainWindow to refresh
    } else {
        QMessageBox::warning(this, "Error", "Failed to add souvenir");
    }
}

void AdminPanel::on_deleteSouvenirButton_clicked()
{
    QString collegeName = ui->souvenirCollegeCombo->currentText();
    if (collegeName == "Select a college") {
        QMessageBox::warning(this, "Error", "Please select a college first");
        return;
    }

    QList<QTableWidgetItem*> selectedItems = ui->souvenirsTable->selectedItems();
    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select at least one souvenir to delete");
        return;
    }

    if (QMessageBox::question(this, "Confirm Delete",
                            "Are you sure you want to delete the selected souvenir(s)?")
        == QMessageBox::Yes) {
        QSet<int> rowsToDelete;
        for (QTableWidgetItem* item : selectedItems) {
            rowsToDelete.insert(item->row());
        }

        bool success = true;
        for (int row : rowsToDelete) {
            QString souvenirName = ui->souvenirsTable->item(row, 0)->text();
            if (!dbManager->deleteSouvenir(collegeName, souvenirName)) {
                success = false;
                break;
            }
        }

        if (success) {
            loadSouvenirs(collegeName);
            emit souvenirsChanged(); // Signal MainWindow to refresh
        } else {
            QMessageBox::warning(this, "Error", "Failed to delete some souvenirs");
        }
    }
}

void AdminPanel::on_applySouvenirsButton_clicked()
{
    QString collegeName = ui->souvenirCollegeCombo->currentText();
    if (collegeName == "Select a college") {
        QMessageBox::warning(this, "Error", "Please select a college first");
        return;
    }

    bool success = true;
    for (int row = 0; row < ui->souvenirsTable->rowCount(); row++) {
        QString name = ui->souvenirsTable->item(row, 0)->text();
        double price = ui->souvenirsTable->item(row, 1)->text().toDouble();
        
        if (!dbManager->updateSouvenir(collegeName, name, price)) {
            success = false;
            break;
        }
    }
    
    if (success) {
        QMessageBox::information(this, "Success", "Changes applied successfully");
        loadSouvenirs(collegeName);
        emit souvenirsChanged();  // Signal that souvenirs were updated
        hasUnsavedChanges = false;
    } else {
        QMessageBox::warning(this, "Error", "Failed to apply some changes");
    }
}

void AdminPanel::updateSouvenirComboBox()
{
    qDebug() << "Updating souvenir combo box";
    
    // Store current selection
    QString currentSelection = ui->souvenirCollegeCombo->currentText();
    
    // Block signals while updating
    ui->souvenirCollegeCombo->blockSignals(true);
    
    ui->souvenirCollegeCombo->clear();
    ui->souvenirCollegeCombo->addItem("Select a college");
    
    QVector<Campus> campuses = dbManager->getAllCampuses();
    for (const Campus& campus : campuses) {
        qDebug() << "Adding college to combo box:" << campus.getName();
        ui->souvenirCollegeCombo->addItem(campus.getName());
    }
    
    // Restore previous selection if it exists
    int index = ui->souvenirCollegeCombo->findText(currentSelection);
    if (index != -1) {
        ui->souvenirCollegeCombo->setCurrentIndex(index);
    }
    
    ui->souvenirCollegeCombo->blockSignals(false);
    qDebug() << "Souvenir combo box updated with" << campuses.size() << "colleges";
    
    // Load souvenirs for the selected college
    if (ui->souvenirCollegeCombo->currentText() != "Select a college") {
        loadSouvenirs(ui->souvenirCollegeCombo->currentText());
    }
}

void AdminPanel::revertChanges()
{
    pendingDistanceChanges.clear();
    pendingColleges.clear();
    hasUnsavedChanges = false;
}

void AdminPanel::setupSqlTerminal()
{
    // Create a new tab for SQL terminal
    QWidget* sqlTerminalTab = new QWidget();
    ui->tabWidget->addTab(sqlTerminalTab, "SQL Terminal");
    
    // Create a layout for the tab
    QVBoxLayout* layout = new QVBoxLayout(sqlTerminalTab);
    
    // Add a text edit for displaying results
    QTextEdit* resultDisplay = new QTextEdit();
    resultDisplay->setReadOnly(true);
    resultDisplay->setFont(QFont("Courier", 10));
    layout->addWidget(resultDisplay);
    
    // Add a line edit for entering SQL commands
    QLineEdit* sqlInput = new QLineEdit();
    sqlInput->setPlaceholderText("Enter SQL command...");
    layout->addWidget(sqlInput);
    
    // Add button for executing SQL
    QPushButton* executeButton = new QPushButton("Execute SQL");
    layout->addWidget(executeButton);
    
    // Store references to these widgets for later use
    sqlTerminalDisplay = resultDisplay;
    sqlTerminalInput = sqlInput;
    
    // Connect signals
    connect(executeButton, &QPushButton::clicked, this, &AdminPanel::executeSqlCommand);
    connect(sqlInput, &QLineEdit::returnPressed, this, &AdminPanel::executeSqlCommand);
    
    // Add helper buttons for common operations
    QHBoxLayout* helpersLayout = new QHBoxLayout();
    layout->addLayout(helpersLayout);
    
    QPushButton* resetUsersButton = new QPushButton("Reset Users Table");
    helpersLayout->addWidget(resetUsersButton);
    connect(resetUsersButton, &QPushButton::clicked, this, &AdminPanel::resetUsersTable);
    
    QPushButton* showTablesButton = new QPushButton("Show Tables");
    helpersLayout->addWidget(showTablesButton);
    connect(showTablesButton, &QPushButton::clicked, this, [this]() {
        sqlTerminalInput->setText("SELECT name FROM sqlite_master WHERE type='table';");
        executeSqlCommand();
    });
    
    QPushButton* showUsersButton = new QPushButton("Show Users");
    helpersLayout->addWidget(showUsersButton);
    connect(showUsersButton, &QPushButton::clicked, this, [this]() {
        sqlTerminalInput->setText("SELECT * FROM users;");
        executeSqlCommand();
    });
}

void AdminPanel::executeSqlCommand()
{
    QString sqlCommand = sqlTerminalInput->text().trimmed();
    if (sqlCommand.isEmpty()) {
        return;
    }
    
    sqlTerminalDisplay->append("> " + sqlCommand);
    
    QSqlQuery query(dbManager->getDB());
    if (query.exec(sqlCommand)) {
        QStringList result;
        QSqlRecord record = query.record();
        
        // Get column names
        QStringList headers;
        for (int i = 0; i < record.count(); i++) {
            headers << record.fieldName(i);
        }
        
        if (!headers.isEmpty()) {
            result << headers.join(" | ");
            result << QString("-").repeated(result.first().length());
        }
        
        // Get rows
        while (query.next()) {
            QStringList rowData;
            for (int i = 0; i < record.count(); i++) {
                rowData << query.value(i).toString();
            }
            result << rowData.join(" | ");
        }
        
        if (result.size() > 2) {
            sqlTerminalDisplay->append(result.join("\n"));
            sqlTerminalDisplay->append(QString("\nSuccess: %1 rows returned.").arg(result.size() - 2));
        } else {
            if (sqlCommand.toLower().startsWith("select")) {
                sqlTerminalDisplay->append("Query executed successfully. No rows returned.");
            } else {
                sqlTerminalDisplay->append(QString("Success: %1 rows affected.").arg(query.numRowsAffected()));
            }
        }
    } else {
        sqlTerminalDisplay->append("Error: " + query.lastError().text());
    }
    
    sqlTerminalDisplay->append("\n");
    sqlTerminalInput->clear();
}

void AdminPanel::resetUsersTable()
{
    if (QMessageBox::question(this, "Reset Users Table", 
                           "This will completely rebuild the users table and create a new admin user.\n"
                           "Are you sure you want to continue?", 
                           QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes) {
        return;
    }
    
    // Start a transaction
    dbManager->getDB().transaction();
    
    // Drop the users table completely
    if (!dbManager->executeSQL("DROP TABLE IF EXISTS users")) {
        sqlTerminalDisplay->append("Error: Failed to drop users table.");
        dbManager->getDB().rollback();
        return;
    }
    
    // Create the users table with a clean schema
    if (!dbManager->executeSQL("CREATE TABLE users ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                              "username TEXT UNIQUE NOT NULL,"
                              "password TEXT NOT NULL,"
                              "is_admin INTEGER NOT NULL DEFAULT 0)")) {
        sqlTerminalDisplay->append("Error: Failed to create users table.");
        dbManager->getDB().rollback();
        return;
    }
    
    // Create the admin user with a consistent password hash
    QString passwordHash = QString(QCryptographicHash::hash(
        QString("admin123").toUtf8(), QCryptographicHash::Sha256).toHex());
    
    QSqlQuery query(dbManager->getDB());
    query.prepare("INSERT INTO users (username, password, is_admin) VALUES (?, ?, ?)");
    query.addBindValue("admin");
    query.addBindValue(passwordHash);
    query.addBindValue(1);
    
    if (!query.exec()) {
        sqlTerminalDisplay->append("Error: Failed to create admin user: " + query.lastError().text());
        dbManager->getDB().rollback();
        return;
    }
    
    if (dbManager->getDB().commit()) {
        sqlTerminalDisplay->append("Users table reset successfully. New admin user created (admin/admin123)");
        loadUsers(); // Refresh the users list
    } else {
        sqlTerminalDisplay->append("Failed to commit transaction");
    }
}

void AdminPanel::applyUserChanges()
{
    // You can implement logic here to save any pending changes in the users tab
    // For now, just refresh the users data
    loadUsers();
    QMessageBox::information(this, "Users", "Changes applied successfully");
}

void AdminPanel::onDistanceChanged(QTableWidgetItem* item)
{
    // Only process changes to the distance column (column index 2)
    if (item->column() != 2) return;
    
    int row = item->row();
    QString fromCollege = ui->distancesTable->item(row, 0)->text();
    QString toCollege = ui->distancesTable->item(row, 1)->text();
    
    bool ok;
    double newDistance = item->text().toDouble(&ok);
    
    if (!ok || newDistance < 0) {
        QMessageBox::warning(this, "Invalid Distance", "Please enter a valid positive number.");
        
        // Reset to the original value
        double originalDistance = dbManager->getDistance(fromCollege, toCollege);
        ui->distancesTable->blockSignals(true);
        item->setText(QString::number(originalDistance));
        ui->distancesTable->blockSignals(false);
        return;
    }
    
    // Store the change in the pending changes map
    if (!pendingDistanceChanges.contains(fromCollege)) {
        pendingDistanceChanges[fromCollege] = QMap<QString, double>();
    }
    pendingDistanceChanges[fromCollege][toCollege] = newDistance;
    
    // Also store the reverse direction since distances are bidirectional
    if (!pendingDistanceChanges.contains(toCollege)) {
        pendingDistanceChanges[toCollege] = QMap<QString, double>();
    }
    pendingDistanceChanges[toCollege][fromCollege] = newDistance;
    
    hasUnsavedChanges = true;
}

void AdminPanel::applyDistanceChanges()
{
    if (pendingDistanceChanges.isEmpty()) {
        QMessageBox::information(this, "No Changes", "No changes to apply.");
        return;
    }
    
    bool success = true;
    
    // Start a transaction
    dbManager->getDB().transaction();
    
    // Apply all pending changes
    for (auto it = pendingDistanceChanges.begin(); it != pendingDistanceChanges.end(); ++it) {
        QString fromCollege = it.key();
        QMap<QString, double> toColleges = it.value();
        
        for (auto jt = toColleges.begin(); jt != toColleges.end(); ++jt) {
            QString toCollege = jt.key();
            double newDistance = jt.value();
            
            if (!dbManager->updateDistance(fromCollege, toCollege, newDistance)) {
                success = false;
                qDebug() << "Failed to update distance from" << fromCollege << "to" << toCollege;
                break;
            }
        }
        
        if (!success) break;
    }
    
    if (success) {
        dbManager->getDB().commit();
        QMessageBox::information(this, "Success", "Distance changes applied successfully.");
        pendingDistanceChanges.clear();
        hasUnsavedChanges = false;
        emit distancesChanged(); // Signal that distances were updated
    } else {
        dbManager->getDB().rollback();
        QMessageBox::critical(this, "Error", "Failed to apply some distance changes.");
    }
}

void AdminPanel::cancelDistanceChanges()
{
    if (pendingDistanceChanges.isEmpty()) {
        return;
    }
    
    if (QMessageBox::question(this, "Cancel Changes", 
                            "Are you sure you want to cancel all distance changes?",
                            QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        // Reload distances to discard changes
        disconnect(ui->distancesTable, &QTableWidget::itemChanged, this, &AdminPanel::onDistanceChanged);
        pendingDistanceChanges.clear();
        hasUnsavedChanges = false;
        loadDistances();
    }
}

void AdminPanel::closeDistancesTab()
{
    if (hasUnsavedChanges) {
        int result = QMessageBox::question(this, "Unsaved Changes", 
                                         "You have unsaved distance changes. Do you want to save before closing?", 
                                         QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        
        if (result == QMessageBox::Yes) {
            applyDistanceChanges();
            if (!hasUnsavedChanges) {
                reject(); // Close dialog only if changes were successfully applied
            }
        } else if (result == QMessageBox::No) {
            pendingDistanceChanges.clear();
            hasUnsavedChanges = false;
            reject(); // Close dialog without saving
        }
        // If Cancel, do nothing
    } else {
        reject(); // Close dialog
    }
} 