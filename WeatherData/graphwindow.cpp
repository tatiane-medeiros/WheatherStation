#include "graphwindow.h"
#include "ui_graphwindow.h"

GraphWindow::GraphWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphWindow)
{
    ui->setupUi(this);
}

GraphWindow::~GraphWindow()
{
    delete ui;
}


void GraphWindow::setTable(Table *t)
{
    myTable = t;
}



// gui functions
void GraphWindow::realtimeDataSlot()
{
  static QTime time(QTime::currentTime());
  // calculate two new data points:
  double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
  static double lastPointKey = 0;
  if (key-lastPointKey > 0.002) // at most add point every 2 ms
  {
    // add data to lines:
    ui->customPlot->graph(0)->addData(key, qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843));
    ui->customPlot->graph(1)->addData(key, qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364));
    // rescale value (vertical) axis to fit the current data:
    //ui->customPlot->graph(0)->rescaleValueAxis();
    //ui->customPlot->graph(1)->rescaleValueAxis(true);
    lastPointKey = key;
  }
  // make key axis range scroll with the data (at a constant range size of 8):
  ui->customPlot->xAxis->setRange(key, 8, Qt::AlignRight);
  ui->customPlot->replot();

  // calculate frames per second:
  static double lastFpsKey;
  static int frameCount;
  ++frameCount;
  if (key-lastFpsKey > 2) // average fps over 2 seconds
  {
    ui->statusBar->showMessage(
          QString("%1 FPS, Total Data points: %2")
          .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
          .arg(ui->customPlot->graph(0)->data()->size()+ui->customPlot->graph(1)->data()->size())
          , 0);
    lastFpsKey = key;
    frameCount = 0;
  }
}

void GraphWindow::bracketDataSlot()
{
  double secs = QCPAxisTickerDateTime::dateTimeToKey(QDateTime::currentDateTime());

  // update data to make phase move:
  int n = 500;
  double phase = secs*5;
  double k = 3;
  QVector<double> x(n), y(n);
  for (int i=0; i<n; ++i)
  {
    x[i] = i/(double)(n-1)*34 - 17;
    y[i] = qExp(-x[i]*x[i]/20.0)*qSin(k*x[i]+phase);
  }
  ui->customPlot->graph()->setData(x, y);

  itemDemoPhaseTracer->setGraphKey((8*M_PI+fmod(M_PI*1.5-phase, 6*M_PI))/k);

  ui->customPlot->replot();

  // calculate frames per second:
  double key = secs;
  static double lastFpsKey;
  static int frameCount;
  ++frameCount;
  if (key-lastFpsKey > 2) // average fps over 2 seconds
  {
    ui->statusBar->showMessage(
          QString("%1 FPS, Total Data points: %2")
          .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
          .arg(ui->customPlot->graph(0)->data()->size())
          , 0);
    lastFpsKey = key;
    frameCount = 0;
  }
}

void GraphWindow::screenShot()
{
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
  QPixmap pm = QPixmap::grabWindow(qApp->desktop()->winId(), this->x()+2, this->y()+2, this->frameGeometry().width()-4, this->frameGeometry().height()-4);
#elif QT_VERSION < QT_VERSION_CHECK(5, 5, 0)
  QPixmap pm = qApp->primaryScreen()->grabWindow(qApp->desktop()->winId(), this->x()+2, this->y()+2, this->frameGeometry().width()-4, this->frameGeometry().height()-4);
#else
  QPixmap pm = qApp->primaryScreen()->grabWindow(qApp->desktop()->winId(), this->x()-7, this->y()-7, this->frameGeometry().width()+14, this->frameGeometry().height()+14);
#endif
  QString fileName = demoName.toLower()+".png";
  fileName.replace(" ", "");
  pm.save("./screenshots/"+fileName);
  qApp->quit();
}

void GraphWindow::allScreenShots()
{
    #if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
      QPixmap pm = QPixmap::grabWindow(qApp->desktop()->winId(), this->x()+2, this->y()+2, this->frameGeometry().width()-4, this->frameGeometry().height()-4);
    #else
      QPixmap pm = qApp->primaryScreen()->grabWindow(qApp->desktop()->winId(), this->x()+2, this->y()+2, this->frameGeometry().width()-4, this->frameGeometry().height()-4);
    #endif
  QString fileName = demoName.toLower()+".png";
  fileName.replace(" ", "");
  pm.save("./screenshots/"+fileName);

  if (currentDemoIndex < 19)
  {
    if (dataTimer.isActive())
      dataTimer.stop();
    dataTimer.disconnect();
    delete ui->customPlot;
    ui->customPlot = new QCustomPlot(ui->centralWidget);
   // ui->verticalLayout->addWidget(ui->customPlot);

    // setup delay for demos that need time to develop proper look:
    int delay = 250;
    if (currentDemoIndex == 10) // Next is Realtime data demo
      delay = 12000;
    else if (currentDemoIndex == 15) // Next is Item demo
      delay = 5000;
    QTimer::singleShot(delay, this, SLOT(allScreenShots()));
  } else
  {
    qApp->quit();
  }
}

void GraphWindow::paintEvent() {
         QPixmap pixmap(this->size());
         this->render(&pixmap);

         pixmap.save(demoName +".png");

     }


