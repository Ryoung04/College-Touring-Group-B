#include "dbmanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "csvhandler.h"
#include <QUuid>
#include <QCryptographicHash>

DBManager::DBManager(QObject *parent) : QObject(parent)
{
    // First check available drivers
    qDebug() << "Available SQL drivers:" << QSqlDatabase::drivers();
}

bool DBManager::connectToDatabase(const QString& path)
{
    // Store the path for reconnection if needed
    dbPath = path;

    // Remove any existing connection
    if (QSqlDatabase::contains("CAMPUS_CONNECTION")) {
        QSqlDatabase::removeDatabase("CAMPUS_CONNECTION");
    }

    // Create a new connection
    db = QSqlDatabase::addDatabase("QSQLITE", "CAMPUS_CONNECTION");
    db.setDatabaseName(path);

    if (!db.open()) {
        qDebug() << "Failed to open database at:" << path;
        qDebug() << "Error:" << db.lastError().text();
        return false;
    }

    // Initialize database with tables
    QSqlQuery query(db);
    
    // Enable foreign keys
    query.exec("PRAGMA foreign_keys = ON");

    // Create all tables including users table
    if (!createTables()) {
        qDebug() << "Failed to create database tables";
        return false;
    }

    qDebug() << "Database initialized successfully at:" << path;
    return true;
}

DBManager::~DBManager()
{
    if (db.isOpen())
        db.close();
}

bool DBManager::isOpen() const
{
    return db.isOpen();
}

bool DBManager::createTables()
{
    QSqlQuery query(db);
    
    // Create colleges table
    if (!query.exec(
        "CREATE TABLE IF NOT EXISTS colleges ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    name TEXT UNIQUE NOT NULL"
        ")"
    )) {
        qDebug() << "Failed to create colleges table:" << query.lastError().text();
        return false;
    }
    
    // Create distances table
    if (!query.exec(
        "CREATE TABLE IF NOT EXISTS distances ("
        "    from_college_id INTEGER,"
        "    to_college_id INTEGER,"
        "    distance REAL NOT NULL,"
        "    FOREIGN KEY (from_college_id) REFERENCES colleges(id),"
        "    FOREIGN KEY (to_college_id) REFERENCES colleges(id),"
        "    PRIMARY KEY (from_college_id, to_college_id)"
        ")"
    )) {
        qDebug() << "Failed to create distances table:" << query.lastError().text();
        return false;
    }
    
    // Create souvenirs table
    if (!query.exec(
        "CREATE TABLE IF NOT EXISTS souvenirs ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    college_id INTEGER,"
        "    name TEXT NOT NULL,"
        "    price REAL NOT NULL,"
        "    FOREIGN KEY (college_id) REFERENCES colleges(id),"
        "    UNIQUE(college_id, name)"
        ")"
    )) {
        qDebug() << "Failed to create souvenirs table:" << query.lastError().text();
        return false;
    }

    // Create users table
    if (!query.exec(
        "CREATE TABLE IF NOT EXISTS users ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    username TEXT UNIQUE NOT NULL,"
        "    password TEXT NOT NULL,"
        "    is_admin INTEGER NOT NULL DEFAULT 0"
        ")"
    )) {
        qDebug() << "Failed to create users table:" << query.lastError().text();
        return false;
    }

    // Create initial admin user if users table is empty
    query.exec("SELECT COUNT(*) FROM users");
    if (query.next() && query.value(0).toInt() == 0) {
        // Use question mark placeholders for consistency
        query.prepare("INSERT INTO users (username, password, is_admin) VALUES (?, ?, ?)");
        
        // Hash the password
        QString passwordHash = QString(QCryptographicHash::hash(
            QString("admin123").toUtf8(), QCryptographicHash::Sha256).toHex());
        
        query.addBindValue("admin");
        query.addBindValue(passwordHash);
        query.addBindValue(1);
        
        if (!query.exec()) {
            qDebug() << "Failed to create admin user:" << query.lastError().text();
            return false;
        }
        
        qDebug() << "Created default admin user: admin/admin123";
    }

    qDebug() << "All tables created successfully";
    return true;
}

