#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mMyNewWindow = new NewWindow();

}

MainWindow::~MainWindow()
{
    delete mMyNewWindow;
    delete ui;
}

void MainWindow::openNewWindow()
{
   mMyNewWindow = new NewWindow();
   mMyNewWindow->show();

}

void MainWindow::on_myButton_clicked()
{
    //close old second window and open a new
    mMyNewWindow->close();
    mMyNewWindow = new NewWindow();
    mMyNewWindow->show();

}

void   MainWindow::closeEvent(QCloseEvent*)
{
    // close all windows on exit
    qApp->quit();
}
