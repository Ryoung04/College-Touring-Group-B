#ifndef CSVHANDLER_H
#define CSVHANDLER_H

#include <QString>
#include <QVector>
#include <QStringList>
#include "../models/user.h"

class CSVHandler {
public:
    static const QString USER_FILE;
    static bool writeUsers(const QString& filename, const QVector<User>& users);
    static QVector<User> readUsers(const QString& filename);
    static QString hashPassword(const QString& password);
    static bool validateUser(const QString& username, const QString& password);

private:
    static QVector<QString> convertUserToStringList(const User& user);
    static User convertStringListToUser(const QStringList& fields);
};

#endif // CSVHANDLER_H 