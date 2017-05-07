#include "tablewindow.h"
#include "ui_tablewindow.h"

TableWindow::TableWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TableWindow)
{
    ui->setupUi(this);
    createTable();
}

TableWindow::~TableWindow()
{
    delete ui;
}

void TableWindow::createTable()
{
    //create table from data
    setWindowTitle("Tabela");
    ui->tableWidget->setColumnCount(19);
    QStringList names;
     //temp_inst,temp_max,temp_min,umid_inst,umid_max,umid_min,
    //pto_orvalho_inst,pto_orvalho_max,pto_orvalho_min,pressao,pressao_max,pressao_min,vento_direcao,vento_vel, vento_rajada,radiacao,precipitacao
    names << "data"<<"hora"<<"temp. inst"<<"temp max"<<"temp min" <<"umid. inst" <<"umid max" <<"umid min" <<"pto. orvalho" <<"pto. orv. max"
         <<"pto. orv. min"<<"pressao"<<"pressao max"<<"pressao min"<<"dir. vento"<<"vel. vento"<<"rajada"<<"radiacao"<<"precipitacao";
    ui->tableWidget->setHorizontalHeaderLabels(names);
   //insetLayout()->setInsetAlignment(0, Qt::AlignBottom|Qt::AlignRight);

    Table *t = new Table();
    t->readData();

    for(int i =0; i< t->lines.size(); i++){
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(i,0, new QTableWidgetItem(t->lines.at(i).data()));
         ui->tableWidget->setItem(i,1, new QTableWidgetItem(t->lines.at(i).hora()));

        for(int j =0; j<17; j++){
            ui->tableWidget->setItem(i,j+2, new QTableWidgetItem(QString::number( t->lines.at(i).colums[j])));
        }
    }
     ui->tableWidget->resizeColumnsToContents();
}
