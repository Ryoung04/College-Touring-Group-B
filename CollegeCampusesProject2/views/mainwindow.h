#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QToolBar>
#include <QPushButton>
#include <QShortcut>
#include <QListWidget>
#include <QGroupBox>
#include "../utils/dbmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(DBManager* db, bool isAdmin = false, QWidget *parent = nullptr);
    ~MainWindow();
    void showDistancesTab();
    void showSouvenirsTab();
    void showTripPlannerTab();
    void displayDistances(const QString& distances);
    void setIsAdmin(bool admin);

private slots:
    void refreshColleges();
    void refreshSouvenirs();
    void refreshDistances();
    void onTabChanged(int index);
    void on_refreshDistancesButton_clicked() { refreshDistances(); }
    void on_refreshSouvenirsButton_clicked() { refreshSouvenirs(); }
    void on_refreshTripButton_clicked() { refreshColleges(); }
    void on_actionManageColleges_triggered();
    
    // Trip planner methods
    void setupTripPlanner();
    void loadAllColleges();
    void addToTrip();
    void removeFromTrip();
    void moveCollegeUp();
    void moveCollegeDown();
    void calculateRoute();
    void optimizeRoute();
    void resetTrip();
    void updateTripCollegeHighlighting();

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    void setupMenuBar();
    void updateAllComboBoxes();
    void refreshAllData();
    void setupUiConnections();
    void addCollegesToTrip(const QList<QListWidgetItem*>& items);
    void removeCollegesFromTrip(const QList<QListWidgetItem*>& items);
    
    Ui::MainWindow *ui;
    DBManager* dbManager;
    bool isAdmin;
};

#endif // MAINWINDOW_H 