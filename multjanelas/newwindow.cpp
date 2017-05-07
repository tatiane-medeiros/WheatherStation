#include "newwindow.h"
#include "ui_newwindow.h"

NewWindow::NewWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewWindow)
{
    ui->setupUi(this);
    createTable();
}

NewWindow::~NewWindow()
{
    delete ui;
}


void NewWindow::paintEvent() {
         QPixmap pixmap(this->size());
         this->render(&pixmap);
         pixmap.save("test.png");

}

void NewWindow::createTable()
{
    //create table from data
    setWindowTitle("Tabela");
    ui->tableWidget->setColumnCount(3);
    QStringList names;
    names << "um"<<"dois"<<"tres";
    ui->tableWidget->setHorizontalHeaderLabels(names);
    Data *d = new Data();
    for(int i =0; i< d->v.count(); i++){
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        for(int j =0; j<3; j++){
            ui->tableWidget->setItem(i,j, new QTableWidgetItem(d->v.at(i).at(j)));
        }
    }
}

void NewWindow::on_saveImage_clicked()
{
    ui->saveImage->setVisible(false);
    this->paintEvent();
}
