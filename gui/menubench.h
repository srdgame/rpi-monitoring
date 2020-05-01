#ifndef MENUBENCH_H
#define MENUBENCH_H

#include <QDialog>

#include "images.h"
#include "qcustomplot.h"

class Machine;

namespace Ui {
class MenuBench;
}

class MenuBench : public QDialog
{
    Q_OBJECT

public:
    explicit MenuBench(QWidget *parent = nullptr, Machine * machine = nullptr);
    ~MenuBench();

private:
    void realtimePlot(QCustomPlot * plot, int value);

private slots:
    void openMenuSys(void);
    void openMenuGraph(void);
    void openMenuNet(void);
    void realtimePlotCpu(void);
    void realtimePlotRam(void);
    int launchStressCpu(void);
    int launchStressRam(void);

private:
    Ui::MenuBench *ui;
    Machine * m_machine;
    QCustomPlot * m_plotCpu;
    QCustomPlot * m_plotRam;
};

#endif // MENUBENCH_H
