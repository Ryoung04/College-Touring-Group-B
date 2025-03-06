#ifndef SOUVENIRTRIPMANAGER_H
#define SOUVENIRTRIPMANAGER_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QTableWidget>

class SouvenirTripManager : public QObject
{
    Q_OBJECT

public:
    // Structure to represent a souvenir in the trip
    struct TripSouvenir {
        QString collegeName;
        QString name;
        double price;
        int quantity;
        
        TripSouvenir(const QString& college, const QString& souvenirName, double souvenirPrice, int qty = 1)
            : collegeName(college), name(souvenirName), price(souvenirPrice), quantity(qty) {}
            
        double totalPrice() const { return price * quantity; }
    };
    
    explicit SouvenirTripManager(QObject *parent = nullptr);
    
    // Methods to manage souvenirs
    void addSouvenir(const QString& collegeName, const QString& souvenirName, double price);
    void removeSouvenir(int index);
    void clearSouvenirs();
    void updateQuantity(int index, int quantity);
    
    // Getters
    QVector<TripSouvenir> getSouvenirs() const { return selectedSouvenirs; }
    double getTotalCost() const;
    QString getSouvenirsSummary() const;
    
    // Utility methods
    void exportToTable(QTableWidget* table) const;

signals:
    void souvenirAdded();
    void souvenirRemoved();
    void quantityChanged();

private:
    QVector<TripSouvenir> selectedSouvenirs;
};

#endif // SOUVENIRTRIPMANAGER_H 