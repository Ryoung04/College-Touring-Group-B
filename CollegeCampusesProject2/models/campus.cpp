#include "campus.h"

Campus::Campus() : campusId(0), undergraduateCount(0)
{
}

Campus::Campus(int id, const QString& name, const QString& state, 
               int undergraduateCount, const QString& startingDate,
               const QString& location)
    : campusId(id)
    , name(name)
    , state(state)
    , undergraduateCount(undergraduateCount)
    , startingDate(startingDate)
    , location(location)
{
} 