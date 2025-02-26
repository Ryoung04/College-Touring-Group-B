#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H

#include <QMainWindow>
#include "mainwindow.h"
#include "../utils/dbmanager.h"

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

private:
    Ui::HomeWindow *ui;
    DBManager* dbManager;
    MainWindow* mainWindow;

signals:
    void returnToHome();
};

#endif // HOMEWINDOW_H 