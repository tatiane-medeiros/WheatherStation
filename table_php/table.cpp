#include "table.h"


Table::Table()
{

    //double temp_inst,temp_max,temp_min,umid_inst,umid_max,umid_min,pto_orvalho_inst,pto_orvalho_max,pto_orvalho_min,pressao,pressao_max,pressao_min,vento_direcao,vento_vel, vento_rajada,radiacao,precipitacao;
}

Table::~Table()
{

}

void Table::readData()
{
    QByteArray aux, ch;
    Line curr;
    int i = 0;
    QFile file("meteorology.php");
    Q_ASSERT_X(file.open(QIODevice::ReadOnly), "error:", "file not found.");

        file.read(412);//221 titulos colunas

        while (!file.atEnd()) {
            i=0;
            ch = file.read(9);
            if(!ch.contains("<br>A303")) break;
            aux = file.read(10);    //Lê a data da linha atual
            curr.m_data = curr.m_data.fromString(QString(aux), "dd/MM/yyyy");

            file.read(1);
            aux.clear();
            aux = file.read(2); //Lê a hora da linha atual
            curr.m_hora = aux.toInt();
            file.read(1);
            aux.clear();

            for(i=0; i<3; ++i){     //Valores de Temperatura
            aux = file.read(4);
            curr.colums[i] = aux.toDouble();

            file.read(1);
            }
            for(i=3; i<6; ++i){      //Valores de Umidade
            aux = file.read(2);
            curr.colums[i] = aux.toDouble();

            file.read(1);
            }
            for(i=6; i<9; ++i){      //Valores do ponto de orvalho
            aux = file.read(4);
            curr.colums[i] = aux.toDouble();

            file.read(1);
            }
            for(i=9; i<12; ++i){      //Valores da Pressão
            aux = file.read(6);
            curr.colums[i] = aux.toDouble();

            file.read(1);
            }

            aux = file.read(3);      // Velocidade do vento
            curr.colums[i] = aux.toDouble();

            file.read(1);
            aux.clear();
            i++;
            while (ch != ",") {
                ch = file.read(1);
                if(ch != ",") aux.append(ch);
            }
            ch.clear();
            curr.colums[i] = aux.toDouble();    //Direção do vento (ºC)

            i++;
            aux = file.read(3);     // Rajada
            curr.colums[i] = aux.toDouble();

            file.read(1);
            aux.clear();
            i++;
            while (ch != ",") {
                ch = file.read(1);
                if(ch != ",") aux.append(ch);
            }
            ch.clear();
            curr.colums[i] = aux.toDouble();   //Radiação

            i++;
            aux = file.read(3);
            curr.colums[i] = aux.toDouble();    //Chuva (mm)

            lines.append(curr);
            vec.append(curr);
           // curr.printL();
      }

}

