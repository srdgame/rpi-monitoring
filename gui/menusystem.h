#ifndef MENUSYSTEM_H
#define MENUSYSTEM_H

#include <QDialog>
#include <QTextBrowser>
#include <QQuickItem>

#include "machine.h"

class Machine;

namespace Ui {
class MenuSystem;
}

class MenuSystem : public QDialog
{
    Q_OBJECT

public:
    MenuSystem(QWidget *parent = nullptr);
    MenuSystem(QWidget *parent = nullptr, Machine * machine = nullptr);
    ~MenuSystem();

    void init_constructor(void);
    void init_sysLabels(void);
    void init_sysRadial(void);
    void init_sysInfo(void);
    void init_sysCpuInfo(void);
    void init_sysText(void);
    void init_cpuText(void);

private slots:
    void openMenuGraph(void);
    void openMenuBench(void);
    void openMenuNet(void);
    void updateRam(void);
    void updateCpu(void);
    void updateDiskFs(void);

private:
    Ui::MenuSystem *ui;
    Machine * m_machine;
    QTextBrowser * m_txtUser;
    QTextBrowser * m_txtOs;
    QTextBrowser * m_txtKernel;
    QTextBrowser * m_txtModel;
    QTextBrowser * m_txtCore;
    QTextBrowser * m_txtSpeed;
    QQuickItem * m_cpu;
    QQuickItem * m_ram;
    QQuickItem * m_disk;
};


#endif // MENUSYSTEM_H
