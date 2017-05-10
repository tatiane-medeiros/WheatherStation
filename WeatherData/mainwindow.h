#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tablewindow.h"

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

protected:
    void  closeEvent(QCloseEvent*);

private:
    Ui::MainWindow *ui;
    TableWindow *myTableWindow;
};

#endif // MAINWINDOW_H
