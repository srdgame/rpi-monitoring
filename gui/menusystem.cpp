/**
 * \file menusystem.cpp
 * \brief System menu which displays target general information
 * \author Julien Karecki
 */

/****************************************************
 *                                      INCLUDE
 * **************************************************/
#include "menusystem.h"
#include "ui_menusystem.h"
#include <QQuickWidget>
#include <iostream>

#include "radialbar.h"
#include "cpu.h"
#include "ram.h"
#include "diskfs.h"
#include "menugraph.h"
#include "menubench.h"
#include "menunet.h"


using namespace std;

/****************************************************
 *                                      CONSTRUCTOR
 * **************************************************/
MenuSystem::MenuSystem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MenuSystem)
{
    MenuSystem::init_constructor();
    m_machine = nullptr;
}

MenuSystem::MenuSystem(QWidget *parent, Machine * machine) :
    QDialog(parent),
    ui(new Ui::MenuSystem),
    m_machine(machine)
{
    MenuSystem::init_constructor();
}

MenuSystem::~MenuSystem()
{
    delete ui;
    delete m_machine;
    delete m_txtUser;
    delete m_txtOs;
    delete m_txtKernel;
    delete m_txtModel;
    delete m_txtCore;
    delete m_txtSpeed;
    delete m_cpu;
    delete m_ram;
    delete m_disk;
}


/****************************************************
 *                                      SIGNALS
 * **************************************************/


/****************************************************
 *                                      SLOTS
 * **************************************************/
void MenuSystem::updateRam(void)
{
    Ram * ram = m_machine->getRam();
    m_ram->setProperty("value", ram->getLoad());
}

void MenuSystem::updateCpu(void)
{
    Cpu * cpu = m_machine->getCpu();
    m_cpu->setProperty("value", static_cast<uint32_t>(cpu->getLoad()));
}

void MenuSystem::updateDiskFs(void)
{
    DiskFs * diskFs = m_machine->getDiskFs();

    diskFs->getDiskFs();

    long total = diskFs->getTotalSize();
    long avail = diskFs->getFreeSize();
    long perc = (total-avail)*100 / total;

    m_disk->setProperty("value", static_cast<int>(perc));
}

void MenuSystem::openMenuGraph(void)
{
    MenuGraph *menu_graph = new MenuGraph(nullptr, m_machine);
    menu_graph->show();
    QWidget::close();
}

void MenuSystem::openMenuNet(void)
{
    MenuNet *menu = new MenuNet(nullptr, m_machine);
    menu->show();
    QWidget::close();
}

void MenuSystem::openMenuBench(void)
{
    MenuBench *menu = new MenuBench(nullptr, m_machine);
    menu->show();
    QWidget::close();
}


/****************************************************
 *                                      PRIVATE FUNCTIONS
 * **************************************************/


/****************************************************
 *                                      PUBLIC FUNCTIONS
 * **************************************************/
void MenuSystem::init_constructor(void)
{
    ui->setupUi(this);

    // set background image
    QPixmap backgroundImage(IM_MENUSYS_PATH);
    ui->background_sys->setPixmap(backgroundImage);

    // set label fonts
    MenuSystem::init_sysLabels();

    // set radial bars
    MenuSystem::init_sysRadial();

    // set sys txt
    MenuSystem::init_sysText();

    // set cpu txt
    MenuSystem::init_cpuText();


    // set btn transparent
    foreach(QCommandLinkButton *btn, this->findChildren<QCommandLinkButton*>())
    {
        btn->setStyleSheet("background: transparent;");
    }

    // connect signals
    connect(ui->btn_graph, SIGNAL(clicked()), this, SLOT(openMenuGraph()));
    connect(ui->btn_net, SIGNAL(clicked()), this, SLOT(openMenuNet()));
    connect(ui->btn_bench, SIGNAL(clicked()), this, SLOT(openMenuBench()));

    QTimer *timer = new QTimer(this);
    QTimer *timer2 = new QTimer(this);

    MenuSystem::updateRam();
    MenuSystem::updateCpu();
    MenuSystem::updateDiskFs();
    connect(timer, SIGNAL(timeout()), this, SLOT(updateRam()));
    connect(timer, SIGNAL(timeout()), this, SLOT(updateCpu()));
    connect(timer2, SIGNAL(timeout()), this, SLOT(updateDiskFs()));
    timer->start(1000);
    timer2->start(30000);
}

void MenuSystem::init_sysLabels(void)
{
    int i = 0;

    foreach(QLabel *label, this->findChildren<QLabel*>())
    {
        label->setStyleSheet("color: white");
        i++;
    }
}

void MenuSystem::init_sysRadial(void)
{
    int i = 0;
    QQuickItem *quick;

    quick = ui->radial_perf->rootObject()->findChild<QQuickItem*>("radial_cpu");
    if (quick != nullptr)
    {
        quick->setProperty("value", 0);
        m_cpu=quick;
        i++;
    }

    quick = ui->radial_perf->rootObject()->findChild<QQuickItem*>("radial_ram");
    if (quick != nullptr)
    {
        quick->setProperty("value", 0);
        m_ram=quick;
        i++;
    }

    quick = ui->radial_perf->rootObject()->findChild<QQuickItem*>("radial_disk");
    if (quick != nullptr)
    {
        quick->setProperty("value", 0);
        m_disk=quick;
        i++;
    }
}

void MenuSystem::init_sysText(void)
{
    m_txtUser = ui->txt_user;
    m_txtOs = ui->txt_os;
    m_txtKernel = ui->txt_kernel;

    m_txtUser->setText(m_machine->getUser());
    m_txtOs->setText(m_machine->getOs());
    m_txtKernel->setText(m_machine->getKernel());
}

void MenuSystem::init_cpuText(void)
{
    Cpu * cpu = new Cpu();
    cpu = m_machine->getCpu();

    m_txtModel = ui->txt_model;
    m_txtCore = ui->txt_core;
    m_txtSpeed = ui->txt_speed;

    m_txtModel->setText(QString::fromStdString(cpu->getModel()));
    m_txtCore->setText(QString::number(cpu->getNbCore()));
    m_txtSpeed->setText(QString::fromStdString(cpu->getFreq()));
}
