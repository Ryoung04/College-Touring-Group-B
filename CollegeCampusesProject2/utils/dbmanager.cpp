#include "dbmanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QTextStream>
#include <QDebug>

DBManager::DBManager(const QString& path)
{
    // First check available drivers
    qDebug() << "Available SQL drivers:" << QSqlDatabase::drivers();

    // Store the path for reconnection if needed
    m_dbPath = path;

    // Remove any existing connection
    if (QSqlDatabase::contains("CAMPUS_CONNECTION")) {
        QSqlDatabase::removeDatabase("CAMPUS_CONNECTION");
    }

    // Create a new connection
    m_db = QSqlDatabase::addDatabase("QSQLITE", "CAMPUS_CONNECTION");
    m_db.setDatabaseName(path);

    if (!m_db.open()) {
        qDebug() << "Failed to open database at:" << path;
        qDebug() << "Error:" << m_db.lastError().text();
        return;
    }

    // Initialize database with tables
    QSqlQuery query(m_db);
    
    // Enable foreign keys
    query.exec("PRAGMA foreign_keys = ON");

    // Create tables if they don't exist
    if (!query.exec("CREATE TABLE IF NOT EXISTS colleges ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "name TEXT NOT NULL UNIQUE)")) {
        qDebug() << "Error creating colleges table:" << query.lastError().text();
    }

    if (!query.exec("CREATE TABLE IF NOT EXISTS distances ("
                   "from_college_id INTEGER,"
                   "to_college_id INTEGER,"
                   "distance REAL,"
                   "PRIMARY KEY (from_college_id, to_college_id),"
                   "FOREIGN KEY (from_college_id) REFERENCES colleges(id),"
                   "FOREIGN KEY (to_college_id) REFERENCES colleges(id))")) {
        qDebug() << "Error creating distances table:" << query.lastError().text();
    }

    if (!query.exec("CREATE TABLE IF NOT EXISTS souvenirs ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "college_id INTEGER,"
                   "name TEXT NOT NULL,"
                   "price REAL NOT NULL CHECK (price >= 0),"
                   "FOREIGN KEY (college_id) REFERENCES colleges(id),"
                   "UNIQUE(college_id, name))")) {
        qDebug() << "Error creating souvenirs table:" << query.lastError().text();
    }

    qDebug() << "Database initialized successfully at:" << path;
}

DBManager::~DBManager()
{
    if (m_db.isOpen())
        m_db.close();
}

bool DBManager::isOpen() const
{
    return m_db.isOpen();
}

bool DBManager::createTables()
{
    QSqlQuery query(m_db);
    
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

    m_db.transaction();

    // Prepare statements once
    QSqlQuery insertCollege(m_db);
    insertCollege.prepare("INSERT OR IGNORE INTO colleges (name) VALUES (?)");
    
    QSqlQuery insertDistance(m_db);
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

    bool success = m_db.commit();
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
    m_db.transaction();

    // Clear existing souvenirs first
    QSqlQuery clearQuery(m_db);
    if (!clearQuery.exec("DELETE FROM souvenirs")) {
        qDebug() << "Failed to clear existing souvenirs:" << clearQuery.lastError().text();
        m_db.rollback();
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
            QSqlQuery query(m_db);
            query.prepare("SELECT id FROM colleges WHERE name = ?");
            query.addBindValue(collegeName);
            
            if (!query.exec()) {
                qDebug() << "Failed to query college:" << query.lastError().text();
                m_db.rollback();
                return false;
            }
            
            if (!query.next()) {
                qDebug() << "WARNING: College not found in database:" << collegeName;
                qDebug() << "Available colleges:";
                QSqlQuery collegesQuery(m_db);
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
                m_db.rollback();
                return false;
            }
            
            qDebug() << "Successfully imported souvenir:" << souvenirName << "for" << collegeName;
        } else {
            qDebug() << "Invalid line format:" << line;
        }
    }

    bool success = m_db.commit();
    qDebug() << "Souvenir import" << (success ? "successful" : "failed");
    return success;
}

bool DBManager::ensureConnection() const
{
    if (!m_db.isOpen()) {
        qDebug() << "Attempting to reopen database connection";
        const_cast<QSqlDatabase&>(m_db).open();
    }
    return m_db.isOpen();
}

