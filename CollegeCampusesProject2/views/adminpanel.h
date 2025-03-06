#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include <QDialog>
#include <QCloseEvent>
#include <QMessageBox>
#include <QInputDialog>
#include <QSqlQueryModel>
#include <QVector>
#include "../utils/dbmanager.h"
#include <QTextEdit>
#include <QLineEdit>
#include <QTableWidgetItem>

namespace Ui {
class AdminPanel;
}

class AdminPanel : public QDialog
{
    Q_OBJECT

public:
    explicit AdminPanel(DBManager* db, QWidget *parent = nullptr);
    ~AdminPanel();

signals:
    void collegesChanged();
    void souvenirsChanged();
    void distancesChanged();

private slots:
    void on_tabWidget_currentChanged(int index);
    
    // User management
    void on_addUserButton_clicked();
    void on_editUserButton_clicked();
    void on_deleteUserButton_clicked();
    void on_userTabButton_clicked();
    
    // Souvenir management
    void on_souvenirCollegeCombo_currentTextChanged(const QString &collegeName);
    void on_addSouvenirButton_clicked();
    void on_deleteSouvenirButton_clicked();
    void on_applySouvenirsButton_clicked();
    
    // College management
    void on_addCollegeButton_clicked();
    void on_editCollegeButton_clicked();
    void on_deleteCollegeButton_clicked();
    
    // Distance management
    void onDistanceChanged(QTableWidgetItem* item);
    void applyDistanceChanges();
    void cancelDistanceChanges();
    void closeDistancesTab();
    
    void setupSqlTerminal();
    void executeSqlCommand();
    void resetUsersTable();
    void applyUserChanges();

private:
    Ui::AdminPanel *ui;
    DBManager* dbManager;
    QSqlQueryModel* userModel = nullptr;
    bool hasUnsavedChanges;
    QVector<Campus> pendingColleges;
    QMap<QString, QMap<QString, double>> pendingDistanceChanges;
    QTextEdit* sqlTerminalDisplay;
    QLineEdit* sqlTerminalInput;

    void setupTables();
    void loadUsers();
    void loadColleges();
    void loadDistances();
    void loadSouvenirs(const QString& collegeName);
    void updateSouvenirComboBox();
    void revertChanges();
    void closeEvent(QCloseEvent* event) override;
    void reject() override;
};

#endif // ADMINPANEL_H 