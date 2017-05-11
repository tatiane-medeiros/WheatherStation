#ifndef DATAFUNCTIONS
#define DATAFUNCTIONS
#include <QDebug>
#include <QDate>
//#include "table.h"

QString monthName(int n){
    QString name;
    switch (n) {
    case 1:
        name.append("janeiro");
        break;
    case 2:
        name.append("fevereiro");
        break;
    case 3:
        name.append("março");
        break;
    case 4:
        name.append("abril");
        break;
    case 5:
        name.append("maio");
        break;
    case 6:
        name.append("junho");
        break;
    case 7:
        name.append("julho");
        break;
    case 8:
        name.append("agosto");
        break;
    case 9:
        name.append("setembro");
        break;
    case 10:
        name.append("outubro");
        break;
    case 11:
        name.append("novembro");
        break;
    case 12:
        name.append("dezembro");
        break;
    default:
        break;
    }
    return name;
}

QVector<QString> datesLabels(int d, int m, int y, int size){
    QVector<QString> temp;
    QDate a;
    QString date;
    a.setDate(y,m,d);
    for(int i =0; i<size; ++i) {
        date.append(QString::number(a.day()).rightJustified(2,'0') + "/" + QString::number(a.month()).rightJustified(2,'0') + "/"+ QString::number(a.year()));
        temp.append(date);
        date.clear();
        a =a.addDays(1);

    }

    return temp;
}


#endif // DATAFUNCTIONS
