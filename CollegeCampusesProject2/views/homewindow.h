#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H

#include <QMainWindow>
#include <QSet>
#include "../utils/dbmanager.h"

// Forward declaration instead of including the header
class MainWindow;

namespace Ui {
class HomeWindow;
}

class HomeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit HomeWindow(DBManager* db, QWidget *parent = nullptr);
    ~HomeWindow();

private slots:
    void on_distancesButton_clicked();
    void on_souvenirsButton_clicked();
    void on_tripPlannerButton_clicked();
    void onMainWindowClosed(); // Add this method to handle MainWindow closure

private:
    void displayCollegeDistances(const QString& startCollege, QSet<QString>& visited, QString& output, int depth = 0);
    Ui::HomeWindow *ui;
    DBManager* dbManager;
    MainWindow* mainWindow;
};

#endif // HOMEWINDOW_H 