#include <QCoreApplication>
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "table.h"
#include "tablewindow.h"

int main(int argc, char *argv[])
{
   // QCoreApplication a(argc, argv);

//    Table *t = new Table();
//    t->readData();
//    qDebug()<< t->vec.at(1).data();
//    qDebug()<< t->vec.at(1).colums[0];
    QApplication a(argc, argv);
    TableWindow w;
    w.show();

    return a.exec();
}
