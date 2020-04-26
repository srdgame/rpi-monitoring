#include "menusystem.h"
#include <QApplication>
#include "radialbar.h"
#include "machine.h"



#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

QT_CHARTS_USE_NAMESPACE





using namespace std;


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qmlRegisterType<RadialBar>("RadialBar", 1, 0, "RadialBar");

    Machine * machine = new Machine;

    MenuSystem * win_sys = new MenuSystem(nullptr, machine);
    win_sys->show();



//    // Create your time series
//       QLineSeries *series = new QLineSeries();
//       series->append(0, 6);
//       series->append(2, 4);
//       series->append(3, 8);
//       series->append(7, 4);
//       series->append(10, 5);
//       *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) <<   QPointF(20, 2);

//    // Configure your chart
//       QChart *chart = new QChart();
//       chart->addSeries(series);
//       chart->legend()->setAlignment(Qt::AlignLeft);
//       chart->createDefaultAxes();
//       chart->setTitle("Simple line chart example");
//       chart->setOpacity(0.1);

//       // Create your chart view
//       QChartView *chartView = new QChartView(chart);
//       chartView->setRenderHint(QPainter::Antialiasing);
//       // Display into a main window
//       QMainWindow window;
//       window.setCentralWidget(chartView);
//       window.resize(400, 300);
//       window.show();

    return app.exec();
}
