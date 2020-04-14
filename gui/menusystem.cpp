#include "menusystem.h"
#include "ui_menusystem.h"
#include <QQuickWidget>

#include "radialbar.h"
#include "cpu.h"
#include "ram.h"
#include "menugraph.h"
#include "menubench.h"
#include "menunet.h"

#include <iostream>


using namespace std;


MenuSystem::MenuSystem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MenuSystem)
{
    init_constructor();
    m_machine = nullptr;
}

MenuSystem::MenuSystem(QWidget *parent, Machine * machine) :
    QDialog(parent),
    ui(new Ui::MenuSystem),
    m_machine(machine)
{
    init_constructor();
}

MenuSystem::~MenuSystem()
{
    delete ui;
    delete m_machine;
}


void MenuSystem::init_constructor(void)
{
    ui->setupUi(this);

    // set background image
    QPixmap backgroundImage("/home/dev/Documents/Git/rpi-monitoring/images/menu_system.png");
    ui->background_sys->setPixmap(backgroundImage);

    // set label fonts
    init_sysLabels();

    // set radial bars
    init_sysRadial();

    // set sys txt
    init_sysText();

    // set cpu txt
    init_cpuText();


    // set btn transparent
    foreach(QCommandLinkButton *btn, this->findChildren<QCommandLinkButton*>())
    {
        btn->setStyleSheet("background: transparent;");
    }

    // connect signals
    connect(ui->btn_graph, SIGNAL(clicked()), this, SLOT(openMenuGraph()));
    connect(ui->btn_net, SIGNAL(clicked()), this, SLOT(openMenuNet()));
    connect(ui->btn_bench, SIGNAL(clicked()), this, SLOT(openMenuBench()));
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

void MenuSystem::updateRam(void)
{
    Ram * ram = m_machine->getRam();
    m_ram->setProperty("value", ram->getLoad());
    cout << "ram " << ram->getLoad() << endl;
}
