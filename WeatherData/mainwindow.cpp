#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myTableWindow = new TableWindow();
    ui->dateEdit->setMinimumDate(QDate(2017,01,01));
    ui->dateEdit->setMaximumDate(QDate(2017,05,10));
    ui->dateEdit_2->setMinimumDate(QDate(2017,01,01));
    ui->dateEdit_2->setMaximumDate(QDate(2017,05,10));
    ui->dateEdit->setDate(QDate(2017,05,10));

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
    myTableWindow->setTable(myTable);
    myTableWindow->createTable();
    myTableWindow->show();

}

void   MainWindow::closeEvent(QCloseEvent*)
{
    // close all windows on exit
    qApp->quit();
}

//create line chart
void MainWindow::on_lineChartButton_clicked()
{
    myGraph = new GraphWindow();
    myTable->setDailyData();
    QVector<double> temp = myTable->temperatureMonth(5,2017);
    QVector<QString> labels = myTable->datesLabels(1,5,2017,temp.count());
    myGraph->createChart(1,temp, labels, "temperatura",0,40);
    myGraph->show();
}

//create bar chart
void MainWindow::on_barChartButton_clicked()
{

}
