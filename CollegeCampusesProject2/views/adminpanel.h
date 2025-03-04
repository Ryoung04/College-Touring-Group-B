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

signals:
    void collegesChanged();
    void souvenirsChanged();
    void distancesChanged();

private slots:
    void on_addCollegeButton_clicked();
    void on_editCollegeButton_clicked();
    void on_deleteCollegeButton_clicked();
    void on_saveCollegesButton_clicked();
    void on_applySouvenirsButton_clicked();
    void on_saveSouvenirsButton_clicked();
    void on_cancelSouvenirsButton_clicked();
    void on_souvenirCollegeCombo_currentTextChanged(const QString &collegeName);
    void on_addSouvenirButton_clicked();
    void on_deleteSouvenirButton_clicked();
    void on_distancesApplyButton_clicked();
    void on_distancesSaveExitButton_clicked();
    void on_distancesCancelButton_clicked();
    void on_addUserButton_clicked();
    void on_editUserButton_clicked();
    void on_deleteUserButton_clicked();
    void on_tabWidget_currentChanged(int index);

private:
    void setupTables();
    void loadColleges();
    void loadDistances();
    void loadSouvenirs(const QString& collegeName);
    void updateSouvenirComboBox();
    void revertChanges();

    Ui::AdminPanel *ui;
    DBManager* dbManager;
    QMap<QPair<QString, QString>, double> pendingDistanceChanges;
    QVector<Campus> pendingColleges;
    bool hasUnsavedChanges;
};

#endif // ADMINPANEL_H 