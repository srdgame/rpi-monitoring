#include "menusystem.h"
#include "ui_menusystem.h"
#include <QQuickWidget>
#include "radialbar.h"
#include "cpu.h"


using namespace std;


MenuSystem::MenuSystem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MenuSystem)
{
    init_constructor(m_machine);
    m_machine = nullptr;
}

MenuSystem::MenuSystem(QWidget *parent, Machine * machine) : QDialog(parent), ui(new Ui::MenuSystem), m_machine(machine)
{
    init_constructor(m_machine);
}

MenuSystem::~MenuSystem()
{
    delete ui;
    delete m_machine;
}


void MenuSystem::init_constructor(Machine * machine)
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
    init_sysText(machine);

    // set cpu txt
    init_cpuText(m_machine->getCpu());
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

    foreach(QQuickItem *quick, ui->radial_perf->rootObject()->findChildren<QQuickItem*>())
    {
        quick->setProperty("value", 0);
        i++;
    }
}

void MenuSystem::init_sysText(Machine * machine)
{
    m_txtUser = ui->txt_user;
    m_txtOs = ui->txt_os;
    m_txtKernel = ui->txt_kernel;

    m_txtUser->setText(machine->getUser());
    m_txtOs->setText(machine->getOs());
    m_txtKernel->setText(machine->getKernel());
}

void MenuSystem::init_cpuText(Cpu * cpu)
{
    m_txtModel = ui->txt_model;
    m_txtCore = ui->txt_core;
    m_txtSpeed = ui->txt_speed;

    m_txtModel->setText(QString::fromStdString(cpu->getModel()));
    m_txtCore->setText(QString::number(cpu->getNbCore()));
    m_txtSpeed->setText(QString::fromStdString(cpu->getFreq()));
}


