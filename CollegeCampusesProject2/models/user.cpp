#include "user.h"

// Default constructor
User::User()
    : m_id(""), 
      m_username(""), 
      m_password(""), 
      m_isAdmin(false), 
      dateCreated(QDateTime::currentDateTime())
{
}

// Parameterized constructor
User::User(const QString& id, const QString& username, const QString& password, bool isAdmin)
    : m_id(id), 
      m_username(username), 
      m_password(password), 
      m_isAdmin(isAdmin), 
      dateCreated(QDateTime::currentDateTime())
{
}

// END OF FILE - No other method implementations here 