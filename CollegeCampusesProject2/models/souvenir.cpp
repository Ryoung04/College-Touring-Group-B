#include "souvenir.h"

Souvenir::Souvenir() 
    : souvenirId(0), campusId(0), price(0.0), quantity(0)
{
}

Souvenir::Souvenir(int id, int campusId, const QString& name, 
                   double price, int quantity, const QString& category)
    : souvenirId(id)
    , campusId(campusId)
    , name(name)
    , price(price)
    , quantity(quantity)
    , category(category)
{
} 