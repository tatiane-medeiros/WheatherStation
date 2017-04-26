#ifndef TABLE_H
#define TABLE_H
#include <QDate>
#include <QVector>
#include <QFile>
#include <QDebug>
#include "line.h"

class Table
{
private:
    QList<Line> lines;

public:
    Table();
    ~Table();

    void readData();

};

#endif // TABLE_H
