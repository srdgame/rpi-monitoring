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
#include "ram.h"


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
    m_plot = new QCustomPlot();
    m_plot->addGraph();
    m_plot->graph(0)->setAntialiasedFill(true);
    m_plot->graph(0)->setAntialiased(true);

    /* Configure x-Axis as time in secs */
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%s");
    m_plot->xAxis->setTicker(timeTicker);
    m_plot->axisRect()->setupFullAxesBox();

    /* Configure x and y-Axis to display Labels */
    m_plot->xAxis->setLabel("Time(s)");
    m_plot->xAxis->setLabelFont(QFont(QFont().family(), 8));
    m_plot->xAxis->setTickLabelFont(QFont(QFont().family(),8));

    m_plot->yAxis->setLabel("Utilization(%)");
    m_plot->yAxis->setLabelFont(QFont(QFont().family(), 8));
    m_plot->yAxis->setTickLabelFont(QFont(QFont().family(),8));
    m_plot->yAxis->setRange(0, 100);

    ui->layout_ram->addWidget(m_plot);

    // connect signals
    connect(ui->btn_sys, SIGNAL(clicked()), this, SLOT(openMenuSys()));
    connect(ui->btn_bench, SIGNAL(clicked()), this, SLOT(openMenuBench()));
    connect(ui->btn_net, SIGNAL(clicked()), this, SLOT(openMenuNet()));

    connect(timer, SIGNAL(timeout()), this, SLOT(realtimePlot()));
    timer->start(100);

}

MenuGraph::~MenuGraph()
{
    delete ui;
    delete m_machine;
    delete m_tab_disk;
    delete m_plot;
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

void MenuGraph::realtimePlot()
{
    static QTime time(QTime::currentTime());
    double key = time.elapsed()/1000.0;
    static double lastPointKey = 0;
    if(key - lastPointKey > 0.002)
    {
        m_plot->graph(0)->addData(key, m_machine->getRam()->getLoad());
        lastPointKey = key;
    }

    /* make key axis range scroll right with the data at a constant range. */
    m_plot->xAxis->setRange(key, 20, Qt::AlignRight);
    m_plot->replot();
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
