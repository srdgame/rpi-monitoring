/**
 * \file menunet.cpp
 * \brief Network menu which displays network information
 * \author Julien Karecki
 */

/****************************************************
 *                                      INCLUDE
 * **************************************************/
#include "menunet.h"
#include "ui_menunet.h"

#include "menusystem.h"
#include "menugraph.h"
#include "menubench.h"
#include "network.h"

#include <unistd.h>


/****************************************************
 *                                      CONSTRUCTOR
 * **************************************************/
MenuNet::MenuNet(QWidget *parent, Machine * machine) :
    QDialog(parent),
    ui(new Ui::MenuNet),
    m_machine(machine)
{
    QTimer * timer = new QTimer();
    m_grid = new QGridLayout();
    QGridLayout * grid_header = new QGridLayout();


    ui->setupUi(this);
    // set background image
    QPixmap backgroundImage(IM_MENUNET_PATH);
    ui->background_image->setPixmap(backgroundImage);

    // set btn transparent
    foreach(QCommandLinkButton *btn, this->findChildren<QCommandLinkButton*>())
    {
        btn->setStyleSheet("background: transparent;");
    }

    ui->layout_array->addLayout(grid_header);
    grid_header->addWidget(new QLabel("Name"), 0, 0);
    grid_header->addWidget(new QLabel("Address"), 0, 1);
    foreach (QLabel * label, this->findChildren<QLabel *>())
    {
        label->setFont(QFont("DejaVu", 22));
        label->setStyleSheet("color: white");
    }
    MenuNet::updateNet();


    // connect signals
    connect(ui->btn_sys, SIGNAL(clicked()), this, SLOT(openMenuSys()));
    connect(ui->btn_graph, SIGNAL(clicked()), this, SLOT(openMenuGraph()));
    connect(ui->btn_bench, SIGNAL(clicked()), this, SLOT(openMenuBench()));
}

MenuNet::~MenuNet()
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


/****************************************************
 *                                      PRIVATE FUNCTIONS
 * **************************************************/


/****************************************************
 *                                      PUBLIC FUNCTIONS
 * **************************************************/
void MenuNet::updateNet(void)
{
    vector<QString> netIp = *(m_machine->getNet()->getInterfacesIp());
    vector<QString> netName = *(m_machine->getNet()->getInterfacesName());
    uint nb = m_machine->getNet()->getNbInterfaces();
    uint i = 0;

    ui->layout_array->addLayout(m_grid);

    for (i=0; i<nb; i++)
    {
        m_grid->addWidget(new QLabel(netName[i]), i, 0);
        m_grid->addWidget(new QLabel(netIp[i]), i, 1);
    }

    foreach (QLabel * label, this->findChildren<QLabel *>())
    {
        label->setStyleSheet("color: white");
    }
}
