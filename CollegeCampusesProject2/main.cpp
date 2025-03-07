#include "views/mainwindow.h"

#include <QApplication>
#include <QDir>
#include "utils/dbmanager.h"
#include "views/loginwindow.h"
#include "utils/custombackground.h"
#include "views/adminpanel.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>

// Path to database file relative to executable
const QString DB_FILENAME = "campus_db.sqlite";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // Set up the database path
    QString execPath = QCoreApplication::applicationDirPath();
    QString dbPath = execPath + "/" + DB_FILENAME;
    qDebug() << "Database path:" << dbPath;
    
    // Create and connect to database
    DBManager dbManager;
    if (!dbManager.connectToDatabase(dbPath)) {
        qDebug() << "Failed to connect to database";
        return 1;
    }

    // Delete the database file if you want to start fresh
    // QFile::remove(dbPath);
    // dbManager.connectToDatabase(dbPath);

    // Import data if database is empty
    QVector<Campus> campuses = dbManager.getAllCampuses();
    qDebug() << "Initial campus count:" << campuses.size();
    
    if (campuses.isEmpty()) {
        qDebug() << "Database is empty, importing initial data...";
        
        // Define paths to CSV files
        QString collegesCSV = ":/data/colleges.csv";
        QString souvenirsCSV = ":/data/souvenirs.csv";
        
        // Debug: Print contents of CSV files
        QFile file(collegesCSV);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            qDebug() << "First few lines of colleges CSV:";
            for (int i = 0; i < 5 && !in.atEnd(); i++) {
                qDebug() << in.readLine();
            }
            file.close();
        }
        
        QFile souvenirFile(souvenirsCSV);
        if (souvenirFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&souvenirFile);
            qDebug() << "First few lines of souvenirs CSV:";
            for (int i = 0; i < 5 && !in.atEnd(); i++) {
                qDebug() << in.readLine();
            }
            souvenirFile.close();
        }
        
        // Import data
        bool collegesImported = dbManager.importCollegesFromCSV(collegesCSV);
        qDebug() << "Colleges import:" << (collegesImported ? "success" : "failed");
        
        // Check if colleges were imported successfully
        campuses = dbManager.getAllCampuses();
        qDebug() << "Colleges after import:" << campuses.size();
        
        // List all imported colleges
        qDebug() << "Imported colleges:";
        for (const Campus& campus : campuses) {
            qDebug() << "  -" << campus.getName();
        }
        
        // Now import souvenirs
        bool souvenirsImported = dbManager.importSouvenirsFromCSV(souvenirsCSV);
        qDebug() << "Souvenirs import:" << (souvenirsImported ? "success" : "failed");
        
        // Debug souvenirs 
        dbManager.debugPrintSouvenirs();
    }

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
