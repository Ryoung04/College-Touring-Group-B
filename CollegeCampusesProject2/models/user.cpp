#include "user.h"
#include <QCryptographicHash>

User::User() : isAdmin(false), dateCreated(QDateTime::currentDateTime())
{
}

User::User(const QString& id, const QString& username, const QString& password, bool isAdmin)
    : userId(id),
      username(username),
      password(password),
      isAdmin(isAdmin),
      dateCreated(QDateTime::currentDateTime())
{
} 