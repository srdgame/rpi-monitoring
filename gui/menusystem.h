#ifndef MENUSYSTEM_H
#define MENUSYSTEM_H

#include <QDialog>
#include <QTextBrowser>

#include "machine.h"

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

    void init_constructor(Machine * machine);
    void init_sysLabels(void);
    void init_sysRadial(void);

    void init_sysInfo(void);
    void init_sysCpuInfo(void);
    void init_sysText(Machine * machine);
    void init_cpuText(Cpu * cpu);

private:
    Ui::MenuSystem *ui;
    Machine * m_machine;
    QTextBrowser * m_txtUser;
    QTextBrowser * m_txtOs;
    QTextBrowser * m_txtKernel;
    QTextBrowser * m_txtModel;
    QTextBrowser * m_txtCore;
    QTextBrowser * m_txtSpeed;
};

#endif // MENUSYSTEM_H
