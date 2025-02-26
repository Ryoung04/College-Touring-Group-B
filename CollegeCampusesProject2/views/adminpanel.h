#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include <QDialog>
#include <QTableWidget>
#include <QPushButton>
#include <QCloseEvent>
#include "../utils/dbmanager.h"

namespace Ui {
class AdminPanel;
}

class AdminPanel : public QDialog
{
    Q_OBJECT

public:
    explicit AdminPanel(DBManager* db, QWidget *parent = nullptr);
    ~AdminPanel();

protected:
    void reject() override;
    void closeEvent(QCloseEvent* event) override;

private slots:
    void on_addCollegeButton_clicked();
    void on_editCollegeButton_clicked();
    void on_deleteCollegeButton_clicked();
    void on_souvenirCollegeCombo_currentTextChanged(const QString &collegeName);
    void on_applyButton_clicked();
    void on_saveExitButton_clicked();
    void on_cancelButton_clicked();
    void on_applySouvenirsButton_clicked();
    void on_saveSouvenirsButton_clicked();
    void on_cancelSouvenirsButton_clicked();
    void on_saveCollegesButton_clicked();
    void on_addUserButton_clicked();
    void on_editUserButton_clicked();
    void on_deleteUserButton_clicked();
    void on_usersTable_itemChanged(QTableWidgetItem* item);

private:
    void setupTables();
    void loadColleges();
    void loadDistances();
    void loadSouvenirs(const QString& collegeName);
    void updateSouvenirComboBox();
    void applyDistanceChanges();
    void setupUsersTable();
    void loadUsers();
    void revertChanges();

    Ui::AdminPanel *ui;
    DBManager* dbManager;
    QMap<QPair<QString, QString>, double> pendingDistanceChanges;
    QVector<Campus> pendingColleges;
    bool hasUnsavedChanges;
};

#endif // ADMINPANEL_H 