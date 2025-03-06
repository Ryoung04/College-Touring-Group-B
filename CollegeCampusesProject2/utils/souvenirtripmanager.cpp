#include "souvenirtripmanager.h"
#include <QTableWidgetItem>
#include <QPushButton>
#include <QHeaderView>

SouvenirTripManager::SouvenirTripManager(QObject *parent)
    : QObject(parent)
{
}

void SouvenirTripManager::addSouvenir(const QString &collegeName, const QString &name, double price)
{
    // Check if the souvenir already exists
    for (int i = 0; i < selectedSouvenirs.size(); i++) {
        if (selectedSouvenirs[i].collegeName == collegeName && selectedSouvenirs[i].name == name) {
            // If it exists, just increment the quantity
            selectedSouvenirs[i].quantity++;
            emit quantityChanged();
            return;
        }
    }
    
    // If it doesn't exist, add a new one
    TripSouvenir souvenir(collegeName, name, price);
    
    selectedSouvenirs.append(souvenir);
    emit souvenirAdded();
}

void SouvenirTripManager::removeSouvenir(int index)
{
    if (index >= 0 && index < selectedSouvenirs.size()) {
        selectedSouvenirs.remove(index);
        emit souvenirRemoved();
    }
}

void SouvenirTripManager::clearSouvenirs()
{
    selectedSouvenirs.clear();
    emit souvenirRemoved();
}

void SouvenirTripManager::updateQuantity(int index, int quantity)
{
    if (index >= 0 && index < selectedSouvenirs.size() && quantity > 0) {
        selectedSouvenirs[index].quantity = quantity;
        emit quantityChanged();
    } else if (index >= 0 && index < selectedSouvenirs.size() && quantity <= 0) {
        // If quantity is set to 0 or negative, remove the souvenir
        removeSouvenir(index);
    }
}

double SouvenirTripManager::getTotalCost() const
{
    double total = 0.0;
    for (const TripSouvenir &souvenir : selectedSouvenirs) {
        total += souvenir.totalPrice();
    }
    return total;
}

QString SouvenirTripManager::getSouvenirsSummary() const
{
    QString summary;
    
    if (selectedSouvenirs.isEmpty()) {
        return "No souvenirs added to trip.";
    }
    
    summary = "Souvenirs:\n";
    
    double total = 0.0;
    for (const TripSouvenir &souvenir : selectedSouvenirs) {
        summary += QString("- %1 from %2: $%3 x %4 = $%5\n")
                    .arg(souvenir.name)
                    .arg(souvenir.collegeName)
                    .arg(souvenir.price, 0, 'f', 2)
                    .arg(souvenir.quantity)
                    .arg(souvenir.totalPrice(), 0, 'f', 2);
        
        total += souvenir.totalPrice();
    }
    
    summary += QString("\nTotal: $%1").arg(total, 0, 'f', 2);
    
    return summary;
}

void SouvenirTripManager::exportToTable(QTableWidget *table) const
{
    if (!table) return;
    
    table->setRowCount(selectedSouvenirs.size());
    
    if (table->columnCount() < 5) {
        table->setColumnCount(5);
        table->setHorizontalHeaderLabels({"College", "Souvenir", "Price", "Quantity", "Total"});
    }
    
    for (int i = 0; i < selectedSouvenirs.size(); i++) {
        const TripSouvenir &souvenir = selectedSouvenirs[i];
        
        table->setItem(i, 0, new QTableWidgetItem(souvenir.collegeName));
        table->setItem(i, 1, new QTableWidgetItem(souvenir.name));
        table->setItem(i, 2, new QTableWidgetItem(QString("$%1").arg(souvenir.price, 0, 'f', 2)));
        table->setItem(i, 3, new QTableWidgetItem(QString::number(souvenir.quantity)));
        table->setItem(i, 4, new QTableWidgetItem(QString("$%1").arg(souvenir.totalPrice(), 0, 'f', 2)));
    }
    
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
} 