bool DBManager::importCollegesFromCSV(const QString& csvPath)
{
    QFile file(csvPath);
    if (!file.open(QIODevice::ReadOnly | QFileDevice::Text)) {
        qDebug() << "Failed to open CSV file:" << csvPath;
        return false;
    }

    db.transaction();

    // Prepare statements once
    QSqlQuery insertCollege(db);
    insertCollege.prepare("INSERT OR IGNORE INTO colleges (name) VALUES (?)");
    
    QSqlQuery insertDistance(db);
    insertDistance.prepare(
        "INSERT OR REPLACE INTO distances (from_college_id, to_college_id, distance) "
        "SELECT c1.id, c2.id, :distance "
        "FROM colleges c1, colleges c2 "
        "WHERE c1.name = :from AND c2.name = :to"
    );

    QTextStream in(&file);
    in.readLine(); // Skip header

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;
        
        // Split by comma but respect quotes
        QStringList fields;
        QString current;
        bool inQuotes = false;
        
        for (QChar c : line) {
            if (c == '"') {
                inQuotes = !inQuotes;
            } else if (c == ',' && !inQuotes) {
                fields.append(current.trimmed());
                current.clear();
            } else {
                current.append(c);
            }
        }
        fields.append(current.trimmed());

        if (fields.size() < 3) {
            qDebug() << "Invalid line format:" << line;
            continue;
        }

        // Remove any remaining quotes from college names
        QString from = fields[0].remove('"').trimmed();
        QString to = fields[1].remove('"').trimmed();
        
        bool ok;
        double distance = fields[2].toDouble(&ok);
        if (!ok || distance <= 0) {
            qDebug() << "Invalid distance value:" << fields[2];
            continue;
        }

        // Debug output
        qDebug() << "Importing distance:" << from << "->" << to << "=" << distance;

        // Insert colleges
        insertCollege.addBindValue(from);
        if (!insertCollege.exec()) {
            qDebug() << "Error inserting college" << from << ":" << insertCollege.lastError().text();
        }
        
        insertCollege.addBindValue(to);
        if (!insertCollege.exec()) {
            qDebug() << "Error inserting college" << to << ":" << insertCollege.lastError().text();
        }

        // Insert distance
        insertDistance.bindValue(":distance", distance);
        insertDistance.bindValue(":from", from);
        insertDistance.bindValue(":to", to);
        if (!insertDistance.exec()) {
            qDebug() << "Error inserting distance:" << insertDistance.lastError().text();
        }
    }

    bool success = db.commit();
    file.close();
    return success;
}

bool DBManager::importSouvenirsFromCSV(const QString& csvPath)
{
    QFile file(csvPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open souvenirs CSV file:" << csvPath;
        return false;
    }

    // Debug: Print entire file contents
    qDebug() << "\nReading souvenirs file:" << csvPath;
    qDebug() << "File contents:";
    QTextStream debugStream(&file);
    while (!debugStream.atEnd()) {
        qDebug() << debugStream.readLine();
    }
    file.seek(0); // Reset file position

    QTextStream in(&file);
    db.transaction();

    // Clear existing souvenirs first
    QSqlQuery clearQuery(db);
    if (!clearQuery.exec("DELETE FROM souvenirs")) {
        qDebug() << "Failed to clear existing souvenirs:" << clearQuery.lastError().text();
        db.rollback();
        return false;
    }

    // Skip header line
    if (!in.atEnd()) {
        QString header = in.readLine();
        qDebug() << "Header line:" << header;
    }

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");
        
        if (fields.size() >= 3) {
            // Remove any quotes and trim whitespace
            QString collegeName = fields[0].remove('"').trimmed();
            QString souvenirName = fields[1].remove('"').trimmed();
            double price = fields[2].remove('"').trimmed().toDouble();

            // Special case for University of Michigan
            if (collegeName == "University of Michigan") {
                collegeName = "University of  Michigan";  // Use double space version
            }

            qDebug() << "\nProcessing line:";
            qDebug() << "  College:" << collegeName;
            qDebug() << "  Souvenir:" << souvenirName;
            qDebug() << "  Price:" << price;

            // Get college ID
            QSqlQuery query(db);
            query.prepare("SELECT id FROM colleges WHERE name = ?");
            query.addBindValue(collegeName);
            
            if (!query.exec()) {
                qDebug() << "Failed to query college:" << query.lastError().text();
                db.rollback();
                return false;
            }
            
            if (!query.next()) {
                qDebug() << "WARNING: College not found in database:" << collegeName;
                qDebug() << "Available colleges:";
                QSqlQuery collegesQuery(db);
                collegesQuery.exec("SELECT name FROM colleges ORDER BY name");
                while (collegesQuery.next()) {
                    qDebug() << "  -" << collegesQuery.value(0).toString();
                }
                continue;
            }
            
            int collegeId = query.value(0).toInt();
            qDebug() << "Found college ID:" << collegeId << "for" << collegeName;
            
            // Insert souvenir
            query.prepare("INSERT INTO souvenirs (college_id, name, price) VALUES (?, ?, ?)");
            query.addBindValue(collegeId);
            query.addBindValue(souvenirName);
            query.addBindValue(price);
            
            if (!query.exec()) {
                qDebug() << "Failed to insert souvenir:" << souvenirName;
                qDebug() << "Error:" << query.lastError().text();
                db.rollback();
                return false;
            }
            
            qDebug() << "Successfully imported souvenir:" << souvenirName << "for" << collegeName;
        } else {
            qDebug() << "Invalid line format:" << line;
        }
    }

    bool success = db.commit();
    qDebug() << "Souvenir import" << (success ? "successful" : "failed");
    return success;
}

