#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
     void setupBarChartDemo(QCustomPlot *customPlot);


private slots:
  void realtimeDataSlot();
  void bracketDataSlot();
  void screenShot();
  void allScreenShots();

private:
    Ui::MainWindow *ui;
    QString demoName;
    QTimer dataTimer;
    QCPItemTracer *itemDemoPhaseTracer;
    int currentDemoIndex;
};

#endif // MAINWINDOW_H
