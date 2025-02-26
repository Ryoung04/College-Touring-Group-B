#include "mainwindow.h"

#include <QApplication>
#include <QDir>
#include "utils/dbmanager.h"
#include "views/loginwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Create database manager
    QString dbPath = QDir(QCoreApplication::applicationDirPath()).filePath("colleges.db");
    DBManager dbManager(dbPath);

    // Create and show login window
    LoginWindow loginWindow(&dbManager);
    loginWindow.show();

    return a.exec();
}
