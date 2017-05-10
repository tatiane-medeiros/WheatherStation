#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include "table.h"
#include "tablewindow.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

//        Table *t = new Table();
//       t->readData();
//        t->setDailyData();
//        qDebug() << t->humidMonth(5,2017);

    return a.exec();
}
