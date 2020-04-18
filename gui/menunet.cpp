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


/****************************************************
 *                                      CONSTRUCTOR
 * **************************************************/
MenuNet::MenuNet(QWidget *parent, Machine * machine) :
    QDialog(parent),
    ui(new Ui::MenuNet),
    m_machine(machine)
{
    ui->setupUi(this);
    // set background image
    QPixmap backgroundImage(IM_MENUNET_PATH);
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