bool DBManager::ensureConnection() const
{
    if (!db.isOpen()) {
        qDebug() << "Attempting to reopen database connection";
        const_cast<QSqlDatabase&>(db).open();
    }
    return db.isOpen();
}

QVector<Campus> DBManager::getAllCampuses() const
{
    QVector<Campus> campuses;
    if (!ensureConnection()) {
        qDebug() << "Failed to ensure database connection";
        return campuses;
    }

    QSqlQuery query(db);
    
    if (!query.exec("SELECT id, name FROM colleges ORDER BY name")) {
        qDebug() << "Error fetching campuses:" << query.lastError().text();
        return campuses;
    }
    
    while (query.next()) {
        Campus campus;
        campus.setId(query.value(0).toInt());
        campus.setName(query.value(1).toString());
        campuses.append(campus);
    }
    
    qDebug() << "Loaded" << campuses.size() << "campuses from database";
    return campuses;
}

double DBManager::getDistance(const QString& fromCollege, const QString& toCollege) const
{
    if (!isOpen()) return -1;

    // First get the college IDs from their names
    QSqlQuery queryFrom(db);
    queryFrom.prepare("SELECT id FROM colleges WHERE name = ?");
    queryFrom.addBindValue(fromCollege);
    
    if (!queryFrom.exec() || !queryFrom.next()) {
        qDebug() << "Cannot find 'from' college when getting distance:" << fromCollege;
        return -1;
    }
    
    int fromCollegeId = queryFrom.value(0).toInt();
    
    QSqlQuery queryTo(db);
    queryTo.prepare("SELECT id FROM colleges WHERE name = ?");
    queryTo.addBindValue(toCollege);
    
    if (!queryTo.exec() || !queryTo.next()) {
        qDebug() << "Cannot find 'to' college when getting distance:" << toCollege;
        return -1;
    }
    
    int toCollegeId = queryTo.value(0).toInt();
    
    // Now query the distance using the IDs
    QSqlQuery distanceQuery(db);
    distanceQuery.prepare("SELECT distance FROM distances WHERE from_college_id = ? AND to_college_id = ?");
    distanceQuery.addBindValue(fromCollegeId);
    distanceQuery.addBindValue(toCollegeId);
    
    if (!distanceQuery.exec()) {
        qDebug() << "Error querying distance:" << distanceQuery.lastError().text();
        return -1;
    }
    
    if (distanceQuery.next() && !distanceQuery.value(0).isNull()) {
        return distanceQuery.value(0).toDouble();
    }
    
    // Try the reverse direction
    distanceQuery.prepare("SELECT distance FROM distances WHERE from_college_id = ? AND to_college_id = ?");
    distanceQuery.addBindValue(toCollegeId);
    distanceQuery.addBindValue(fromCollegeId);
    
    if (!distanceQuery.exec()) {
        qDebug() << "Error querying reverse distance:" << distanceQuery.lastError().text();
        return -1;
    }
    
    if (distanceQuery.next() && !distanceQuery.value(0).isNull()) {
        return distanceQuery.value(0).toDouble();
    }
    
    // No distance found in either direction
    return -1;
}

