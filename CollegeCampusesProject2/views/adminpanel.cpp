#include "adminpanel.h"
#include "ui_adminpanel.h"
#include <QMessageBox>
#include <QInputDialog>
#include "addcollegedialog.h"
#include <QDebug>
#include <QMainWindow>
#include <QComboBox>

AdminPanel::AdminPanel(DBManager* db, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AdminPanel)
    , dbManager(db)
    , hasUnsavedChanges(false)
{
    ui->setupUi(this);
    setWindowTitle("Admin Panel");
    setupTables();

    // Connect tab widget signal to update souvenir combo box
    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &AdminPanel::on_tabWidget_currentChanged);

    // Initialize buttons for the default tab
    on_tabWidget_currentChanged(ui->tabWidget->currentIndex());
}

AdminPanel::~AdminPanel()
{
    delete ui;
}

void AdminPanel::setupTables()
{
    // Setup tables
    ui->collegesTable->setColumnCount(2);
    ui->collegesTable->setHorizontalHeaderLabels({"ID", "Name"});
    ui->collegesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    
    ui->distancesTable->setColumnCount(3);
    ui->distancesTable->setHorizontalHeaderLabels({"From", "To", "Distance"});
    ui->distancesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    
    // Load initial data
    loadColleges();
    loadDistances();
    
    // Setup souvenirs table
    ui->souvenirsTable->setColumnCount(2);
    ui->souvenirsTable->setHorizontalHeaderLabels({"Name", "Price"});
    ui->souvenirsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    
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
    
    // Get both existing and pending colleges
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

void AdminPanel::on_addCollegeButton_clicked()
{
    qDebug() << "Add College clicked";
    
    AddCollegeDialog dialog(dbManager->getAllCampuses(), this);
    if (dialog.exec() == QDialog::Accepted) {
        QString collegeName = dialog.getCollegeName();
        QMap<QString, double> distances = dialog.getDistances();
        
        qDebug() << "Adding college:" << collegeName;
        
        if (dbManager->addCollegeWithDistances(collegeName, distances)) {
            qDebug() << "College added successfully";
            loadColleges();
            loadDistances();
            updateSouvenirComboBox();
            emit collegesChanged(); // Signal MainWindow to refresh
            emit distancesChanged(); // Since distances were also added
            
            // Let the parent window handle the refresh via signals instead
            // of trying to access its internals directly
            qDebug() << "Emitted collegesChanged signal";
        } else {
            qDebug() << "Failed to add college";
            QMessageBox::critical(this, "Error", "Failed to add college");
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
    } else {
        QMessageBox::warning(this, "Error", "Failed to apply some changes");
    }
}

void AdminPanel::on_saveSouvenirsButton_clicked()
{
    on_applySouvenirsButton_clicked(); // Apply changes first
    emit souvenirsChanged();  // Signal that souvenirs were updated
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
    qDebug() << "Save and Exit clicked";
    
    try {
        // Apply any pending changes first
        for (const auto& campus : pendingColleges) {
            qDebug() << "Saving college:" << campus.getName();
            if (!dbManager->addCollege(campus.getName())) {
                qDebug() << "Failed to save college:" << campus.getName();
                // Continue with other colleges even if one fails
            }
        }

        // Clear pending changes
        pendingColleges.clear();
        hasUnsavedChanges = false;

        qDebug() << "Changes saved successfully";
        QMessageBox::information(this, "Success", "Changes saved successfully");
        emit collegesChanged();  // Signal that colleges were updated
        emit distancesChanged();  // College changes affect distances too
        accept(); // Close the dialog with success status
    }
    catch (const std::exception& e) {
        qDebug() << "Error saving changes:" << e.what();
        QMessageBox::critical(this, "Error", "Failed to save some changes. The database may be partially updated.");
        // Don't close the dialog on error
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
}

void AdminPanel::revertChanges()
{
    pendingDistanceChanges.clear();
    pendingColleges.clear();
    hasUnsavedChanges = false;
}

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

void AdminPanel::on_distancesApplyButton_clicked()
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
        loadDistances(); // Refresh admin panel view
        emit distancesChanged(); // Signal MainWindow to refresh
    } else {
        QMessageBox::warning(this, "Error", "Failed to apply some changes");
    }
}

void AdminPanel::on_distancesSaveExitButton_clicked()
{
    on_distancesApplyButton_clicked(); // Apply changes first
    emit distancesChanged();  // Signal that distances were updated
    accept(); // Close dialog
}

void AdminPanel::on_distancesCancelButton_clicked()
{
    if (QMessageBox::question(this, "Confirm Cancel", 
                            "Are you sure you want to discard changes?") 
        == QMessageBox::Yes) {
        reject(); // Close dialog without saving
    }
}

void AdminPanel::reject()
{
    if (hasUnsavedChanges) {
        QMessageBox::StandardButton reply = QMessageBox::question(this, 
            "Unsaved Changes",
            "You have unsaved changes. Are you sure you want to discard them?",
            QMessageBox::Yes | QMessageBox::No);
            
        if (reply == QMessageBox::Yes) {
            revertChanges();
            QDialog::reject();  // Call base class implementation
        }
        // If No, do nothing and stay in dialog
    } else {
        QDialog::reject();  // Call base class implementation
    }
}

void AdminPanel::on_tabWidget_currentChanged(int index)
{
    // Hide all buttons first
    ui->addCollegeButton->setVisible(false);
    ui->editCollegeButton->setVisible(false);
    ui->deleteCollegeButton->setVisible(false);
    ui->addUserButton->setVisible(false);
    ui->editUserButton->setVisible(false);
    ui->deleteUserButton->setVisible(false);
    ui->addSouvenirButton->setVisible(false);
    ui->deleteSouvenirButton->setVisible(false);

    // Show only the relevant buttons based on the selected tab
    switch(index) {
        case 0: // Colleges tab
            ui->addCollegeButton->setVisible(true);
            ui->editCollegeButton->setVisible(true);
            ui->deleteCollegeButton->setVisible(true);
            break;
        case 1: // Distances tab
            // Typically distance editing uses the college buttons or special distance buttons
            // If there are specific distance buttons, show them here
            break;
        case 2: // Souvenirs tab
            ui->addSouvenirButton->setVisible(true);
            ui->deleteSouvenirButton->setVisible(true);
            break;
        case 3: // Users tab
            ui->addUserButton->setVisible(true);
            ui->editUserButton->setVisible(true);
            ui->deleteUserButton->setVisible(true);
            break;
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
                                       "Should this user be an administrator?",
                                       QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes;
    
    if (dbManager->addUser(username, password, isAdmin)) {
        QMessageBox::information(this, "Success", "User added successfully");
        // Refresh users list if you have a table for users
        // loadUsers();
    } else {
        QMessageBox::warning(this, "Error", "Failed to add user. Username may already exist.");
    }
}

void AdminPanel::on_editUserButton_clicked()
{
    // Get users from DB
    QVector<DBManager::UserInfo> users = dbManager->getAllUsers();
    
    if (users.isEmpty()) {
        QMessageBox::information(this, "No Users", "There are no users to edit.");
        return;
    }
    
    // Create a list of usernames for selection
    QStringList usernames;
    for (const auto& user : users) {
        usernames << user.username;
    }
    
    bool ok;
    QString selectedUsername = QInputDialog::getItem(this, "Edit User", 
                                                "Select user to edit:", 
                                                usernames, 0, false, &ok);
    if (!ok || selectedUsername.isEmpty()) return;
    
    // Find the user info
    DBManager::UserInfo selectedUser;
    for (const auto& user : users) {
        if (user.username == selectedUsername) {
            selectedUser = user;
            break;
        }
    }
    
    // Get new username
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
    bool isAdmin = QMessageBox::question(this, "Edit User", 
                                       "Should this user be an administrator?",
                                       QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes;
    
    if (dbManager->updateUser(selectedUser.id, newUsername, newPassword, isAdmin)) {
        QMessageBox::information(this, "Success", "User updated successfully");
        // Refresh users list if you have a table for users
        // loadUsers();
    } else {
        QMessageBox::warning(this, "Error", "Failed to update user.");
    }
}

void AdminPanel::on_deleteUserButton_clicked()
{
    // Get users from DB
    QVector<DBManager::UserInfo> users = dbManager->getAllUsers();
    
    if (users.isEmpty()) {
        QMessageBox::information(this, "No Users", "There are no users to delete.");
        return;
    }
    
    // Create a list of usernames for selection
    QStringList usernames;
    for (const auto& user : users) {
        usernames << user.username;
    }
    
    bool ok;
    QString selectedUsername = QInputDialog::getItem(this, "Delete User", 
                                                  "Select user to delete:", 
                                                  usernames, 0, false, &ok);
    if (!ok || selectedUsername.isEmpty()) return;
    
    // Find the user info
    DBManager::UserInfo selectedUser;
    for (const auto& user : users) {
        if (user.username == selectedUsername) {
            selectedUser = user;
            break;
        }
    }
    
    // Confirm deletion
    if (QMessageBox::question(this, "Confirm Delete", 
                           "Are you sure you want to delete user '" + selectedUsername + "'?",
                           QMessageBox::Yes | QMessageBox::No) == QMessageBox::No) {
        return;
    }
    
    if (dbManager->deleteUser(selectedUser.id)) {
        QMessageBox::information(this, "Success", "User deleted successfully");
        // Refresh users list if you have a table for users
        // loadUsers();
    } else {
        QMessageBox::warning(this, "Error", "Failed to delete user. The user may not exist or an error occurred.");
    }
} 