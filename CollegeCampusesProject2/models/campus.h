#ifndef CAMPUS_H
#define CAMPUS_H

#include <QString>

class Campus {
public:
    Campus();
    Campus(int id, const QString& name, const QString& state, 
           int undergraduateCount, const QString& startingDate,
           const QString& location);

    int getId() const { return campusId; }
    QString getName() const { return name; }
    QString getState() const { return state; }
    int getUndergraduateCount() const { return undergraduateCount; }
    QString getStartingDate() const { return startingDate; }
    QString getLocation() const { return location; }

    void setId(int id) { campusId = id; }
    void setName(const QString& n) { name = n; }
    void setState(const QString& s) { state = s; }
    void setUndergraduateCount(int count) { undergraduateCount = count; }
    void setStartingDate(const QString& date) { startingDate = date; }
    void setLocation(const QString& loc) { location = loc; }

private:
    int campusId;
    QString name;
    QString state;
    int undergraduateCount;
    QString startingDate;
    QString location;
};

#endif // CAMPUS_H 