QVector<QPair<QString, double>> DBManager::getSouvenirs(const QString& collegeName) const
{
    QVector<QPair<QString, double>> souvenirs;
    QSqlQuery query(db);
    
    query.prepare(
        "SELECT s.name, s.price "
        "FROM souvenirs s "
        "JOIN colleges c ON s.college_id = c.id "
        "WHERE c.name = ?"
    );
    query.addBindValue(collegeName);
    
    if (!query.exec()) {
        qDebug() << "Error fetching souvenirs:" << query.lastError().text();
        return souvenirs;
    }
    
    while (query.next()) {
        QString name = query.value(0).toString();
        double price = query.value(1).toDouble();
        souvenirs.append({name, price});
        qDebug() << "Found souvenir:" << name << "for" << price;
    }
    
    qDebug() << "Total souvenirs found for" << collegeName << ":" << souvenirs.size();
    return souvenirs;
}

bool DBManager::addSouvenir(const QString& collegeName, const QString& name, double price)
{
    QSqlQuery query(db);
    
    // First get the college ID
    query.prepare("SELECT id FROM colleges WHERE name = ?");
    query.addBindValue(collegeName);
    
    if (!query.exec() || !query.next()) {
        qDebug() << "Error finding college:" << query.lastError().text();
        return false;
    }
    
    int collegeId = query.value(0).toInt();
    
    // Insert the new souvenir
    query.prepare("INSERT INTO souvenirs (college_id, name, price) VALUES (?, ?, ?)");
    query.addBindValue(collegeId);
    query.addBindValue(name);
    query.addBindValue(price);
    
    if (!query.exec()) {
        qDebug() << "Error adding souvenir:" << query.lastError().text();
        return false;
    }
    
    return true;
}

bool DBManager::updateSouvenir(const QString& collegeName, const QString& name, double price)
{
    QSqlQuery query(db);
    
    // Update the souvenir price
    query.prepare(
        "UPDATE souvenirs SET price = ? "
        "WHERE name = ? AND college_id = ("
        "    SELECT id FROM colleges WHERE name = ?"
        ")"
    );
    
    query.addBindValue(price);
    query.addBindValue(name);
    query.addBindValue(collegeName);
    
    if (!query.exec()) {
        qDebug() << "Error updating souvenir:" << query.lastError().text();
        return false;
    }
    
    return query.numRowsAffected() > 0;
}

bool DBManager::deleteSouvenir(const QString& collegeName, const QString& name)
{
    QSqlQuery query(db);
    
    // Delete the souvenir
    query.prepare(
        "DELETE FROM souvenirs "
        "WHERE name = ? AND college_id = ("
        "    SELECT id FROM colleges WHERE name = ?"
        ")"
    );
    
    query.addBindValue(name);
    query.addBindValue(collegeName);
    
    if (!query.exec()) {
        qDebug() << "Error deleting souvenir:" << query.lastError().text();
        return false;
    }
    
    return query.numRowsAffected() > 0;
}

