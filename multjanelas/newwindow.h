#ifndef NEWWINDOW_H
#define NEWWINDOW_H

#include <QMainWindow>
#include "data.h"

namespace Ui {
class NewWindow;
}

class NewWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewWindow(QWidget *parent = 0);
    ~NewWindow();
protected:
    void paintEvent();
    void createTable();

private slots:
    void on_saveImage_clicked();

private:
    Ui::NewWindow *ui;
};

#endif // NEWWINDOW_H
