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


/****************************************************
 *                                      CONSTRUCTOR
 * **************************************************/
MenuBench::MenuBench(QWidget *parent, Machine * machine) :
    QDialog(parent),
    ui(new Ui::MenuBench),
    m_machine(machine)
{
    ui->setupUi(this);
    // set background image
    QPixmap backgroundImage(IM_MENUBENCH_PATH);
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


/****************************************************
 *                                      PRIVATE FUNCTIONS
 * **************************************************/


/****************************************************
 *                                      PUBLIC FUNCTIONS
 * **************************************************/
