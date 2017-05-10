#ifndef WEATHERDATA_H
#define WEATHERDATA_H
#include <QDebug>
#include <QVector>

class weatherData
{
public:
    weatherData();
    ~weatherData();

    QVector<double> temperature;
    QVector<QString> datas;
    QVector<double> pressure;

};

#endif // WEATHERDATA_H
