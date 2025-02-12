#pragma once

#include <QString>
#include <QMap>
#include <QSet>

class CSVParser
{
public:
    CSVParser();
    QPair<QMap<QString, QMap<QString, double>>, QSet<QString>> parseCollegeData();

private:
    QString collegeData;
};
