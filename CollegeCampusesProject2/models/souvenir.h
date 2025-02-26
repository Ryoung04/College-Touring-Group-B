#ifndef SOUVENIR_H
#define SOUVENIR_H

#include <QString>

class Souvenir {
public:
    Souvenir();
    Souvenir(int id, int campusId, const QString& name, double price, 
             int quantity, const QString& category);

    int getId() const { return souvenirId; }
    int getCampusId() const { return campusId; }
    QString getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }
    QString getCategory() const { return category; }

    void setId(int id) { souvenirId = id; }
    void setCampusId(int id) { campusId = id; }
    void setName(const QString& n) { name = n; }
    void setPrice(double p) { price = p; }
    void setQuantity(int q) { quantity = q; }
    void setCategory(const QString& c) { category = c; }

private:
    int souvenirId;
    int campusId;
    QString name;
    double price;
    int quantity;
    QString category;
};

#endif // SOUVENIR_H 