bool DBManager::updateDistance(const QString& fromCollege, const QString& toCollege, double distance)
{
    if (!isOpen()) return false;
    
    // First get the college IDs from the names
    QSqlQuery queryFrom(db);
    queryFrom.prepare("SELECT id FROM colleges WHERE name = ?");
    queryFrom.addBindValue(fromCollege);
    
    if (!queryFrom.exec() || !queryFrom.next()) {
        qDebug() << "Cannot find college:" << fromCollege;
        qDebug() << "SQL error:" << queryFrom.lastError().text();
        return false;
    }
    int fromCollegeId = queryFrom.value(0).toInt();
    
    QSqlQuery queryTo(db);
    queryTo.prepare("SELECT id FROM colleges WHERE name = ?");
    queryTo.addBindValue(toCollege);
    
    if (!queryTo.exec() || !queryTo.next()) {
        qDebug() << "Cannot find college:" << toCollege;
        qDebug() << "SQL error:" << queryTo.lastError().text();
        return false;
    }
    int toCollegeId = queryTo.value(0).toInt();
    
    // Now update the distance with the college IDs
    QSqlQuery updateQuery(db);
    updateQuery.prepare("UPDATE distances SET distance = ? WHERE from_college_id = ? AND to_college_id = ?");
    updateQuery.addBindValue(distance);
    updateQuery.addBindValue(fromCollegeId);
    updateQuery.addBindValue(toCollegeId);
    
    bool success = updateQuery.exec();
    if (!success || updateQuery.numRowsAffected() == 0) {
        // The distance might not exist yet, so try to insert it
        qDebug() << "Update failed or no rows affected. Trying to insert distance.";
        qDebug() << "SQL error:" << updateQuery.lastError().text();
        
        QSqlQuery insertQuery(db);
        insertQuery.prepare("INSERT INTO distances (from_college_id, to_college_id, distance) VALUES (?, ?, ?)");
        insertQuery.addBindValue(fromCollegeId);
        insertQuery.addBindValue(toCollegeId);
        insertQuery.addBindValue(distance);
        
        success = insertQuery.exec();
        if (!success) {
            qDebug() << "Failed to insert distance:" << insertQuery.lastError().text();
            return false;
        }
    }
    
    // Also update the reverse direction for symmetry
    QSqlQuery reverseQuery(db);
    reverseQuery.prepare("UPDATE distances SET distance = ? WHERE from_college_id = ? AND to_college_id = ?");
    reverseQuery.addBindValue(distance);
    reverseQuery.addBindValue(toCollegeId);  // Swapped IDs for reverse direction
    reverseQuery.addBindValue(fromCollegeId); // Swapped IDs for reverse direction
    
    bool reverseSuccess = reverseQuery.exec();
    if (!reverseSuccess || reverseQuery.numRowsAffected() == 0) {
        // The reverse distance might not exist yet, so try to insert it
        qDebug() << "Update of reverse direction failed. Trying to insert.";
        qDebug() << "SQL error:" << reverseQuery.lastError().text();
        
        QSqlQuery reverseInsertQuery(db);
        reverseInsertQuery.prepare("INSERT INTO distances (from_college_id, to_college_id, distance) VALUES (?, ?, ?)");
        reverseInsertQuery.addBindValue(toCollegeId);
        reverseInsertQuery.addBindValue(fromCollegeId);
        reverseInsertQuery.addBindValue(distance);
        
        reverseSuccess = reverseInsertQuery.exec();
        if (!reverseSuccess) {
            qDebug() << "Failed to insert reverse distance:" << reverseInsertQuery.lastError().text();
            // We'll still return true if at least the forward direction was updated
        }
    }
    
    return success;
}

bool DBManager::addCollege(const QString& name)
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO colleges (name) VALUES (?)");
    query.addBindValue(name);
    
    return query.exec();
}

bool DBManager::updateCollege(int id, const QString& newName)
{
    QSqlQuery query(db);
    query.prepare("UPDATE colleges SET name = ? WHERE id = ?");
    query.addBindValue(newName);
    query.addBindValue(id);
    
    return query.exec();
}

bool DBManager::deleteCollege(int id)
{
    QSqlQuery query(db);
    
    // Start a transaction since we need to delete from multiple tables
    db.transaction();
    
    // Delete distances first (due to foreign key constraints)
    query.prepare("DELETE FROM distances WHERE from_college_id = ? OR to_college_id = ?");
    query.addBindValue(id);
    query.addBindValue(id);
    if (!query.exec()) {
        db.rollback();
        return false;
    }
    
    // Delete souvenirs
    query.prepare("DELETE FROM souvenirs WHERE college_id = ?");
    query.addBindValue(id);
    if (!query.exec()) {
        db.rollback();
        return false;
    }
    
    // Finally delete the college
    query.prepare("DELETE FROM colleges WHERE id = ?");
    query.addBindValue(id);
    if (!query.exec()) {
        db.rollback();
        return false;
    }
    
    return db.commit();
}

