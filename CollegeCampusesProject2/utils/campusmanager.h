#ifndef CAMPUSMANAGER_H
#define CAMPUSMANAGER_H

#include <QString>
#include <QVector>
#include "../models/campus.h"

class CampusManager {
public:
    static const QString CAMPUS_FILE;
    static const QString DISTANCES_FILE;

    static QVector<Campus> readCampuses(const QString& filename);
    static bool writeCampuses(const QString& filename, const QVector<Campus>& campuses);
    static QVector<QVector<int>> readDistances(const QString& filename);
    static int getDistance(const QVector<QVector<int>>& distances, int fromId, int toId);
    static QVector<int> optimizeRoute(const QVector<QVector<int>>& distances, const QVector<int>& campusIds);
    static int calculateTotalDistance(const QVector<QVector<int>>& distances, const QVector<int>& route);

private:
    static Campus convertStringListToCampus(const QStringList& fields);
    static QStringList convertCampusToStringList(const Campus& campus);
};

#endif // CAMPUSMANAGER_H 