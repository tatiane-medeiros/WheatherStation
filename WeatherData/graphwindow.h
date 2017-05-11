#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include <QTimer>
#include "table.h"


namespace Ui {
class GraphWindow;
}

class GraphWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GraphWindow(QWidget *parent = 0);
    ~GraphWindow();
    void setTable(Table *t);
      void createChart(int type, QVector<double> data, QVector<QString> labels, QString name, int min, int max);

protected:
    void paintEvent();
    void barChart(QCustomPlot *customPlot, QVector<double> data, QVector<QString> labels, QString name, int min, int max);
    void lineChart(QCustomPlot *customPlot, QVector<double> data, QVector<QString> labels, QString name, int min, int max);

private slots:
  void realtimeDataSlot();
  void bracketDataSlot();
  void screenShot();
  void allScreenShots();

  void on_saveImage_clicked();


private:
    Ui::GraphWindow *ui;
    QString demoName;
    QTimer dataTimer;
    QCPItemTracer *itemDemoPhaseTracer;
    int currentDemoIndex;
    Table *myTable;
};

#endif // GRAPHWINDOW_H
