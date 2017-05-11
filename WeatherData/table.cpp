#include "table.h"

Table::Table()
{

}

Table::~Table()
{

}

void Table::readData()
{
    QByteArray aux, ch;
    Line curr;
    int i = 0;
    QFile file("data.php");
    Q_ASSERT_X(file.open(QIODevice::ReadOnly), "error:", "file not found.");

        file.read(412);//221 titulos colunas
        file.read(1);
        while (!file.atEnd()) {
            i=0;
            ch = file.read(8);
            if(!ch.contains("br>A303")) break;
            aux = file.read(10);    //Lê a data da linha atual
            curr.setDate(QDate::fromString(QString(aux), "dd/MM/yyyy"));

            file.read(1);
            aux.clear();
            aux = file.read(2); //Lê a hora da linha atual
            curr.setHour(aux.toInt());
            file.read(1);
            aux.clear();

            for(i=0; i<3; ++i){     //Valores de Temperatura
            aux = file.read(4);
            curr.setVariable(i, aux.toDouble());

            file.read(1);
            }
            for(i=3; i<6; ++i){      //Valores de Umidade
            aux = file.read(2);
             curr.setVariable(i, aux.toDouble());

            file.read(1);
            }
            for(i=6; i<9; ++i){      //Valores do ponto de orvalho
            aux = file.read(4);
             curr.setVariable(i, aux.toDouble());

            file.read(1);
            }
            for(i=9; i<12; ++i){      //Valores da Pressão
            aux = file.read(6);
            curr.setVariable(i, aux.toDouble());

            file.read(1);
            }

            aux = file.read(3);      // Velocidade do vento
            curr.setVariable(i, aux.toDouble());

            file.read(1);
            aux.clear();
            i++;
            while (ch != ",") {
                ch = file.read(1);
                if(ch != ",") aux.append(ch);
            }
            ch.clear();
            curr.setVariable(i, aux.toDouble());    //Direção do vento (ºC)
            aux.clear();

            i++;
            while (ch != ",") {
                ch = file.read(1);
                if(ch != ",") aux.append(ch);
            }

            curr.setVariable(i, aux.toDouble()); // Rajada
            ch.clear();
            aux.clear();

            file.read(1);
            aux.clear();
            i++;
            while (ch != ",") {
                ch = file.read(1);
                if(ch != ",") aux.append(ch);
            }
            ch.clear();
           curr.setVariable(i, aux.toDouble());   //Radiação
            aux.clear();

            i++;
            while (ch != "<") {
                ch = file.read(1);
                if(ch != "<") aux.append(ch);
            }

            curr.setVariable(i, aux.toDouble());    //Chuva (mm)
            vec.append(curr);

      }

}

void Table::setDailyData()
{
    QDate curr;
    QVector<double> lineData;
    QVector<double> line;
    int count = 0;
    bool reset = true;

     for(int i=0; i<vec.count(); ++i){

         if(reset){
             curr = vec.at(i).getDate();

             line.clear();
             lineData.clear();
             lineData.resize(5);
             count = 0;
             reset = false;

         }
         lineData[0] += vec.at(i).getVariable(0);    //temp.
         lineData[1] += vec.at(i).getVariable(3);    //umid.
         lineData[2] += vec.at(i).getVariable(6);    //pto. orvalho
         lineData[3] += vec.at(i).getVariable(9);    //pressão
         lineData[4] += vec.at(i).getVariable(16);   //chuva
         count++;

         if(count == 24){
             line << lineData[0]/24 << lineData[1]/24 << lineData[2]/24 << lineData[3]/24 << lineData[4];
             dailyData.insert(curr, line);
             reset = true;
         }

     }
}



QVector<Line> Table::selectFromDate(QDate start, QDate end)
{
    QVector<Line> select;
    Line aux;
    for(int i=0; i<vec.count(); ++i){
        aux = vec.at(i);

        if((aux.getDate() >= start) && (aux.getDate() <= end) ){
            select.append(aux);

        }

         //parar quando passar do intervalo
        else if(aux.getDate() > end)   break;
    }

       return select;

}

void Table::printDailyData()
{
    QHash<QDate, QVector<double> >::Iterator i;
   // n = dailyData.begin();
    for (i = dailyData.begin(); i != dailyData.end(); ++i){
        QDate d = i.key();
           std::cout << d.toString().toStdString() << ": " << dailyData[i.key()].at(0)<< std::endl;
    }


}

QString Table::toStringMonth(int m)
{
    QString name;
    switch (m) {
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

QVector<double> Table::selectDailyData(int index, int m, int y)
{
    QVector<double> temp;
    QDate d;
    d.setDate(y,m,1);
    while (d.month() == m) {
        if(dailyData.contains(d)){
            temp << dailyData[d].at(index);
        }
        else if(dailyData.end().key() == d) break;

        d =d.addDays(1);

    }

    return temp;
}

QVector<double> Table::temperatureMonth(int m, int y)
{
   return selectDailyData(0,m,y);

}

QVector<double> Table::pressureMonth(int m, int y)
{
    return selectDailyData(3,m,y);
}

QVector<double> Table::humidMonth(int m, int y)
{
    return selectDailyData(1,m,y);
}

QVector<double> Table::dewMonth(int m, int y)
{
    return selectDailyData(2,m,y);
}

QVector<double> Table::rainMonth(int m, int y)
{
    return selectDailyData(4,m,y);
}

QVector<QString> Table::datesLabels(int d, int m, int y, int size)
{
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
