#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tablewindow.h"
#include "graphwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_tableButton_clicked();

    void on_lineChartButton_clicked();

    void on_barChartButton_clicked();

protected:
    void closeEvent(QCloseEvent*);
    void settings();
    void showMessage();

private:
    Ui::MainWindow *ui;
    TableWindow *myTableWindow;
    Table *myTable;
    GraphWindow *myGraph;
};

#endif // MAINWINDOW_H
