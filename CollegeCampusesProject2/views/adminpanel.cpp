#include "adminpanel.h"
#include "ui_adminpanel.h"
#include <QMessageBox>
#include <QInputDialog>
#include "addcollegedialog.h"

AdminPanel::AdminPanel(DBManager* db, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AdminPanel)
    , dbManager(db)
    , pendingDistanceChanges()
    , pendingColleges()
    , hasUnsavedChanges(false)
{
    ui->setupUi(this);
    setWindowTitle("Admin Panel");
    setupTables();
    loadColleges();
    loadDistances();
}

AdminPanel::~AdminPanel()
{
    delete ui;
}

void AdminPanel::setupTables()
{
    // Setup colleges table
    ui->collegesTable->setColumnCount(2);
    ui->collegesTable->setHorizontalHeaderLabels({"ID", "Name"});
    ui->collegesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Setup distances table
    ui->distancesTable->setColumnCount(3);
    ui->distancesTable->setHorizontalHeaderLabels({"From", "To", "Distance"});
    ui->distancesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Setup souvenirs table
    ui->souvenirsTable->setColumnCount(2);
    ui->souvenirsTable->setHorizontalHeaderLabels({"Name", "Price"});
    ui->souvenirsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Load colleges into combo box
    updateSouvenirComboBox();

    // Make distances table editable
    ui->distancesTable->setEditTriggers(QTableWidget::DoubleClicked | QTableWidget::EditKeyPressed);
    
    // Only make the distance column editable
    connect(ui->distancesTable, &QTableWidget::itemChanged, this, [this](QTableWidgetItem* item) {
        if (item->column() == 2) { // Distance column
            bool ok;
            double newDistance = item->text().toDouble(&ok);
            if (!ok || newDistance < 0) {
                QMessageBox::warning(this, "Invalid Input", "Please enter a valid positive number");
                loadDistances(); // Reset the table
                return;
            }
        }
    });

    // Make souvenirs table editable
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
        } else {
            // Don't allow editing of Name column
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        }
    });

    // Setup users table
    setupUsersTable();
}

