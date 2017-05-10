#include "graphwindow.h"
#include "ui_graphwindow.h"

GraphWindow::GraphWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphWindow)
{
    ui->setupUi(this);
    setGeometry(400, 250, 600, 460);
  // barChartTemp(ui->customPlot);
   //  setupLineStyleDemo(ui->customPlot);
    Table *t = new Table();
    t->readData();
    t->setDailyData();
    QVector<double> temp = t->humidMonth(5,2017);
     QVector<QString> labels = t->datesLabels(1,5,2017,temp.count());
    barChart(ui->customPlot, temp, labels, "Umidade",50, 100);
    setWindowTitle("Grafico da umidade no mÊs de maio");
//    QVector<double> temp = t->temperatureMonth(5,2017);
//     QVector<QString> labels = t->datesLabels(1,5,2017,temp.count());
//    lineChart(ui->customPlot, temp, labels, "Temperatura");
//    setWindowTitle("Grafico da temperatura");
    ui->customPlot->replot();
}

GraphWindow::~GraphWindow()
{
    delete ui;
}

void GraphWindow::setupBarChartDemo(QCustomPlot *customPlot)
{
  demoName = "Bar Chart Demo";
  // set dark background gradient:
  QLinearGradient gradient(0, 0, 0, 400);
  gradient.setColorAt(0, QColor(90, 90, 90));
  gradient.setColorAt(0.38, QColor(105, 105, 105));
  gradient.setColorAt(1, QColor(70, 70, 70));
  customPlot->setBackground(QBrush(gradient));

  // create empty bar chart objects:
  QCPBars *regen = new QCPBars(customPlot->xAxis, customPlot->yAxis);
  QCPBars *nuclear = new QCPBars(customPlot->xAxis, customPlot->yAxis);
  QCPBars *fossil = new QCPBars(customPlot->xAxis, customPlot->yAxis);
  regen->setAntialiased(false); // gives more crisp, pixel aligned bar borders
  nuclear->setAntialiased(false);
  fossil->setAntialiased(false);
  regen->setStackingGap(1);
  nuclear->setStackingGap(1);
  fossil->setStackingGap(1);
  // set names and colors:
  fossil->setName("Fossil fuels");
  fossil->setPen(QPen(QColor(251,18,194).lighter(170)));
  fossil->setBrush(QColor(251,18,194));
  nuclear->setName("Nuclear");
  nuclear->setPen(QPen(QColor(250, 170, 20).lighter(150)));
  nuclear->setBrush(QColor(250, 170, 20));
  regen->setName("Regenerative");
  regen->setPen(QPen(QColor(41,244,9).lighter(130)));
  regen->setBrush(QColor(41,244,9));
  // stack bars on top of each other:
  nuclear->moveAbove(fossil);
  regen->moveAbove(nuclear);

  // prepare x axis with country labels:
  QVector<double> ticks;
  QVector<QString> labels;
  ticks << 1 << 2 << 3 << 4 << 5 << 6 << 7;
  labels << "USA" << "Japan" << "Germany" << "France" << "UK" << "Italy" << "Canada";
  QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
  textTicker->addTicks(ticks, labels);
  customPlot->xAxis->setTicker(textTicker);
  customPlot->xAxis->setTickLabelRotation(60);
  customPlot->xAxis->setSubTicks(false);
  customPlot->xAxis->setTickLength(0, 4);
  customPlot->xAxis->setRange(0, 8);
  customPlot->xAxis->setBasePen(QPen(Qt::white));
  customPlot->xAxis->setTickPen(QPen(Qt::white));
  customPlot->xAxis->grid()->setVisible(true);
  customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
  customPlot->xAxis->setTickLabelColor(Qt::white);
  customPlot->xAxis->setLabelColor(Qt::white);

  // prepare y axis:
  customPlot->yAxis->setRange(0, 12.1);
  customPlot->yAxis->setPadding(5); // a bit more space to the left border
  customPlot->yAxis->setLabel("Power Consumption in\nKilowatts per Capita (2007)");
  customPlot->yAxis->setBasePen(QPen(Qt::white));
  customPlot->yAxis->setTickPen(QPen(Qt::white));
  customPlot->yAxis->setSubTickPen(QPen(Qt::white));
  customPlot->yAxis->grid()->setSubGridVisible(true);
  customPlot->yAxis->setTickLabelColor(Qt::white);
  customPlot->yAxis->setLabelColor(Qt::white);
  customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
  customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

  // Add data:
  QVector<double> fossilData, nuclearData, regenData;
  fossilData  << 0.86*10.5 << 0.83*5.5 << 0.84*5.5 << 0.52*5.8 << 0.89*5.2 << 0.90*4.2 << 0.67*11.2;
  nuclearData << 0.08*10.5 << 0.12*5.5 << 0.12*5.5 << 0.40*5.8 << 0.09*5.2 << 0.00*4.2 << 0.07*11.2;
  regenData   << 0.06*10.5 << 0.05*5.5 << 0.04*5.5 << 0.06*5.8 << 0.02*5.2 << 0.07*4.2 << 0.25*11.2;
  fossil->setData(ticks, fossilData);
  nuclear->setData(ticks, nuclearData);
  regen->setData(ticks, regenData);

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

void GraphWindow::setupLineStyleDemo(QCustomPlot *customPlot)                           // grafico de linha
{
  demoName = "Line Style Demo";
  customPlot->legend->setVisible(true);
  customPlot->legend->setFont(QFont("Helvetica", 9));
  QPen pen;
  QString linename = "Temperatura Média";
  // add graphs with different line styles:

    customPlot->addGraph();
    pen.setColor(QColor(253,14,195));
    customPlot->graph()->setPen(pen);

     customPlot->graph()->setName(linename);
    customPlot->graph()->setLineStyle((QCPGraph::LineStyle)1); // line style: 1 = line
    customPlot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
    customPlot->setBackground(QColor(240,230,174));
    // generate data:
    QVector<double> x(10), y(10);
    weatherData *d = new weatherData();
    for (int j=0; j<10; ++j)
    {
      x[j] = j;
      y[j] = d->temperature[j];
    }

    QVector<double> ticks;
    QVector<QString> labels;
    ticks << 0 << 1 << 2 << 3 << 4 << 5 << 6 << 7 <<8 << 9 ;
    labels << "01/05" << "02/05" << "03/05" << "04/05" << "05/05" << "06/05" << "07/05" << "08/05" << "09/05" << "10/05"; //datas
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);

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


//temperatura e pressao
void GraphWindow::tempexPresChart(QCustomPlot *customPlot)
{
    demoName = "Temperature x Pressure";
    customPlot->legend->setVisible(true);
    customPlot->legend->setFont(QFont("Helvetica", 9));
    QPen pen;
    QString linename = "pressure";
    QString barname = "temperature";
    QVector<double> ticks;
    ticks << 0 << 1 << 2 << 3 << 4 << 5 << 6 << 7 <<8 << 9 ;
    weatherData *d = new weatherData();

    //temperatura
    customPlot->addGraph( customPlot->xAxis, customPlot->yAxis);
    pen.setColor(QColor(253,14,195));
    customPlot->graph(0)->setName(barname);
    customPlot->graph(0)->setLineStyle((QCPGraph::LineStyle)1);
    customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
    customPlot->graph(0)->setData(ticks, d->temperature);
    //customPlot->yAxis->setLabel("Temperatura");
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, d->datas); //eixo x por data
    customPlot->xAxis->setTicker(textTicker);

    //pressao
    pen.setColor(QColor(253,204,195));
    customPlot->addGraph(customPlot->xAxis, customPlot->yAxis2 );

    customPlot->graph(1)->setName(linename);
    customPlot->yAxis2->setVisible(true);
    customPlot->graph(1)->setLineStyle((QCPGraph::LineStyle)1);
    customPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
    customPlot->graph(1)->setData(ticks, d->pressure);
    customPlot->yAxis->setRange(0,40);
    customPlot->yAxis2->setRange(1000,1005);
    customPlot->xAxis->setRange(0,10);
    customPlot->graph(0)->rescaleAxes(true);
    customPlot->graph(1)->rescaleAxes(true);
    customPlot->yAxis->scaleRange(1.1, customPlot->yAxis->range().center());
    customPlot->yAxis2->scaleRange(1.1, customPlot->yAxis2->range().center());
    customPlot->xAxis->scaleRange(1.1, customPlot->xAxis->range().center());

    customPlot->yAxis->setTicks(true);
    customPlot->yAxis->setTickLabels(true);
    customPlot->yAxis2->setTicks(true);
    customPlot->yAxis2->setTickLabels(true);
    customPlot->axisRect()->setupFullAxesBox();


}




