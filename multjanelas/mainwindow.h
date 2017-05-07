#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "newwindow.h"

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
    void on_myButton_clicked();
    void openNewWindow();

protected:
void  closeEvent(QCloseEvent*);

private:
    Ui::MainWindow *ui;
    NewWindow *mMyNewWindow;
};

#endif // MAINWINDOW_H
