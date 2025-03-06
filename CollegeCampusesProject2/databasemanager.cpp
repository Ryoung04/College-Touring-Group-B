bool DatabaseManager::initializeDatabase()
{
    // ... existing code ...
    
    // Create users table if it doesn't exist
    QSqlQuery createUsersTable;
    if (!createUsersTable.exec("CREATE TABLE IF NOT EXISTS users ("
                            "username TEXT PRIMARY KEY, "
                            "password TEXT NOT NULL, "
                            "isAdmin INTEGER NOT NULL)")) {
        qDebug() << "Error creating users table:" << createUsersTable.lastError().text();
        return false;
    }
    
    // Check if there are any users, if not add default admin
    QSqlQuery countUsers;
    countUsers.exec("SELECT COUNT(*) FROM users");
    if (countUsers.next() && countUsers.value(0).toInt() == 0) {
        QSqlQuery addDefaultAdmin;
        addDefaultAdmin.prepare("INSERT INTO users (username, password, isAdmin) VALUES (:username, :password, :isAdmin)");
        addDefaultAdmin.bindValue(":username", "admin");
        addDefaultAdmin.bindValue(":password", "admin");
        addDefaultAdmin.bindValue(":isAdmin", 1);
        
        if (!addDefaultAdmin.exec()) {
            qDebug() << "Error adding default admin:" << addDefaultAdmin.lastError().text();
        }
    }
    
    // ... existing code ...
    return true;
} 