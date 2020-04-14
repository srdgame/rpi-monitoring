#include "menubench.h"
#include "ui_menubench.h"

#include "menusystem.h"
#include "menugraph.h"
#include "menunet.h"


MenuBench::MenuBench(QWidget *parent, Machine * machine) :
    QDialog(parent),
    ui(new Ui::MenuBench),
    m_machine(machine)
{
    ui->setupUi(this);
    // set background image
    QPixmap backgroundImage("/home/dev/Documents/Git/rpi-monitoring/images/menu_bench.png");
    ui->background_image->setPixmap(backgroundImage);

    // set btn transparent
    foreach(QCommandLinkButton *btn, this->findChildren<QCommandLinkButton*>())
    {
        btn->setStyleSheet("background: transparent;");
    }

    // connect signals
    connect(ui->btn_sys, SIGNAL(clicked()), this, SLOT(openMenuSys()));
    connect(ui->btn_graph, SIGNAL(clicked()), this, SLOT(openMenuGraph()));
    connect(ui->btn_net, SIGNAL(clicked()), this, SLOT(openMenuNet()));
}

MenuBench::~MenuBench()
{
    delete ui;
}

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