bool DBManager::addCollegeWithDistances(const QString& name, const QMap<QString, double>& distances)
{
    QSqlDatabase::database().transaction();
    
    try {
        // First add the college
        QSqlQuery query(db);
        query.prepare("INSERT INTO colleges (name) VALUES (?)");
        query.addBindValue(name);
        
        if (!query.exec()) {
            qDebug() << "Failed to add college:" << query.lastError().text();
            QSqlDatabase::database().rollback();
            return false;
        }
        
        int newCollegeId = query.lastInsertId().toInt();
        
        // Add distances
        for (auto it = distances.begin(); it != distances.end(); ++it) {
            // Get the target college ID
            query.prepare("SELECT id FROM colleges WHERE name = ?");
            query.addBindValue(it.key());
            if (!query.exec() || !query.next()) {
                qDebug() << "Failed to get target college ID:" << query.lastError().text();
                QSqlDatabase::database().rollback();
                return false;
            }
            int targetId = query.value(0).toInt();
            
            // Add distance in both directions
            query.prepare("INSERT INTO distances (from_college_id, to_college_id, distance) VALUES (?, ?, ?)");
            query.addBindValue(newCollegeId);
            query.addBindValue(targetId);
            query.addBindValue(it.value());
            if (!query.exec()) {
                qDebug() << "Failed to add distance:" << query.lastError().text();
                QSqlDatabase::database().rollback();
                return false;
            }
            
            // Add reverse direction
            query.prepare("INSERT INTO distances (from_college_id, to_college_id, distance) VALUES (?, ?, ?)");
            query.addBindValue(targetId);
            query.addBindValue(newCollegeId);
            query.addBindValue(it.value());
            if (!query.exec()) {
                qDebug() << "Failed to add reverse distance:" << query.lastError().text();
                QSqlDatabase::database().rollback();
                return false;
            }
        }
        
        QSqlDatabase::database().commit();
        return true;
        
    } catch (const std::exception& e) {
        qDebug() << "Error in addCollegeWithDistances:" << e.what();
        QSqlDatabase::database().rollback();
        return false;
    }
}

void DBManager::reloadDatabase()
{
    // Close existing connection if open
    if (db.isOpen()) {
        db.close();
    }

    // Remove the old connection if it exists
    QString connectionName = db.connectionName();
    db = QSqlDatabase(); // destroy old connection
    if (QSqlDatabase::contains(connectionName)) {
        QSqlDatabase::removeDatabase(connectionName);
    }

    // Create a new connection with a unique name
    static int connectionCounter = 0;
    QString newConnectionName = QString("CAMPUS_CONNECTION_%1").arg(++connectionCounter);
    db = QSqlDatabase::addDatabase("QSQLITE", newConnectionName);
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        qDebug() << "Failed to reload database at:" << dbPath;
        qDebug() << "Error:" << db.lastError().text();
        return;
    }

    // Enable foreign keys
    QSqlQuery query(db);
    query.exec("PRAGMA foreign_keys = ON");
}

void DBManager::debugPrintSouvenirs() const
{
    QSqlQuery query(db);
    if (!query.exec("SELECT c.name, s.name, s.price FROM colleges c "
                   "LEFT JOIN souvenirs s ON c.id = s.college_id "
                   "ORDER BY c.name, s.name")) {
        qDebug() << "Error querying souvenirs:" << query.lastError().text();
        return;
    }

    QString currentCollege;
    int souvenirCount = 0;
    
    while (query.next()) {
        QString collegeName = query.value(0).toString();
        QString souvenirName = query.value(1).toString();
        double price = query.value(2).toDouble();
        
        if (collegeName != currentCollege) {
            if (!currentCollege.isEmpty()) {
                qDebug() << "Total souvenirs for" << currentCollege << ":" << souvenirCount;
            }
            currentCollege = collegeName;
            souvenirCount = 0;
            qDebug() << "\nCollege:" << collegeName;
        }
        
        if (!souvenirName.isEmpty()) {
            qDebug() << "  -" << souvenirName << "($" << price << ")";
            souvenirCount++;
        }
    }
    
    if (!currentCollege.isEmpty()) {
        qDebug() << "Total souvenirs for" << currentCollege << ":" << souvenirCount;
    }
}

QVector<DBManager::UserInfo> DBManager::getAllUsers() const
{
    qDebug() << "Getting all users";
    
    QVector<UserInfo> users;
    
    QSqlQuery query(db);
    query.exec("SELECT id, username, password, is_admin FROM users");
    
    while (query.next()) {
        UserInfo user;
        user.id = query.value(0).toString();  // Ensure ID is handled as a string
        user.username = query.value(1).toString();
        user.password = query.value(2).toString();
        user.isAdmin = query.value(3).toBool();
        
        users.append(user);
    }
    
    qDebug() << "Found" << users.size() << "users";
    
    return users;
}

