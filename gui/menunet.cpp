#include "menunet.h"
#include "ui_menunet.h"

#include "menusystem.h"
#include "menugraph.h"
#include "menubench.h"


MenuNet::MenuNet(QWidget *parent, Machine * machine) :
    QDialog(parent),
    ui(new Ui::MenuNet),
    m_machine(machine)
{
    ui->setupUi(this);
    // set background image
    QPixmap backgroundImage("/home/dev/Documents/Git/rpi-monitoring/images/menu_network.png");
    ui->background_image->setPixmap(backgroundImage);

    // set btn transparent
    foreach(QCommandLinkButton *btn, this->findChildren<QCommandLinkButton*>())
    {
        btn->setStyleSheet("background: transparent;");
    }

    // connect signals
    connect(ui->btn_sys, SIGNAL(clicked()), this, SLOT(openMenuSys()));
    connect(ui->btn_graph, SIGNAL(clicked()), this, SLOT(openMenuGraph()));
    connect(ui->btn_bench, SIGNAL(clicked()), this, SLOT(openMenuBench()));
}

MenuNet::~MenuNet()
{
    delete ui;
}


void MenuNet::openMenuSys(void)
{
    MenuSystem *menu = new MenuSystem(nullptr, m_machine);
    menu->show();
    QWidget::close();
}

void MenuNet::openMenuGraph(void)
{
    MenuGraph *menu = new MenuGraph(nullptr, m_machine);
    menu->show();
    QWidget::close();
}

void MenuNet::openMenuBench(void)
{
    MenuBench *menu = new MenuBench(nullptr, m_machine);
    menu->show();
    QWidget::close();
}