void AdminPanel::setupUsersTable()
{
    ui->usersTable->setColumnCount(3);
    ui->usersTable->setHorizontalHeaderLabels({"ID", "Username", "Admin"});
    ui->usersTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    loadUsers();
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
    // Get both existing and pending colleges
    QVector<Campus> existingCampuses = dbManager->getAllCampuses();
    QVector<Campus> allCampuses = existingCampuses;
    
    // Add pending colleges to the list
    for (const Campus& pendingCampus : pendingColleges) {
        allCampuses.append(pendingCampus);
    }
    
    int numCampuses = allCampuses.size();
    
    // Calculate total number of distances (n * (n-1)) since we show both directions
    int totalRows = numCampuses * (numCampuses - 1);
    ui->distancesTable->setRowCount(totalRows);
    
    int currentRow = 0;
    for (const Campus& from : allCampuses) {
        for (const Campus& to : allCampuses) {
            if (from.getName() != to.getName()) {
                // Create items for the table
                QTableWidgetItem* fromItem = new QTableWidgetItem(from.getName());
                QTableWidgetItem* toItem = new QTableWidgetItem(to.getName());
                
                // Get distance from pending changes or database
                double distance = 0.0;
                QPair<QString, QString> distancePair{from.getName(), to.getName()};
                
                if (pendingDistanceChanges.contains(distancePair)) {
                    distance = pendingDistanceChanges[distancePair];
                } else {
                    distance = dbManager->getDistance(from.getName(), to.getName());
                }
                
                QTableWidgetItem* distanceItem = new QTableWidgetItem(QString::number(distance));
                
                // Make only the distance column editable
                fromItem->setFlags(fromItem->flags() & ~Qt::ItemIsEditable);
                toItem->setFlags(toItem->flags() & ~Qt::ItemIsEditable);
                
                ui->distancesTable->setItem(currentRow, 0, fromItem);
                ui->distancesTable->setItem(currentRow, 1, toItem);
                ui->distancesTable->setItem(currentRow, 2, distanceItem);
                
                currentRow++;
            }
        }
    }
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

void AdminPanel::on_applyButton_clicked()
{
    bool success = true;
    for (int row = 0; row < ui->distancesTable->rowCount(); row++) {
        QString from = ui->distancesTable->item(row, 0)->text();
        QString to = ui->distancesTable->item(row, 1)->text();
        double distance = ui->distancesTable->item(row, 2)->text().toDouble();
        
        if (!dbManager->updateDistance(from, to, distance)) {
            success = false;
            break;
        }
    }
    
    if (success) {
        QMessageBox::information(this, "Success", "Changes applied successfully");
        loadDistances(); // Refresh the view
    } else {
        QMessageBox::warning(this, "Error", "Failed to apply some changes");
    }
}

void AdminPanel::on_saveExitButton_clicked()
{
    on_applyButton_clicked(); // Apply changes first
    accept(); // Close dialog
}

void AdminPanel::on_cancelButton_clicked()
{
    if (QMessageBox::question(this, "Confirm Cancel", 
                            "Are you sure you want to discard changes?") 
        == QMessageBox::Yes) {
        reject(); // Close dialog without saving
    }
}

void AdminPanel::on_addCollegeButton_clicked()
{
    QVector<Campus> existingCampuses = dbManager->getAllCampuses();
    AddCollegeDialog dialog(existingCampuses, this);
    
    if (dialog.exec() == QDialog::Accepted) {
        QString name = dialog.getCollegeName();
        QMap<QString, double> distances = dialog.getDistances();
        
        if (name.isEmpty()) {
            QMessageBox::warning(this, "Error", "Please enter a college name");
            return;
        }
        
        if (distances.size() != existingCampuses.size()) {
            QMessageBox::warning(this, "Error", "Please enter all distances");
            return;
        }
        
        // Store in pending changes
        Campus newCampus;
        newCampus.setId(ui->collegesTable->rowCount() + 1); // Temporary ID
        newCampus.setName(name);
        pendingColleges.append(newCampus);
        
        // Update colleges table
        int row = ui->collegesTable->rowCount();
        ui->collegesTable->insertRow(row);
        ui->collegesTable->setItem(row, 0, new QTableWidgetItem(QString::number(newCampus.getId())));
        ui->collegesTable->setItem(row, 1, new QTableWidgetItem(name));
        
        // Store distances in both directions
        for (auto it = distances.begin(); it != distances.end(); ++it) {
            pendingDistanceChanges[{name, it.key()}] = it.value();
            pendingDistanceChanges[{it.key(), name}] = it.value(); // Store both directions
        }
        
        hasUnsavedChanges = true;
        
        // Update the distances table to show the new distances
        loadDistances();
        
        // Update the souvenir combo box
        updateSouvenirComboBox();
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
        } else {
            QMessageBox::warning(this, "Error", "Failed to delete college");
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
    } else {
        QMessageBox::warning(this, "Error", "Failed to apply some changes");
    }
}

void AdminPanel::on_saveSouvenirsButton_clicked()
{
    on_applySouvenirsButton_clicked(); // Apply changes first
    accept(); // Close dialog
}

void AdminPanel::on_cancelSouvenirsButton_clicked()
{
    if (QMessageBox::question(this, "Confirm Cancel", 
                            "Are you sure you want to discard changes?") 
        == QMessageBox::Yes) {
        reject(); // Close dialog without saving
    }
}

void AdminPanel::on_saveCollegesButton_clicked()
{
    if (hasUnsavedChanges) {
        // First add the colleges
        for (const Campus& campus : pendingColleges) {
            if (!dbManager->addCollege(campus.getName())) {
                QMessageBox::warning(this, "Error", "Failed to add college: " + campus.getName());
                return;
            }
        }
        
        // Then add all the distances
        for (auto it = pendingDistanceChanges.begin(); it != pendingDistanceChanges.end(); ++it) {
            const QString& fromCollege = it.key().first;
            const QString& toCollege = it.key().second;
            double distance = it.value();
            
            if (!dbManager->updateDistance(fromCollege, toCollege, distance)) {
                QMessageBox::warning(this, "Error", 
                    QString("Failed to update distance from %1 to %2").arg(fromCollege, toCollege));
                return;
            }
        }
        
        QMessageBox::information(this, "Success", "Changes saved successfully");
        pendingColleges.clear();
        pendingDistanceChanges.clear();
        hasUnsavedChanges = false;
        
        // Refresh all views
        loadColleges();
        loadDistances();
        updateSouvenirComboBox();
    }
    accept();
}

void AdminPanel::updateSouvenirComboBox()
{
    // Block signals while updating
    ui->souvenirCollegeCombo->blockSignals(true);
    
    QString currentSelection = ui->souvenirCollegeCombo->currentText();
    ui->souvenirCollegeCombo->clear();
    ui->souvenirCollegeCombo->addItem("Select a college");
    
    QVector<Campus> campuses = dbManager->getAllCampuses();
    for (const Campus& campus : campuses) {
        ui->souvenirCollegeCombo->addItem(campus.getName());
    }
    
    int index = ui->souvenirCollegeCombo->findText(currentSelection);
    if (index != -1) {
        ui->souvenirCollegeCombo->setCurrentIndex(index);
    } else {
        ui->souvenirCollegeCombo->setCurrentIndex(0);
    }
    
    ui->souvenirCollegeCombo->blockSignals(false);
}

void AdminPanel::loadUsers()
{
    auto users = dbManager->getAllUsers();
    ui->usersTable->setRowCount(users.size());
    
    for (int i = 0; i < users.size(); ++i) {
        QTableWidgetItem* idItem = new QTableWidgetItem(QString::number(users[i].id));
        idItem->setFlags(idItem->flags() & ~Qt::ItemIsEditable);
        
        QTableWidgetItem* usernameItem = new QTableWidgetItem(users[i].username);
        usernameItem->setFlags(usernameItem->flags() & ~Qt::ItemIsEditable);
        
        QTableWidgetItem* adminItem = new QTableWidgetItem("");
        adminItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        adminItem->setCheckState(users[i].isAdmin ? Qt::Checked : Qt::Unchecked);
        
        if (dbManager->isOriginalAdmin(users[i].id)) {
            adminItem->setFlags(adminItem->flags() & ~Qt::ItemIsEnabled);
        }
        
        ui->usersTable->setItem(i, 0, idItem);
        ui->usersTable->setItem(i, 1, usernameItem);
        ui->usersTable->setItem(i, 2, adminItem);
    }
}

void AdminPanel::on_addUserButton_clicked()
{
    bool ok;
    QString username = QInputDialog::getText(this, "Add User",
                                          "Username:", QLineEdit::Normal,
                                          "", &ok);
    if (!ok || username.isEmpty()) return;
    
    QString password = QInputDialog::getText(this, "Add User",
                                          "Password:", QLineEdit::Password,
                                          "", &ok);
    if (!ok || password.isEmpty()) return;
    
    bool isAdmin = QMessageBox::question(this, "Add User",
                                       "Should this user be an admin?",
                                       QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes;
    
    if (dbManager->addUser(username, password, isAdmin)) {
        QMessageBox::information(this, "Success", "User added successfully");
        loadUsers();
    } else {
        QMessageBox::warning(this, "Error", "Failed to add user");
    }
}

void AdminPanel::on_editUserButton_clicked()
{
    auto selected = ui->usersTable->selectedItems();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select a user to edit");
        return;
    }
    
    int row = selected.first()->row();
    int id = ui->usersTable->item(row, 0)->text().toInt();
    QString currentUsername = ui->usersTable->item(row, 1)->text();
    bool currentIsAdmin = ui->usersTable->item(row, 2)->checkState() == Qt::Checked;
    
    bool ok;
    QString newUsername = QInputDialog::getText(this, "Edit User",
                                             "Username:", QLineEdit::Normal,
                                             currentUsername, &ok);
    if (!ok) return;
    
    QString password;
    if (QMessageBox::question(this, "Edit User",
                            "Do you want to change the password?",
                            QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        password = QInputDialog::getText(this, "Edit User",
                                      "New Password:", QLineEdit::Password,
                                      "", &ok);
        if (!ok) return;
    }
    
    bool isAdmin = currentIsAdmin;
    if (!dbManager->isOriginalAdmin(id)) {
        isAdmin = QMessageBox::question(this, "Edit User",
                                      "Should this user be an admin?",
                                      QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes;
    }
    
    if (dbManager->updateUser(id, newUsername, password, isAdmin)) {
        QMessageBox::information(this, "Success", "User updated successfully");
        loadUsers();
    } else {
        QMessageBox::warning(this, "Error", "Failed to update user");
    }
}

void AdminPanel::on_deleteUserButton_clicked()
{
    auto selected = ui->usersTable->selectedItems();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select a user to delete");
        return;
    }
    
    int row = selected.first()->row();
    int id = ui->usersTable->item(row, 0)->text().toInt();
    QString username = ui->usersTable->item(row, 1)->text();
    
    if (dbManager->isOriginalAdmin(id)) {
        QMessageBox::warning(this, "Error", "Cannot delete the original admin user");
        return;
    }
    
    if (QMessageBox::question(this, "Confirm Delete",
                            QString("Are you sure you want to delete user '%1'?").arg(username),
                            QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        if (dbManager->deleteUser(id)) {
            QMessageBox::information(this, "Success", "User deleted successfully");
            loadUsers();
        } else {
            QMessageBox::warning(this, "Error", "Failed to delete user");
        }
    }
}

void AdminPanel::on_usersTable_itemChanged(QTableWidgetItem* item)
{
    if (item->column() == 2) { // Admin checkbox column
        int row = item->row();
        int id = ui->usersTable->item(row, 0)->text().toInt();
        QString username = ui->usersTable->item(row, 1)->text();
        bool isAdmin = item->checkState() == Qt::Checked;
        
        if (dbManager->updateUser(id, username, "", isAdmin)) {
            // Success
        } else {
            // Failed to update, reload to reset state
            loadUsers();
        }
    }
}

void AdminPanel::revertChanges()
{
    // Clear all pending changes
    pendingColleges.clear();
    pendingDistanceChanges.clear();
    hasUnsavedChanges = false;
    
    // Reload data from database
    loadColleges();
    loadDistances();
    updateSouvenirComboBox();
}

void AdminPanel::reject() // Called when Cancel or X button is clicked
{
    if (hasUnsavedChanges) {
        QMessageBox::StandardButton reply = QMessageBox::question(this, 
            "Unsaved Changes",
            "You have unsaved changes. Are you sure you want to discard them?",
            QMessageBox::Yes | QMessageBox::No);
            
        if (reply == QMessageBox::Yes) {
            revertChanges();
            QDialog::reject();
        }
        // If No, stay on the panel
    } else {
        QDialog::reject();
    }
}

// Update the close event handler
void AdminPanel::closeEvent(QCloseEvent* event)
{
    if (hasUnsavedChanges) {
        QMessageBox::StandardButton reply = QMessageBox::question(this, 
            "Unsaved Changes",
            "You have unsaved changes. Are you sure you want to discard them?",
            QMessageBox::Yes | QMessageBox::No);
            
        if (reply == QMessageBox::Yes) {
            revertChanges();
            event->accept();
        } else {
            event->ignore();
        }
    } else {
        event->accept();
    }
} 