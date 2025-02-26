#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "utils/dbmanager.h"
#include "models/campus.h"
#include "views/adminpanel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(DBManager* db, bool isAdmin = false, QWidget *parent = nullptr);
    ~MainWindow();
    void showDistancesTab();
    void showSouvenirsTab();
    void showTripPlannerTab();

private slots:
    void onCampusSelected(const QString& campusName);
    void on_addToTripButton_clicked();
    void on_removeFromTripButton_clicked();
    void on_optimizeRouteButton_clicked();
    void on_calculateDistanceButton_clicked();
    void on_goToDistancesButton_clicked();
    void on_goToSouvenirsButton_clicked();
    void on_goToTripPlannerButton_clicked();

private:
    void loadCampuses();
    void setupSouvenirTab();
    void updateSouvenirDisplay(const QString& campusName);
    void updateDistancesTable(const QString& startingCampus);
    QVector<QString> findOptimalRoute(const QVector<QString>& campuses);
    double calculateTotalDistance(const QVector<QString>& route);
    void setupAdminControls();
    
    Ui::MainWindow *ui;
    DBManager* dbManager;
    QVector<Campus> allCampuses;
    bool isAdmin;
};

#endif // MAINWINDOW_H
