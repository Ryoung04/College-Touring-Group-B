#pragma once

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QMap>
#include <QString>
#include "csvparser.h"

class CollegeDistanceWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CollegeDistanceWidget(QWidget *parent = nullptr);

signals:
    void logout();

private slots:
    void onCollegeClicked(QListWidgetItem* item);
    void onLogoutClicked();

private:
    void updateTotalDistance();
    double calculateTotalDistance();

    QListWidget* collegeList;
    QListWidget* selectedColleges;
    QLabel* totalDistanceLabel;
    QPushButton* logoutButton;
    QMap<QString, QMap<QString, double>> distanceMap;
};