//Temperature chart
void GraphWindow::barChartTemp(QCustomPlot *customPlot)
{
  demoName = "Bar Chart Temperature";
  // set dark background gradient:
  QLinearGradient gradient(0, 0, 0, 400);
  gradient.setColorAt(0, QColor(90, 90, 90));
  gradient.setColorAt(0.38, QColor(105, 105, 105));
  gradient.setColorAt(1, QColor(70, 70, 70));
  customPlot->setBackground(QBrush(gradient));

  // create empty bar chart objects:
  QCPBars *tempmed = new QCPBars(customPlot->xAxis, customPlot->yAxis);
   // gives more crisp, pixel aligned bar borders
  tempmed->setAntialiased(false);
  tempmed->setStackingGap(1);
  // set names and colors:
  tempmed->setName("Temperatura media");
  tempmed->setPen(QPen(QColor(250, 170, 20).lighter(150)));     //....change color
  tempmed->setBrush(QColor(251,18,194));

  // prepare x axis with country labels:
  QVector<double> ticks;
 // QVector<QString> labels;
  weatherData *d = new weatherData();
  ticks << 0 << 1 << 2 << 3 << 4 << 5 << 6 << 7 <<8 <<9<<10;

  QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
  textTicker->addTicks(ticks, d->datas); //eixo x por data
  customPlot->xAxis->setTicker(textTicker);
  customPlot->xAxis->setSubTicks(false);
  customPlot->xAxis->setTickLength(0, 4);
  customPlot->xAxis->setRange(0, d->temperature.count()); //tamanho das barras se ajustam ao numero de barras
  customPlot->xAxis->setBasePen(QPen(Qt::white));
  customPlot->xAxis->setTickPen(QPen(Qt::white));
  customPlot->xAxis->grid()->setVisible(true);
  customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
  customPlot->xAxis->setTickLabelColor(Qt::white);
  customPlot->xAxis->setLabelColor(Qt::white);

  // prepare y axis:
  customPlot->yAxis->setRange(0, 40);
  customPlot->yAxis->setPadding(5); // a bit more space to the left border
  customPlot->yAxis->setLabel("Temperatura Média Diária(ºC)");
  customPlot->yAxis->setBasePen(QPen(Qt::white));
  customPlot->yAxis->setTickPen(QPen(Qt::white));
  customPlot->yAxis->setSubTickPen(QPen(Qt::white));
  customPlot->yAxis->grid()->setSubGridVisible(true);
  customPlot->yAxis->setTickLabelColor(Qt::white);
  customPlot->yAxis->setLabelColor(Qt::white);
  customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
  customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

  // Add data:
  //QVector<double> medData;
  //medData << 24 << 22 << 28 << 29 << 33 << 35 << 18;

  tempmed->setData(ticks, d->temperature);

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




// funções interface gráfica
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
    //setupDemo(currentDemoIndex+1);
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
}



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
