#include "menugraph.h"
#include "ui_menugraph.h"

#include "menusystem.h"
#include "menubench.h"
#include "menunet.h"
#include "machine.h"


MenuGraph::MenuGraph(QWidget *parent, Machine * machine) :
    QDialog(parent),
    ui(new Ui::MenuGraph),
    m_machine(machine)
{
    ui->setupUi(this);
    // set background image
    QPixmap backgroundImage("/home/dev/Documents/Git/rpi-monitoring/images/menu_graph.png");
    ui->background_graph->setPixmap(backgroundImage);

    // set btn transparent
    foreach(QCommandLinkButton *btn, this->findChildren<QCommandLinkButton*>())
    {
        btn->setStyleSheet("background: transparent;");
    }

    // connect signals
    connect(ui->btn_sys, SIGNAL(clicked()), this, SLOT(openMenuSys()));
    connect(ui->btn_bench, SIGNAL(clicked()), this, SLOT(openMenuBench()));
    connect(ui->btn_net, SIGNAL(clicked()), this, SLOT(openMenuNet()));
}

MenuGraph::~MenuGraph()
{
    delete ui;
}

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