void GraphWindow::on_saveImage_clicked()
{
    ui->saveImage->setVisible(false);
    this->paintEvent();
    ui->saveImage->setVisible(true);
    QMessageBox *msgBox  = new QMessageBox();
          msgBox->setWindowTitle("Salvar gráfico");
          msgBox->setText("Gráfico salvo como " +demoName +".png");
          msgBox->show();
}

void GraphWindow::createChart(int type, QVector<double> data, QVector<QString> labels, QString name, int min, int max)
{
    switch (type) {
    case 1:
       lineChart(ui->customPlot, data,labels,name,min,max);
        break;
    case 0:
       barChart(ui->customPlot, data,labels,name,min,max);
         break;
    default:
        break;
    }
}


//create bar chart from data
void GraphWindow::barChart(QCustomPlot *customPlot, QVector<double> data, QVector<QString> labels, QString name, int min, int max)
{
  demoName = name;
  // set dark background gradient:
  QLinearGradient gradient(0, 0, 0, 400);
  gradient.setColorAt(0, QColor(90, 90, 90));
  gradient.setColorAt(0.38, QColor(105, 105, 105));
  gradient.setColorAt(1, QColor(70, 70, 70));
  customPlot->setBackground(QBrush(gradient));

  // create empty bar chart objects:
  QCPBars *bars = new QCPBars(customPlot->xAxis, customPlot->yAxis);
   // gives more crisp, pixel aligned bar borders
  bars->setAntialiased(false);
  bars->setStackingGap(1);
  // set names and colors:
  bars->setName(name);
  bars->setPen(QPen(QColor(250, 170, 20).lighter(150)));     //....change color
  bars->setBrush(QColor(251,18,194));

  // prepare x axis with country labels:
  QVector<double> ticks;
 // QVector<QString> labels;
  for(int i=0; i<data.count(); ++i){
      ticks.append(i);
  }


  QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
  textTicker->addTicks(ticks, labels); //eixo x por data
  customPlot->xAxis->setTicker(textTicker);
  customPlot->xAxis->setSubTicks(false);
  customPlot->xAxis->setTickLength(0, 4);
  customPlot->xAxis->setRange(0, data.count()); //tamanho das barras se ajustam ao numero de barras
  customPlot->xAxis->setBasePen(QPen(Qt::white));
  customPlot->xAxis->setTickPen(QPen(Qt::white));
  customPlot->xAxis->grid()->setVisible(true);
  customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
  customPlot->xAxis->setTickLabelColor(Qt::white);
  customPlot->xAxis->setLabelColor(Qt::white);

  // prepare y axis:

  customPlot->yAxis->setRange(min, max);
  customPlot->yAxis->setPadding(5); // a bit more space to the left border
  customPlot->yAxis->setLabel(name + " média diária");
  customPlot->yAxis->setBasePen(QPen(Qt::white));
  customPlot->yAxis->setTickPen(QPen(Qt::white));
  customPlot->yAxis->setSubTickPen(QPen(Qt::white));
  customPlot->yAxis->grid()->setSubGridVisible(true);
  customPlot->yAxis->setTickLabelColor(Qt::white);
  customPlot->yAxis->setLabelColor(Qt::white);
  customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
  customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

  bars->setData(ticks, data);

  // setup legend:
  customPlot->legend->setVisible(true);
  customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
  customPlot->legend->setBrush(QColor(255, 255, 255, 100));
  customPlot->legend->setBorderPen(Qt::NoPen);
  QFont legendFont = font();
  legendFont.setPointSize(10);
  customPlot->legend->setFont(legendFont);
  customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}


//create line chart from data
void GraphWindow::lineChart(QCustomPlot *customPlot, QVector<double> data, QVector<QString> labels, QString name, int min, int max)                           // grafico de linha
{
  demoName = name;
  customPlot->legend->setVisible(true);
  customPlot->legend->setFont(QFont("Helvetica", 9));
  QPen pen;

    customPlot->addGraph();
    pen.setColor(QColor(253,14,195));
    customPlot->graph()->setPen(pen);

     customPlot->graph()->setName(name);
    customPlot->graph()->setLineStyle((QCPGraph::LineStyle)1); // line style: 1 = line
    customPlot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
    customPlot->setBackground(QColor(240,230,174));
    // generate data:
    int n = data.count();
    QVector<double> x(n), y(n);

    for (int j=0; j<n; ++j)
    {
      x[j] = j;
      y[j] = data.at(j);
    }


    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(x, labels);

    customPlot->graph()->setData(x, y);
    customPlot->graph()->rescaleAxes(true);

  // zoom out a bit:
  customPlot->yAxis->scaleRange(1.1, customPlot->yAxis->range().center());
  customPlot->xAxis->scaleRange(1.1, customPlot->xAxis->range().center());
  // set blank axis lines:
  customPlot->xAxis->setTicker(textTicker);
  //customPlot->xAxis->setTicks(false);
  customPlot->yAxis->setTicks(true);
  //customPlot->xAxis->setTickLabels(false);
  customPlot->yAxis->setTickLabels(true);
  // make top right axes clones of bottom left axes:
  customPlot->axisRect()->setupFullAxesBox();
}