QVector<Campus> DBManager::getAllCampuses() const
{
    QVector<Campus> campuses;
    if (!ensureConnection()) {
        qDebug() << "Failed to ensure database connection";
        return campuses;
    }

    QSqlQuery query(m_db);
    
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
    QSqlQuery query(m_db);
    
    // Try both directions in a single query
    query.prepare(
        "SELECT MIN(d.distance) "
        "FROM colleges c1, colleges c2, "
        "( "
        "    SELECT from_college_id, to_college_id, distance FROM distances "
        "    UNION ALL "
        "    SELECT to_college_id, from_college_id, distance FROM distances "
        ") d "
        "WHERE c1.id = d.from_college_id "
        "AND c2.id = d.to_college_id "
        "AND c1.name = ? AND c2.name = ?"
    );
    
    query.addBindValue(fromCollege);
    query.addBindValue(toCollege);
    
    if (!query.exec()) {
        qDebug() << "Error getting distance:" << query.lastError().text();
        return -1;
    }
    
    if (query.next() && !query.value(0).isNull()) {
        return query.value(0).toDouble();
    }
    
    return -1;
}

QVector<QPair<QString, double>> DBManager::getSouvenirs(const QString& collegeName) const
{
    QVector<QPair<QString, double>> souvenirs;
    QSqlQuery query(m_db);
    
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
    QSqlQuery query(m_db);
    
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
    QSqlQuery query(m_db);
    
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
    QSqlQuery query(m_db);
    
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

bool DBManager::updateDistance(const QString& fromCollege, const QString& toCollege, double newDistance)
{
    QSqlQuery query(m_db);
    
    // Update the distance in both directions since it's bidirectional
    query.prepare(
        "UPDATE distances "
        "SET distance = ? "
        "WHERE (from_college_id = (SELECT id FROM colleges WHERE name = ?) "
        "AND to_college_id = (SELECT id FROM colleges WHERE name = ?)) "
        "OR (from_college_id = (SELECT id FROM colleges WHERE name = ?) "
        "AND to_college_id = (SELECT id FROM colleges WHERE name = ?))"
    );
    
    query.addBindValue(newDistance);
    query.addBindValue(fromCollege);
    query.addBindValue(toCollege);
    query.addBindValue(toCollege);    // Reverse direction
    query.addBindValue(fromCollege);  // Reverse direction
    
    if (!query.exec()) {
        qDebug() << "Error updating distance:" << query.lastError().text();
        return false;
    }
    
    return query.numRowsAffected() > 0;
}

bool DBManager::addCollege(const QString& name)
{
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO colleges (name) VALUES (?)");
    query.addBindValue(name);
    
    return query.exec();
}

bool DBManager::updateCollege(int id, const QString& newName)
{
    QSqlQuery query(m_db);
    query.prepare("UPDATE colleges SET name = ? WHERE id = ?");
    query.addBindValue(newName);
    query.addBindValue(id);
    
    return query.exec();
}

bool DBManager::deleteCollege(int id)
{
    QSqlQuery query(m_db);
    
    // Start a transaction since we need to delete from multiple tables
    m_db.transaction();
    
    // Delete distances first (due to foreign key constraints)
    query.prepare("DELETE FROM distances WHERE from_college_id = ? OR to_college_id = ?");
    query.addBindValue(id);
    query.addBindValue(id);
    if (!query.exec()) {
        m_db.rollback();
        return false;
    }
    
    // Delete souvenirs
    query.prepare("DELETE FROM souvenirs WHERE college_id = ?");
    query.addBindValue(id);
    if (!query.exec()) {
        m_db.rollback();
        return false;
    }
    
    // Finally delete the college
    query.prepare("DELETE FROM colleges WHERE id = ?");
    query.addBindValue(id);
    if (!query.exec()) {
        m_db.rollback();
        return false;
    }
    
    return m_db.commit();
}

bool DBManager::addCollegeWithDistances(const QString& name, const QMap<QString, double>& distances)
{
    m_db.transaction();
    
    // First add the college
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO colleges (name) VALUES (?)");
    query.addBindValue(name);
    
    if (!query.exec()) {
        m_db.rollback();
        return false;
    }
    
    // Get the new college's ID
    int newCollegeId = query.lastInsertId().toInt();
    
    // Add distances to other colleges
    for (auto it = distances.begin(); it != distances.end(); ++it) {
        // Get the other college's ID
        query.prepare("SELECT id FROM colleges WHERE name = ?");
        query.addBindValue(it.key());
        if (!query.exec() || !query.next()) {
            m_db.rollback();
            return false;
        }
        int otherCollegeId = query.value(0).toInt();
        
        // Add distance in both directions
        query.prepare("INSERT INTO distances (from_college_id, to_college_id, distance) VALUES (?, ?, ?)");
        query.addBindValue(newCollegeId);
        query.addBindValue(otherCollegeId);
        query.addBindValue(it.value());
        if (!query.exec()) {
            m_db.rollback();
            return false;
        }
        
        // Add reverse direction
        query.prepare("INSERT INTO distances (from_college_id, to_college_id, distance) VALUES (?, ?, ?)");
        query.addBindValue(otherCollegeId);
        query.addBindValue(newCollegeId);
        query.addBindValue(it.value());
        if (!query.exec()) {
            m_db.rollback();
            return false;
        }
    }
    
    return m_db.commit();
}

bool DBManager::reloadDatabase()
{
    // Close existing connection if open
    if (m_db.isOpen()) {
        m_db.close();
    }

    // Remove the old connection if it exists
    QString connectionName = m_db.connectionName();
    m_db = QSqlDatabase(); // destroy old connection
    if (QSqlDatabase::contains(connectionName)) {
        QSqlDatabase::removeDatabase(connectionName);
    }

    // Create a new connection with a unique name
    static int connectionCounter = 0;
    QString newConnectionName = QString("CAMPUS_CONNECTION_%1").arg(++connectionCounter);
    m_db = QSqlDatabase::addDatabase("QSQLITE", newConnectionName);
    m_db.setDatabaseName(m_dbPath);

    if (!m_db.open()) {
        qDebug() << "Failed to reload database at:" << m_dbPath;
        qDebug() << "Error:" << m_db.lastError().text();
        return false;
    }

    // Enable foreign keys
    QSqlQuery query(m_db);
    query.exec("PRAGMA foreign_keys = ON");

    return true;
}

void DBManager::debugPrintSouvenirs() const
{
    QSqlQuery query(m_db);
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
    QVector<UserInfo> users;
    QSqlQuery query(m_db);
    
    if (!query.exec("SELECT id, username, is_admin FROM users ORDER BY username")) {
        qDebug() << "Error fetching users:" << query.lastError().text();
        return users;
    }
    
    while (query.next()) {
        UserInfo user;
        user.id = query.value(0).toInt();
        user.username = query.value(1).toString();
        user.isAdmin = query.value(2).toBool();
        users.append(user);
    }
    
    return users;
}

bool DBManager::addUser(const QString& username, const QString& password, bool isAdmin)
{
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO users (username, password, is_admin) VALUES (?, ?, ?)");
    query.addBindValue(username);
    query.addBindValue(password); // Note: In a real app, you'd want to hash this
    query.addBindValue(isAdmin);
    
    return query.exec();
}

bool DBManager::updateUser(int id, const QString& username, const QString& password, bool isAdmin)
{
    if (isOriginalAdmin(id) && !isAdmin) {
        qDebug() << "Cannot remove admin status from original admin";
        return false;
    }
    
    QSqlQuery query(m_db);
    if (password.isEmpty()) {
        // Update without changing password
        query.prepare("UPDATE users SET username = ?, is_admin = ? WHERE id = ?");
        query.addBindValue(username);
        query.addBindValue(isAdmin);
        query.addBindValue(id);
    } else {
        // Update including new password
        query.prepare("UPDATE users SET username = ?, password = ?, is_admin = ? WHERE id = ?");
        query.addBindValue(username);
        query.addBindValue(password); // Note: In a real app, you'd want to hash this
        query.addBindValue(isAdmin);
        query.addBindValue(id);
    }
    
    return query.exec();
}

bool DBManager::deleteUser(int id)
{
    if (isOriginalAdmin(id)) {
        qDebug() << "Cannot delete original admin user";
        return false;
    }
    
    QSqlQuery query(m_db);
    query.prepare("DELETE FROM users WHERE id = ?");
    query.addBindValue(id);
    
    return query.exec();
}

bool DBManager::isOriginalAdmin(int id) const
{
    QSqlQuery query(m_db);
    query.prepare("SELECT id FROM users WHERE id = ? AND username = 'admin'");
    query.addBindValue(id);
    
    return query.exec() && query.next();
} 