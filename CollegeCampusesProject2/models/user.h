#ifndef USER_H
#define USER_H

#include <QString>
#include <QDateTime>

class User {
public:
    User();  // Default constructor
    User(const QString& id, const QString& username, const QString& password, bool isAdmin);  // Constructor with parameters

    QString getId() const { return m_id; }
    QString getUsername() const { return m_username; }
    QString getPassword() const { return m_password; }
    bool isAdmin() const { return m_isAdmin; }
    QDateTime getDateCreated() const { return dateCreated; }

    void setId(const QString& id) { m_id = id; }
    void setUsername(const QString& username) { m_username = username; }
    void setPassword(const QString& password) { m_password = password; }
    void setAdmin(bool isAdmin) { m_isAdmin = isAdmin; }

private:
    QString m_id;
    QString m_username;
    QString m_password;  // This will store hashed password
    bool m_isAdmin;
    QDateTime dateCreated;
};

#endif // USER_H 