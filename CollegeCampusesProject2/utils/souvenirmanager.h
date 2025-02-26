#ifndef SOUVENIRMANAGER_H
#define SOUVENIRMANAGER_H

#include <QString>
#include <QVector>
#include "../models/souvenir.h"

class SouvenirManager {
public:
    static const QString SOUVENIR_FILE;
    
    static QVector<Souvenir> readSouvenirs(const QString& filename);
    static bool writeSouvenirs(const QString& filename, const QVector<Souvenir>& souvenirs);
    static QVector<Souvenir> getSouvenirsByCampus(const QVector<Souvenir>& souvenirs, int campusId);
    static bool updateSouvenirQuantity(Souvenir& souvenir, int quantity);

private:
    static Souvenir convertStringListToSouvenir(const QStringList& fields);
    static QStringList convertSouvenirToStringList(const Souvenir& souvenir);
};

#endif // SOUVENIRMANAGER_H 