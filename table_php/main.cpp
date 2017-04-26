#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "table.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
//    QFile file("meteorology.php");
//    Q_ASSERT_X(file.open(QIODevice::ReadOnly), "error:", "file not found.");

//   // while (!file.atEnd()) {
//        file.read(189);
//        //221 titulos colunas
//        //A303 inicio linha ?????
//        //não sei o que to fazendo da minha vida
//         QByteArray data = file.read(14);
//         qDebug() << data  <<endl;

//         data = file.read(5);
//          qDebug() << data  <<endl;
    Table t;
    t.readData();

    return 0;
}
