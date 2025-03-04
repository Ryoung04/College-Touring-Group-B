#include "views/mainwindow.h"

#include <QApplication>
#include <QDir>
#include "utils/dbmanager.h"
#include "views/loginwindow.h"
#include "utils/custombackground.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Initialize database
    QString dbPath = QDir(QCoreApplication::applicationDirPath()).filePath("colleges.db");
    DBManager dbManager(dbPath);
    
    // Create and show login window
    LoginWindow loginWindow(&dbManager);
    
    // Create and set the custom background
    CustomBackground* background = new CustomBackground(&loginWindow);
    background->setGeometry(loginWindow.rect());
    background->lower(); // Put it behind everything
    
    loginWindow.show();

    return a.exec();
}
