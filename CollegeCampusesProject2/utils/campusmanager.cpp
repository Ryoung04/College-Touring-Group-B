#include "campusmanager.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QSet>
#include <algorithm>
#include <limits>

const QString CampusManager::CAMPUS_FILE = ":/data/data/colleges.csv";
const QString CampusManager::DISTANCES_FILE = ":/data/data/colleges.csv";  // Use the same file

QVector<Campus> CampusManager::readCampuses(const QString& filename) {
    QVector<Campus> campuses;
    QSet<QString> uniqueCampusNames;
    QMap<QString, Campus> campusMap;
    int nextId = 1;

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << filename;
        return campuses;
    }

    QTextStream in(&file);
    
    // Skip header
    if (!in.atEnd())
        in.readLine();
    
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");
        if (fields.size() >= 2) {
            QString startCampus = fields[0].trimmed();
            QString endCampus = fields[1].trimmed();
            
            if (!uniqueCampusNames.contains(startCampus)) {
                uniqueCampusNames.insert(startCampus);
                Campus campus;
                campus.setId(nextId++);
                campus.setName(startCampus);
                campusMap[startCampus] = campus;
            }
            
            if (!uniqueCampusNames.contains(endCampus)) {
                uniqueCampusNames.insert(endCampus);
                Campus campus;
                campus.setId(nextId++);
                campus.setName(endCampus);
                campusMap[endCampus] = campus;
            }
        }
    }

    // Convert map to vector
    for (const QString& name : uniqueCampusNames) {
        campuses.append(campusMap[name]);
    }

    // Sort campuses by ID to maintain consistent order
    std::sort(campuses.begin(), campuses.end(), 
              [](const Campus& a, const Campus& b) { return a.getId() < b.getId(); });

    file.close();
    qDebug() << "Loaded" << campuses.size() << "unique campuses";
    return campuses;
}

bool CampusManager::writeCampuses(const QString& filename, const QVector<Campus>& campuses) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&file);
    
    // Write header
    out << "campusId,name,state,undergraduateCount,startingDate,location\n";
    
    // Write data
    for (const Campus& campus : campuses) {
        out << convertCampusToStringList(campus).join(",") << "\n";
    }
    
    file.close();
    return true;
}

QVector<QVector<int>> CampusManager::readDistances(const QString& filename) {
    QVector<Campus> campuses = readCampuses(filename);
    QMap<QString, int> campusToIndex;
    
    // Create mapping from campus names to indices
    for (int i = 0; i < campuses.size(); ++i) {
        campusToIndex[campuses[i].getName()] = i;
    }
    
    // Initialize distance matrix with zeros
    int n = campuses.size();
    QVector<QVector<int>> distances(n, QVector<int>(n, 0));
    
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for distances:" << filename;
        return distances;
    }

    QTextStream in(&file);
    
    // Skip header
    if (!in.atEnd())
        in.readLine();
    
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");
        if (fields.size() >= 3) {
            QString fromCampus = fields[0].trimmed();
            QString toCampus = fields[1].trimmed();
            int distance = fields[2].toInt();
            
            if (campusToIndex.contains(fromCampus) && campusToIndex.contains(toCampus)) {
                int fromIdx = campusToIndex[fromCampus];
                int toIdx = campusToIndex[toCampus];
                distances[fromIdx][toIdx] = distance;
                distances[toIdx][fromIdx] = distance;  // Make the matrix symmetric
            }
        }
    }
    
    file.close();
    qDebug() << "Created distance matrix of size" << n << "x" << n;
    return distances;
}

int CampusManager::getDistance(const QVector<QVector<int>>& distances, int fromId, int toId) {
    if (fromId >= distances.size() || toId >= distances[fromId].size())
        return -1;
    return distances[fromId][toId];
}

QVector<int> CampusManager::optimizeRoute(const QVector<QVector<int>>& distances, const QVector<int>& campusIds) {
    // Simple nearest neighbor algorithm
    QVector<int> route;
    QVector<bool> visited(campusIds.size(), false);
    
    if (campusIds.isEmpty())
        return route;
        
    // Start with the first campus
    route.append(campusIds[0]);
    visited[0] = true;
    
    while (route.size() < campusIds.size()) {
        int lastCampus = route.last();
        int nearestCampus = -1;
        int minDistance = std::numeric_limits<int>::max();
        
        for (int i = 0; i < campusIds.size(); ++i) {
            if (!visited[i]) {
                int distance = getDistance(distances, lastCampus, campusIds[i]);
                if (distance > 0 && distance < minDistance) {
                    minDistance = distance;
                    nearestCampus = campusIds[i];
                }
            }
        }
        
        if (nearestCampus != -1) {
            route.append(nearestCampus);
            visited[campusIds.indexOf(nearestCampus)] = true;
        }
    }
    
    return route;
}

int CampusManager::calculateTotalDistance(const QVector<QVector<int>>& distances, const QVector<int>& route) {
    int totalDistance = 0;
    
    for (int i = 0; i < route.size() - 1; ++i) {
        int distance = getDistance(distances, route[i], route[i + 1]);
        if (distance < 0)
            return -1;
        totalDistance += distance;
    }
    
    return totalDistance;
}

Campus CampusManager::convertStringListToCampus(const QStringList& fields) {
    return Campus(
        fields[0].toInt(),
        fields[1],
        fields[2],
        fields[3].toInt(),
        fields[4],
        fields[5]
    );
}

QStringList CampusManager::convertCampusToStringList(const Campus& campus) {
    QStringList fields;
    fields << QString::number(campus.getId())
           << campus.getName()
           << campus.getState()
           << QString::number(campus.getUndergraduateCount())
           << campus.getStartingDate()
           << campus.getLocation();
    return fields;
} 