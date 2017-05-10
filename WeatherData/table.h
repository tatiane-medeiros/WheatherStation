#ifndef TABLE_H
#define TABLE_H
#include <QDate>
#include <QVector>
#include <QHash>
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
    //dados diarios: temp. media, umid. media, pressão media, pto. orvalho, chuva.
    QHash<QDate, QVector<double> > dailyData;
    void readData();
    void setDailyData();
    void selectFromDate(QDate start, QDate end);
    void printDailyData();
    QVector<double> selectDailyData(int index, int m, int y);
    QVector<double> temperatureMonth(int m, int y);
    QVector<double> pressureMonth(int m, int y);
    QVector<double> humidMonth(int m, int y);
    QVector<double> dewMonth(int m, int y);
    QVector<double> rainMonth(int m, int y);

};

#endif // TABLE_H