bool DBManager::addUser(const QString& username, const QString& password, bool isAdmin)
{
    qDebug() << "DBManager::addUser - Adding user:" << username << "isAdmin:" << isAdmin;
    
    try {
        // Hash the password
        QString passwordHash = QString(QCryptographicHash::hash(
            password.toUtf8(), QCryptographicHash::Sha256).toHex());
        qDebug() << "Password hashed, length:" << passwordHash.length();
        
        QSqlQuery query(db);
        query.prepare("INSERT INTO users (username, password, is_admin) VALUES (?, ?, ?)");
        query.addBindValue(username);
        query.addBindValue(passwordHash);
        query.addBindValue(isAdmin ? 1 : 0);
        
        qDebug() << "Executing SQL query to add user...";
        bool success = query.exec();
        
        if (!success) {
            qDebug() << "Failed to add user. SQL error:" << query.lastError().text();
        } else {
            qDebug() << "User added successfully to database";
        }
        
        return success;
    }
    catch (const std::exception& e) {
        qDebug() << "Exception in addUser:" << e.what();
        return false;
    }
}

bool DBManager::updateUser(const QString& userId, const QString& newUsername, const QString& newPassword, bool isAdmin)
{
    qDebug() << "Updating user ID:" << userId;
    
    QSqlQuery query(db);
    
    // If a new password is provided, update it too
    if (!newPassword.isEmpty()) {
        // Hash the new password
        QByteArray passwordHash = QCryptographicHash::hash(newPassword.toUtf8(), QCryptographicHash::Sha256).toHex();
        
        query.prepare("UPDATE users SET username = :username, password = :password, is_admin = :is_admin WHERE id = :id");
        query.bindValue(":username", newUsername);
        query.bindValue(":password", QString(passwordHash));
        query.bindValue(":is_admin", isAdmin ? 1 : 0);
        query.bindValue(":id", userId);
    } else {
        // Don't update the password
        query.prepare("UPDATE users SET username = :username, is_admin = :is_admin WHERE id = :id");
        query.bindValue(":username", newUsername);
        query.bindValue(":is_admin", isAdmin ? 1 : 0);
        query.bindValue(":id", userId);
    }
    
    bool success = query.exec();
    if (!success) {
        qDebug() << "Failed to update user:" << query.lastError().text();
    } else {
        qDebug() << "User updated successfully";
    }
    
    return success;
}

bool DBManager::deleteUser(const QString& userId)
{
    qDebug() << "Deleting user ID:" << userId;
    
    QSqlQuery query(db);
    query.prepare("DELETE FROM users WHERE id = ?");
    query.addBindValue(userId);
    
    bool success = query.exec();
    if (!success) {
        qDebug() << "Failed to delete user:" << query.lastError().text();
    } else {
        qDebug() << "User deleted successfully";
    }
    
    return success;
}

bool DBManager::isOriginalAdmin(const QString& id) const
{
    // Check if this is the original admin user
    QSqlQuery query(db);
    query.prepare("SELECT id FROM users WHERE username = 'admin' LIMIT 1");
    
    if (query.exec() && query.next()) {
        QString adminId = query.value(0).toString();
        return id == adminId;
    }
    
    return false;
}

bool DBManager::validateUser(const QString& username, const QString& password, bool& isAdmin)
{
    qDebug() << "Validating user:" << username;
    
    // Hash the password for all users (including admin)
    QString passwordHash = QString(QCryptographicHash::hash(
        password.toUtf8(), QCryptographicHash::Sha256).toHex());
    
    QSqlQuery query(db);
    query.prepare("SELECT is_admin FROM users WHERE username = ? AND password = ?");
    query.addBindValue(username);
    query.addBindValue(passwordHash);
    
    if (query.exec() && query.next()) {
        isAdmin = query.value(0).toBool();
        qDebug() << "User validated successfully. Admin:" << isAdmin;
        return true;
    } else {
        qDebug() << "User validation failed";
        return false;
    }
}

