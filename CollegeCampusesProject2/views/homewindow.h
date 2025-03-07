#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H

#include <QMainWindow>
#include <QSet>
#include "../utils/dbmanager.h"

class MainWindow;

namespace Ui {
class HomeWindow;
}

class HomeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit HomeWindow(DBManager* dbManager, QWidget *parent = nullptr);
    ~HomeWindow();

private slots:
    void on_viewSouvenirsButton_clicked();
    void on_planTripButton_clicked();
    void on_logoutButton_clicked();
    void on_souvenirsButton_clicked();
    void on_tripPlannerButton_clicked();
    void on_distancesButton_clicked();
    void onMainWindowClosed();

private:
    Ui::HomeWindow *ui;
    DBManager* m_dbManager;
    MainWindow* mainWindow = nullptr;
    
    void setupUI();
    void loadColleges();
    void displayCollegeDistances(const QString& startCollege, QSet<QString>& visited, 
                                 QString& output, int depth = 0);
};

#endif // HOMEWINDOW_H 