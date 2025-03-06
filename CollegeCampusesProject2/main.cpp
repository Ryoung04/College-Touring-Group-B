#include "views/mainwindow.h"

#include <QApplication>
#include <QDir>
#include "utils/dbmanager.h"
#include "views/loginwindow.h"
#include "utils/custombackground.h"
#include "views/adminpanel.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // Get the application directory path
    QString appDirPath = QCoreApplication::applicationDirPath();
    QString dbPath = appDirPath + "/colleges.db";
    
    qDebug() << "Database path:" << dbPath;
    
    // Initialize database manager
    DBManager dbManager(dbPath);
    
    // Create login window with custom background
    CustomBackground *background = new CustomBackground();
    LoginWindow *loginWindow = new LoginWindow(&dbManager, background);
    
    // Show login window
    loginWindow->show();
    
    // For testing purposes, you can uncomment this to bypass login and go straight to admin panel
    // AdminPanel adminPanel(&dbManager);
    // adminPanel.exec();
    
    return a.exec();
}
