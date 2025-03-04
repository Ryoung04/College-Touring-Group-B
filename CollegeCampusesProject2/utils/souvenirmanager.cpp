#include "souvenirmanager.h"
#include <QFile>
#include <QTextStream>

const QString SouvenirManager::SOUVENIR_FILE = "data/souvenirs.csv";

QVector<Souvenir> SouvenirManager::readSouvenirs(const QString& filename) {
    QVector<Souvenir> souvenirs;
    QFile file(filename);
    
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return souvenirs;

    QTextStream in(&file);
    
    // Skip header
    if (!in.atEnd())
        in.readLine();
    
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");
        if (fields.size() >= 6) {
            souvenirs.append(convertStringListToSouvenir(fields));
        }
    }
    
    file.close();
    return souvenirs;
}

bool SouvenirManager::writeSouvenirs(const QString& filename, const QVector<Souvenir>& souvenirs) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&file);
    
    // Write header
    out << "souvenirId,campusId,name,price,quantity,category\n";
    
    // Write data
    for (const Souvenir& souvenir : souvenirs) {
        out << convertSouvenirToStringList(souvenir).join(",") << "\n";
    }
    
    file.close();
    return true;
}

QVector<Souvenir> SouvenirManager::getSouvenirsByCampus(const QVector<Souvenir>& souvenirs, int campusId) {
    QVector<Souvenir> result;
    for (const Souvenir& souvenir : souvenirs) {
        if (souvenir.getCampusId() == campusId) {
            result.append(souvenir);
        }
    }
    return result;
}

bool SouvenirManager::updateSouvenirQuantity(Souvenir& souvenir, int quantity) {
    if (quantity < 0 || quantity > souvenir.getQuantity())
        return false;
    
    souvenir.setQuantity(souvenir.getQuantity() - quantity);
    return true;
}

Souvenir SouvenirManager::convertStringListToSouvenir(const QStringList& fields) {
    return Souvenir(
        fields[0].toInt(),
        fields[1].toInt(),
        fields[2],
        fields[3].toDouble(),
        fields[4].toInt(),
        fields[5]
    );
}

QStringList SouvenirManager::convertSouvenirToStringList(const Souvenir& souvenir) {
    QStringList fields;
    fields << QString::number(souvenir.getId())
           << QString::number(souvenir.getCampusId())
           << souvenir.getName()
           << QString::number(souvenir.getPrice(), 'f', 2)
           << QString::number(souvenir.getQuantity())
           << souvenir.getCategory();
    return fields;
} 