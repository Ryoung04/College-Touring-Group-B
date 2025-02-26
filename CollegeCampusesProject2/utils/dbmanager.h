#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QString>
#include <QVector>
#include "../models/campus.h"
#include <QMap>

class DBManager
{
public:
    explicit DBManager(const QString& path);
    ~DBManager();

    bool isOpen() const;
    bool createTables();
    bool importCollegesFromCSV(const QString& csvPath);
    bool importSouvenirsFromCSV(const QString& csvPath);
    QVector<Campus> getAllCampuses() const;
    double getDistance(const QString& fromCollege, const QString& toCollege) const;
    
    // Add these new methods for souvenirs
    QVector<QPair<QString, double>> getSouvenirs(const QString& collegeName) const;
    bool addSouvenir(const QString& collegeName, const QString& name, double price);
    bool updateSouvenir(const QString& collegeName, const QString& name, double price);
    bool deleteSouvenir(const QString& collegeName, const QString& name);
    bool updateDistance(const QString& fromCollege, const QString& toCollege, double newDistance);
    bool addCollege(const QString& name);
    bool updateCollege(int id, const QString& newName);
    bool deleteCollege(int id);
    bool addCollegeWithDistances(const QString& name, const QMap<QString, double>& distances);
    bool reloadDatabase();
    void debugPrintSouvenirs() const;

    // User management methods
    struct UserInfo {
        int id;
        QString username;
        bool isAdmin;
    };
    
    QVector<UserInfo> getAllUsers() const;
    bool addUser(const QString& username, const QString& password, bool isAdmin);
    bool updateUser(int id, const QString& username, const QString& password, bool isAdmin);
    bool deleteUser(int id);
    bool isOriginalAdmin(int id) const;

private:
    bool ensureConnection() const;
    QSqlDatabase m_db;
    QString m_dbPath;
};

#endif // DBMANAGER_H 