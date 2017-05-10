#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myTableWindow = new TableWindow();
}

MainWindow::~MainWindow()
{
    delete myTableWindow;
    delete ui;
}


void MainWindow::on_tableButton_clicked()
{

    QMessageBox *msgBox  = new QMessageBox();
            msgBox->setWindowTitle("Mensagem");
            msgBox->setText("olá");
            msgBox->show();


    //open new table window
    myTableWindow->close();
    myTableWindow = new TableWindow();
    myTableWindow->show();

}

void   MainWindow::closeEvent(QCloseEvent*)
{
    // close all windows on exit
    qApp->quit();
}
