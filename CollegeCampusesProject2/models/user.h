#ifndef USER_H
#define USER_H

#include <QString>
#include <QDateTime>

class User {
public:
    User();  // Default constructor
    User(const QString& id, const QString& username, const QString& password, bool isAdmin);  // Constructor with parameters

    QString getUserId() const { return userId; }
    QString getUsername() const { return username; }
    QString getPassword() const { return password; }
    bool getIsAdmin() const { return isAdmin; }
    QDateTime getDateCreated() const { return dateCreated; }

    void setUserId(const QString& id) { userId = id; }
    void setUsername(const QString& name) { username = name; }
    void setPassword(const QString& pwd) { password = pwd; }
    void setIsAdmin(bool admin) { isAdmin = admin; }

private:
    QString userId;
    QString username;
    QString password;  // This will store hashed password
    bool isAdmin;
    QDateTime dateCreated;
};

#endif // USER_H 