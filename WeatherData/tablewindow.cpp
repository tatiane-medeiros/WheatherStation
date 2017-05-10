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
    names << "data"<<"hora"<<"temp. inst (ºC)"<<"temp max"<<"temp min" <<"umid. inst (%)" <<"umid max" <<"umid min" <<"pto. orvalho (ºC)" <<"pto. orv. max"
         <<"pto. orv. min"<<"pressao (hPa)"<<"pressao max"<<"pressao min"<<"dir. vento"<<"vel. vento(m/s)"<<"rajada"<<"radiacao(kJ/m²)"<<"chuva (mm)";
    ui->tableWidget->setHorizontalHeaderLabels(names);

    Table *t = new Table();
    t->readData();

    for(int i =0; i< t->vec.size(); i++){
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(i,0, new QTableWidgetItem(t->vec.at(i).data()));
         ui->tableWidget->setItem(i,1, new QTableWidgetItem(t->vec.at(i).hora()));

        for(int j =0; j<17; j++){
            ui->tableWidget->setItem(i,j+2, new QTableWidgetItem(QString::number( t->vec.at(i).getVariable(j))));
        }
    }
     ui->tableWidget->resizeColumnsToContents();
}
