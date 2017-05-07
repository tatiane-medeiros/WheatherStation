#ifndef TABLE_H
#define TABLE_H
#include <QDate>
#include <QVector>
#include <QFile>
#include <QDebug>
#include "line.h"

class Table
{
public:
    Table();
    ~Table();
    QList<Line> lines;
    QVector<Line> vec;
    void readData();

};

#endif // TABLE_H
