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
            qDebug() <<aux;

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

            lines.append(curr);
            vec.append(curr);
           // curr.printL();
      }

}

void Table::setDailyData()
{
    QDate curr;
    QVector<double> lineData;
    QVector<double> line;
    bool reset = true;

     for(int i=0; i<vec.count(); ++i){

         if(reset){
             curr = vec.at(i).getDate();

             line.clear();
             lineData.clear();
             lineData.resize(5);
             reset = false;

         }
         lineData[0] += vec.at(i).getVariable(0);    //temp.
         lineData[1] += vec.at(i).getVariable(3);    //umid.
         lineData[2] += vec.at(i).getVariable(6);    //pto. orvalho
         lineData[3] += vec.at(i).getVariable(9);    //pressão
         lineData[4] += vec.at(i).getVariable(16);   //chuva

         if(vec.at(i).getHour() == 0){
             line << lineData[0]/24 << lineData[1]/24 << lineData[2]/24 << lineData[3]/24 << lineData[4];
             dailyData.insert(curr, line);
             reset = true;
         }

     }
}



void Table::selectFromDate(QDate start, QDate end)
{
    for(int i=0; i<vec.count(); ++i){
        if((vec.at(i).getDate() >= start) && (vec.at(i).getDate() <= end)){
            qDebug()<< vec.at(i).data()<<" "<<vec.at(i).hora();
        }
        //parar quando passar do intervalo
    }

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
