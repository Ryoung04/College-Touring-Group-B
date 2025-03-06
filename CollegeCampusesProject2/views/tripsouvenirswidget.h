#ifndef TRIPSOUVENIRSWIDGET_H
#define TRIPSOUVENIRSWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QVector>

// Define the TripSouvenir struct directly here instead of using AdminPanel
struct TripSouvenir {
    QString collegeName;
    QString name;
    double price;
    int quantity;
    
    TripSouvenir(const QString& college, const QString& souvenirName, double souvenirPrice, int qty = 1)
        : collegeName(college), name(souvenirName), price(souvenirPrice), quantity(qty) {}
        
    double totalPrice() const { return price * quantity; }
};

class TripSouvenirsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TripSouvenirsWidget(QWidget* parent = nullptr);

    // Methods to manage souvenirs
    void addSouvenir(const QString& collegeName, const QString& souvenirName, double price);
    void clearSouvenirs();
    void refreshSouvenirs();
    double getTotalCost() const;
    QVector<TripSouvenir> getSelectedSouvenirs() const { return m_selectedSouvenirs; }
    QString getSelectedSouvenirsSummary() const;

signals:
    void souvenirsChanged();

private slots:
    void onViewDetailsClicked();
    void onClearAllClicked();
    void onRemoveSouvenirClicked();

private:
    QTableWidget* m_souvenirsTable;
    QLabel* m_totalCostLabel;
    QPushButton* m_viewDetailsButton;
    QPushButton* m_clearAllButton;
    QVector<TripSouvenir> m_selectedSouvenirs;
    
    void setupUI();
    void updateTotalCostLabel();
    void populateSouvenirsTable();
};

#endif // TRIPSOUVENIRSWIDGET_H 