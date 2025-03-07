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
#include "../utils/souvenirtripmanager.h"
#include <QTableWidget>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(DBManager* db, bool isAdmin, QWidget *parent = nullptr);
    ~MainWindow();
    void showDistancesTab();
    void showSouvenirsTab();
    void showTripPlannerTab();
    void displayDistances(const QString& distances);
    void setIsAdmin(bool admin);

private slots:
    // Admin-related slots
    void on_actionLogin_triggered();
    void onCollegesChanged();
    void onSouvenirsChanged();
    void onDistancesChanged();
    
    // Trip-related slots
    void on_collegeComboBox_currentIndexChanged(int index);
    void loadSouvenirs(const QString& collegeName);
    void addSouvenirToTrip();
    void removeSouvenirFromTrip();
    void onSouvenirTripChanged();
    void updateTripCostLabel();
    
    // General UI slots
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
    
    // New method for Trip Summary Report
    void generateTripSummaryReport();

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
    SouvenirTripManager* souvenirTripManager;
    QTableWidget* tripSouvenirsTable;
    QLabel* totalCostLabel;
    bool isAdmin;
    
    // Load initial data
    void loadColleges();
    
    // Helper methods for trip planning UI
    void setupSouvenirsTab();
    
    // Helper method to format the trip summary
    QString formatTripSummary() const;
};

#endif // MAINWINDOW_H 