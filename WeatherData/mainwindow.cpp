#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Visualização de Dados Meteorológicos");
    myTableWindow = new TableWindow();
    settings();
    myTable = new Table();
    myTable->readData();
}

MainWindow::~MainWindow()
{
    delete myTable;
    delete myTableWindow;
    delete ui;
}


void MainWindow::on_tableButton_clicked()
{

    //open new table window
    myTableWindow->close();    
    myTableWindow = new TableWindow();
    QDate start = ui->dateEdit->date();
    QDate end = ui->dateEdit_2->date();
    myTableWindow->setTable(myTable);
    myTableWindow->createTable(start, end);
    myTableWindow->show();

}

void   MainWindow::closeEvent(QCloseEvent*)
{
    // close all windows on exit
    qApp->quit();
}

void MainWindow::settings()
{
    ui->dateEdit->setMinimumDate(QDate(2017,01,01));
    ui->dateEdit->setMaximumDate(QDate(2017,05,10));
    ui->dateEdit_2->setMinimumDate(QDate(2017,01,01));
    ui->dateEdit_2->setMaximumDate(QDate(2017,05,10));
    ui->dateEdit_2->setDate(QDate(2017,05,10));
    ui->spinBox->setMinimum(1);
    ui->spinBox->setMaximum(5);

}

void MainWindow::showMessage()
{
    QMessageBox *msgBox  = new QMessageBox();
          msgBox->setWindowTitle("Inválido");
          msgBox->setText("Selecione uma opção.");
          msgBox->show();
}

//create line chart
void MainWindow::on_lineChartButton_clicked()
{
    myGraph = new GraphWindow();
    myTable->setDailyData();
    int m = ui->spinBox->value();
    int max, min;
    QVector<double> temp;
    QVector<QString> labels;
    QString name;
    if(ui->radioButtonTemp->isChecked()){
        temp = myTable->temperatureMonth(m,2017);
        name = "Temperatura";
        min = 0;
        max = 40;

    }
    else  if(ui->radioButtonPress->isChecked()){
        temp = myTable->pressureMonth(m,2017);
        name = "Pressão";
        min = 1000;
        max = 1010;
    }
    else  if(ui->radioButtonHumid->isChecked()){
        temp = myTable->humidMonth(m,2017);
        name = "Umidade";
        min = 50;
        max = 100;
    }
    else  if(ui->radioButtonDew->isChecked()){
        temp = myTable->dewMonth(m,2017);
        name = "Ponto de orvalho";
        min = 0;
        max = 30;
    }
    else  if(ui->radioButtonRain->isChecked()){
        temp = myTable->rainMonth(m,2017);
        name = "Chuva acumulada";
        min = 0;
        max = 40;
    }
    else{
        showMessage();
        m = 0;
    }

    if(m != 0){
        myGraph->setWindowTitle("Gráfico da " +name+ " no mês de " + myTable->toStringMonth(m));
        labels = myTable->datesLabels(1,m,2017,temp.count());
        myGraph->createChart(1,temp, labels, name,0,0);
        myGraph->show();
    }


}

//create bar chart
void MainWindow::on_barChartButton_clicked()
{

    myGraph = new GraphWindow();
    myTable->setDailyData();
    int m = ui->spinBox->value();
    int max, min;
    QVector<double> temp;
    QVector<QString> labels;
    QString name;
    if(ui->radioButtonTemp->isChecked()){
        temp = myTable->temperatureMonth(m,2017);
        name = "Temperatura";
        min = 0;
        max = 40;
    }
    else  if(ui->radioButtonPress->isChecked()){
        temp = myTable->pressureMonth(m,2017);
        name = "Pressão";
        min = 950;
        max = 1010;
    }
    else  if(ui->radioButtonHumid->isChecked()){
        temp = myTable->humidMonth(m,2017);
        name = "Umidade";
        min = 50;
        max = 100;
    }
    else  if(ui->radioButtonDew->isChecked()){
        temp = myTable->dewMonth(m,2017);
        name = "Ponto de orvalho";
        min = 0;
        max = 30;
    }
    else  if(ui->radioButtonRain->isChecked()){
        temp = myTable->rainMonth(m,2017);
        name = "Chuva acumulada";
        min = 0;
        max = 40;
    }
    else{
        showMessage();
        m = 0;
    }

    if(m != 0){
         myGraph->setWindowTitle("Gráfico da " +name+ " no mês de " + myTable->toStringMonth(m));
        labels = myTable->datesLabels(1,m,2017,temp.count());
        myGraph->createChart(0,temp, labels, name,min, max);
        myGraph->show();
    }

}
