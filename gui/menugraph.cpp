/**
 * \file menugraph.cpp
 * \brief Graph menu which displays real time graph target performance
 * \author Julien Karecki
 */

/****************************************************
 *                                      INCLUDE
 * **************************************************/
#include "menugraph.h"
#include "ui_menugraph.h"
#include <QVector>

#include "menusystem.h"
#include "menubench.h"
#include "menunet.h"
#include "machine.h"
#include "diskfs.h"


#include <iostream>
using namespace std;

/****************************************************
 *                                      CONSTRUCTOR
 * **************************************************/
MenuGraph::MenuGraph(QWidget *parent, Machine * machine) :
    QDialog(parent),
    ui(new Ui::MenuGraph),
    m_machine(machine)
{
    ui->setupUi(this);
    QTimer * timer = new QTimer();

    // set background image
    QPixmap backgroundImage(IM_MENUGRAPH_PATH);
    ui->background_graph->setPixmap(backgroundImage);

    // set btn transparent
    foreach(QCommandLinkButton *btn, this->findChildren<QCommandLinkButton*>())
    {
        btn->setStyleSheet("background: transparent;");
    }

    MenuGraph::updateDiskBrow();




           // Create your time series
              QLineSeries *series = new QLineSeries();
              series->append(0, 6);
              series->append(2, 4);
              series->append(3, 8);
              series->append(7, 4);
              series->append(10, 5);
              *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) <<   QPointF(20, 2);

           // Configure your chart
              QChart *chart2 = new QChart();
              chart2->addSeries(series);
              chart2->legend()->setAlignment(Qt::AlignLeft);
              chart2->createDefaultAxes();


              // remove borders
              chart2->layout()->setContentsMargins(0,0,0,0);
              chart2->setBackgroundRoundness(0);

              // Create your chart view
              QChartView *chartView2 = new QChartView(chart2);
              chartView2->setRenderHint(QPainter::Antialiasing);

              // Configure your chart
              QLineSeries *series2 = new QLineSeries();
              series2->append(0, 6);
              series2->append(2, 4);
              ui->layout_ram->addWidget(chartView2);




    // connect signals
    connect(ui->btn_sys, SIGNAL(clicked()), this, SLOT(openMenuSys()));
    connect(ui->btn_bench, SIGNAL(clicked()), this, SLOT(openMenuBench()));
    connect(ui->btn_net, SIGNAL(clicked()), this, SLOT(openMenuNet()));

    connect(timer, SIGNAL(timeout()), this, SLOT(updateDiskChart()));
    timer->start(10000);
}

MenuGraph::~MenuGraph()
{
    delete ui;
    delete m_machine;
    delete m_disk_chart;
    delete m_ram_chart;
    delete m_serie;
    delete m_tab_disk;
}

/****************************************************
 *                                      SIGNALS
 * **************************************************/


/****************************************************
 *                                      SLOTS
 * **************************************************/
void MenuGraph::openMenuSys(void)
{
    MenuSystem *menu = new MenuSystem(nullptr, m_machine);
    menu->show();
    QWidget::close();
}

void MenuGraph::openMenuBench(void)
{
    MenuBench *menu = new MenuBench(nullptr, m_machine);
    menu->show();
    QWidget::close();
}

void MenuGraph::openMenuNet(void)
{
    MenuNet *menu = new MenuNet(nullptr, m_machine);
    menu->show();
    QWidget::close();
}


/****************************************************
 *                                      PRIVATE FUNCTIONS
 * **************************************************/
void MenuGraph::updateDiskBrow(void)
{
    QVector<Disk> vec_disk = m_machine->getDiskFs()->getDiskFs();
    QString str_brow = "";

    foreach(Disk disk, vec_disk)
    {
        str_brow.append(QString::fromStdString(disk.toString())+"\n");
    }
    ui->brow_disk->setText(str_brow);
}

/****************************************************
 *                                      PUBLIC FUNCTIONS
 * **************************************************/
