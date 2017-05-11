#ifndef TABLEWINDOW_H
#define TABLEWINDOW_H

#include <QMainWindow>
#include "table.h"

namespace Ui {
class TableWindow;
}

class TableWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TableWindow(QWidget *parent = 0);
    ~TableWindow();
    void setTable(Table *t);

    void createTable();

private:
    Ui::TableWindow *ui;
    Table *myTable;

};

#endif // TABLEWINDOW_H
