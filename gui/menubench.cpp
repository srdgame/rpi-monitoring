/**
 * \file menubench.cpp
 * \brief Benchmark menu which allows to launch several commands/tools to stress target
 * \author Julien Karecki
 */

/****************************************************
 *                                      INCLUDE
 * **************************************************/
#include "menubench.h"
#include "ui_menubench.h"

#include "menusystem.h"
#include "menugraph.h"
#include "menunet.h"
#include "ram.h"
#include "cpu.h"

#include <iostream>

using namespace std;

/****************************************************
 *                                      CONSTRUCTOR
 * **************************************************/
MenuBench::MenuBench(QWidget *parent, Machine * machine) :
    QDialog(parent),
    ui(new Ui::MenuBench),
    m_machine(machine)
{
    ui->setupUi(this);    
    QTimer * timer = new QTimer();
    QTimer * timer2 = new QTimer();

    // set background image
    QPixmap backgroundImage(IM_MENUBENCH_PATH);
    ui->background_image->setPixmap(backgroundImage);

    // set btn transparent
    foreach(QCommandLinkButton *btn, this->findChildren<QCommandLinkButton*>())
    {
        btn->setStyleSheet("background: transparent;");
    }

    m_plotCpu = new QCustomPlot();
    m_plotCpu->addGraph();
    m_plotCpu->graph(0)->setAntialiasedFill(true);
    m_plotCpu->graph(0)->setAntialiased(true);

    /* Configure x-Axis as time in secs */
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%s");
    m_plotCpu->xAxis->setTicker(timeTicker);
    m_plotCpu->axisRect()->setupFullAxesBox();

    /* Configure x and y-Axis to display Labels */
    m_plotCpu->xAxis->setLabel("Time(s)");
    m_plotCpu->xAxis->setLabelFont(QFont(QFont().family(), 8));
    m_plotCpu->xAxis->setTickLabelFont(QFont(QFont().family(),8));

    m_plotCpu->yAxis->setLabel("CPU Utilization(%)");
    m_plotCpu->yAxis->setLabelFont(QFont(QFont().family(), 8));
    m_plotCpu->yAxis->setTickLabelFont(QFont(QFont().family(),8));
    m_plotCpu->yAxis->setRange(0, 100);


    m_plotRam = new QCustomPlot();
    m_plotRam->addGraph();
    m_plotRam->graph(0)->setAntialiasedFill(true);
    m_plotRam->graph(0)->setAntialiased(true);

    /* Configure x-Axis as time in secs */
    QSharedPointer<QCPAxisTickerTime> timeTicker2(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%s");
    m_plotRam->xAxis->setTicker(timeTicker2);
    m_plotRam->axisRect()->setupFullAxesBox();

    /* Configure x and y-Axis to display Labels */
    m_plotRam->xAxis->setLabel("Time(s)");
    m_plotRam->xAxis->setLabelFont(QFont(QFont().family(), 8));
    m_plotRam->xAxis->setTickLabelFont(QFont(QFont().family(),8));

    m_plotRam->yAxis->setLabel("RAM Utilization(%)");
    m_plotRam->yAxis->setLabelFont(QFont(QFont().family(), 8));
    m_plotRam->yAxis->setTickLabelFont(QFont(QFont().family(),8));
    m_plotRam->yAxis->setRange(0, 100);

    ui->layout_graph_cpu->addWidget(m_plotCpu);
    ui->layout_graph_ram->addWidget(m_plotRam);

    ui->spin_cpu_nb->setRange(1, static_cast<int>(m_machine->getCpu()->getNbCore()));
    ui->spin_timeout->setMinimum(1);
    ui->spin_timeout->setValue(10);
    ui->spin_ram_block_nb->setMinimum(1);
    ui->spin_ram_block_size->setRange(1, m_machine->getRam()->getTotal());
    ui->spin_ram_block_size->setValue(1024);


    // connect signals
    connect(ui->btn_sys, SIGNAL(clicked()), this, SLOT(openMenuSys()));
    connect(ui->btn_graph, SIGNAL(clicked()), this, SLOT(openMenuGraph()));
    connect(ui->btn_net, SIGNAL(clicked()), this, SLOT(openMenuNet()));
    connect(ui->btn_stress_cpu, SIGNAL(clicked()), this, SLOT(launchStressCpu()));
    connect(ui->btn_stress_ram, SIGNAL(clicked()), this, SLOT(launchStressRam()));

    connect(timer, SIGNAL(timeout()), this, SLOT(realtimePlotCpu()));
    connect(timer2, SIGNAL(timeout()), this, SLOT(realtimePlotRam()));
    timer->start(100);
    timer2->start(10);
}

MenuBench::~MenuBench()
{
    delete ui;
    delete m_machine;
}


/****************************************************
 *                                      SIGNALS
 * **************************************************/


/****************************************************
 *                                      SLOTS
 * **************************************************/
void MenuBench::openMenuSys(void)
{
    MenuSystem *menu = new MenuSystem(nullptr, m_machine);
    menu->show();
    QWidget::close();
}

void MenuBench::openMenuGraph(void)
{
    MenuGraph *menu = new MenuGraph(nullptr, m_machine);
    menu->show();
    QWidget::close();
}

void MenuBench::openMenuNet(void)
{
    MenuNet *menu = new MenuNet(nullptr, m_machine);
    menu->show();
    QWidget::close();
}

void MenuBench::realtimePlotCpu()
{
    MenuBench::realtimePlot(m_plotCpu, static_cast<int>(m_machine->getCpu()->getLoad()));
}

void MenuBench::realtimePlotRam()
{
    MenuBench::realtimePlot(m_plotRam, m_machine->getRam()->getLoad());
}

int MenuBench::launchStressCpu()
{
    QString cmd = "";

    cmd = "stress --cpu " + QString::number(ui->spin_cpu_nb->value());
    cmd.append(" --timeout " + QString::number(ui->spin_timeout->value()));
    cmd.append(" &");

    return system(cmd.toUtf8());
}

int MenuBench::launchStressRam()
{
    QString cmd = "";

    cmd = "stress --vm " + QString::number(ui->spin_ram_block_nb->value());
    cmd.append(" --vm-bytes " + QString::number(ui->spin_ram_block_size->value()) + "M");
    cmd.append(" --timeout " + QString::number(ui->spin_timeout->value()));
    cmd.append(" &");

    return system(cmd.toUtf8());
}

/****************************************************
 *                                      PRIVATE FUNCTIONS
 * **************************************************/
void MenuBench::realtimePlot(QCustomPlot * plot, int value)
{
    static QTime time(QTime::currentTime());
    double key = time.elapsed()/1000.0;
    static double lastPointKey = 0;
    if(key - lastPointKey > 0.002)
    {
        plot->graph(0)->addData(key, value);
        lastPointKey = key;
    }

    /* make key axis range scroll right with the data at a constant range. */
    plot->xAxis->setRange(key, 20, Qt::AlignRight);
    plot->replot();
}

/****************************************************
 *                                      PUBLIC FUNCTIONS
 * **************************************************/
