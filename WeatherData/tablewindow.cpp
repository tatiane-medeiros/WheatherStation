#include "tablewindow.h"
#include "ui_tablewindow.h"

TableWindow::TableWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TableWindow)
{
    ui->setupUi(this);
    myTable = new Table();

}

TableWindow::~TableWindow()
{
    delete ui;
}

void TableWindow::setTable(Table *t)
{
    myTable = t;
  // qDebug()<<"yes" << t->vec.at(0).data() << myTable->vec.at(0).data();
}

void TableWindow::createTable(QDate start, QDate end)
{
    //create table from data
    setWindowTitle("Tabela");
    ui->tableWidget->setColumnCount(19);
    QStringList names;
    names << "data"<<"hora"<<"temp. inst (ºC)"<<"temp max"<<"temp min" <<"umid. inst (%)" <<"umid max" <<"umid min" <<"pto. orvalho (ºC)" <<"pto. orv. max"
         <<"pto. orv. min"<<"pressao (hPa)"<<"pressao max"<<"pressao min"<<"dir. vento"<<"vel. vento(m/s)"<<"rajada"<<"radiacao(kJ/m²)"<<"chuva (mm)";
    ui->tableWidget->setHorizontalHeaderLabels(names);

    QVector<Line> lines =  myTable->selectFromDate(start, end);

    for(int i =0; i< lines.size(); i++){
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(i,0, new QTableWidgetItem(lines.at(i).data()));
         ui->tableWidget->setItem(i,1, new QTableWidgetItem(lines.at(i).hora()));

        for(int j =0; j<17; j++){
            ui->tableWidget->setItem(i,j+2, new QTableWidgetItem(QString::number(lines.at(i).getVariable(j))));
        }
    }
     ui->tableWidget->resizeColumnsToContents();
}
