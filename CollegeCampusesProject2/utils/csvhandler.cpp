#include "csvhandler.h"
#include <QFile>
#include <QTextStream>
#include <QCryptographicHash>
#include <QDebug>

const QString CSVHandler::USER_FILE = "users.csv";

bool CSVHandler::writeUsers(const QString& filename, const QVector<User>& users) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&file);
    
    // Write header
    out << "userId,username,password,isAdmin,dateCreated\n";
    
    // Write data
    for (const User& user : users) {
        QStringList fields;
        fields << user.getUserId()
               << user.getUsername()
               << user.getPassword()
               << (user.getIsAdmin() ? "1" : "0")
               << user.getDateCreated().toString(Qt::ISODate);
        out << fields.join(",") << "\n";
    }
    
    file.close();
    return true;
}

QVector<User> CSVHandler::readUsers(const QString& filename) {
    QVector<User> users;
    QFile file(filename);
    
    // If file doesn't exist, create it
    if (!file.exists()) {
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "Failed to create users file";
            return users;
        }
        QTextStream out(&file);
        out << "userId,username,password,isAdmin,dateCreated\n";
        file.close();
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open users file";
        return users;
    }

    QTextStream in(&file);
    
    // Skip header
    if (!in.atEnd())
        in.readLine();
    
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");
        if (fields.size() >= 4) {
            users.append(convertStringListToUser(fields));
        }
    }
    
    file.close();
    return users;
}

QString CSVHandler::hashPassword(const QString& password) {
    QByteArray hash = QCryptographicHash::hash(
        password.toUtf8(),
        QCryptographicHash::Sha256
    );
    return QString(hash.toHex());
}

bool CSVHandler::validateUser(const QString& username, const QString& password) {
    QVector<User> users = readUsers(USER_FILE);
    QString hashedPassword = hashPassword(password);
    
    for (const User& user : users) {
        if (user.getUsername() == username && user.getPassword() == hashedPassword) {
            return true;
        }
    }
    return false;
}

QVector<QString> CSVHandler::convertUserToStringList(const User& user) {
    QVector<QString> fields;
    fields.append(user.getUserId());
    fields.append(user.getUsername());
    fields.append(user.getPassword());
    fields.append(user.getIsAdmin() ? "1" : "0");
    return fields;
}

User CSVHandler::convertStringListToUser(const QStringList& fields) {
    return User(
        fields[0],
        fields[1],
        fields[2],
        fields[3] == "1"
    );
} 