bool DBManager::validateUser(const QString& username, const QString& password)
{
    bool isAdmin;
    return validateUser(username, password, isAdmin);
}

bool DBManager::userExists(const QString& username)
{
    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM users WHERE username = ?");
    query.addBindValue(username);
    
    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }
    
    return false;
}

bool DBManager::isUserAdmin(const QString& username)
{
    QSqlQuery query(db);
    query.prepare("SELECT is_admin FROM users WHERE username = ?");
    query.addBindValue(username);
    
    if (query.exec() && query.next()) {
        return query.value(0).toBool();
    }
    
    return false;
}

bool DBManager::createUser(const QString& username, const QString& password, bool isAdmin)
{
    return addUser(username, password, isAdmin);
}

bool DBManager::validateCredentials(const QString& username, const QString& password, bool* isAdmin)
{
    bool admin;
    bool valid = validateUser(username, password, admin);
    
    if (valid && isAdmin) {
        *isAdmin = admin;
    }
    
    return valid;
}

bool DBManager::executeSQL(const QString& sql)
{
    QSqlQuery query(db);
    bool success = query.exec(sql);
    if (!success) {
        qDebug() << "SQL Error:" << query.lastError().text();
    }
    return success;
}

bool DBManager::campusExists(const QString& name)
{
    if (!isOpen()) return false;
    
    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM colleges WHERE name = ?");
    query.addBindValue(name);
    
    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }
    
    return false;
}

bool DBManager::addCampus(const QString& name)
{
    if (!isOpen()) return false;
    
    // Check if the campus already exists
    if (campusExists(name)) {
        qDebug() << "Campus already exists:" << name;
        return false;
    }
    
    QSqlQuery query(db);
    query.prepare("INSERT INTO colleges (name) VALUES (?)");
    query.addBindValue(name);
    
    bool success = query.exec();
    if (!success) {
        qDebug() << "Failed to add campus:" << query.lastError().text();
    }
    
    return success;
}

bool DBManager::addDistance(const QString& fromCollege, const QString& toCollege, double distance)
{
    if (!isOpen()) return false;
    
    // Get college IDs from their names
    // From college ID
    QSqlQuery queryFrom(db);
    queryFrom.prepare("SELECT id FROM colleges WHERE name = ?");
    queryFrom.addBindValue(fromCollege);
    
    if (!queryFrom.exec() || !queryFrom.next()) {
        qDebug() << "Cannot find 'from' college:" << fromCollege;
        qDebug() << "Error:" << queryFrom.lastError().text();
        return false;
    }
    
    int fromCollegeId = queryFrom.value(0).toInt();
    
    // To college ID
    QSqlQuery queryTo(db);
    queryTo.prepare("SELECT id FROM colleges WHERE name = ?");
    queryTo.addBindValue(toCollege);
    
    if (!queryTo.exec() || !queryTo.next()) {
        qDebug() << "Cannot find 'to' college:" << toCollege;
        qDebug() << "Error:" << queryTo.lastError().text();
        return false;
    }
    
    int toCollegeId = queryTo.value(0).toInt();
    
    // Now we have both college IDs, insert the distance
    QSqlQuery insertQuery(db);
    insertQuery.prepare("INSERT OR REPLACE INTO distances (from_college_id, to_college_id, distance) VALUES (?, ?, ?)");
    insertQuery.addBindValue(fromCollegeId);
    insertQuery.addBindValue(toCollegeId);
    insertQuery.addBindValue(distance);
    
    bool success = insertQuery.exec();
    if (!success) {
        qDebug() << "Failed to add distance:" << insertQuery.lastError().text();
        return false;
    }
    
    // Also add the reverse direction for symmetry
    QSqlQuery reverseQuery(db);
    reverseQuery.prepare("INSERT OR REPLACE INTO distances (from_college_id, to_college_id, distance) VALUES (?, ?, ?)");
    reverseQuery.addBindValue(toCollegeId);
    reverseQuery.addBindValue(fromCollegeId);
    reverseQuery.addBindValue(distance);
    
    bool reverseSuccess = reverseQuery.exec();
    if (!reverseSuccess) {
        qDebug() << "Failed to add reverse distance:" << reverseQuery.lastError().text();
        // We'll still return true if at least the forward direction was added
    }
    
    return success;
} 