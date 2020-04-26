#ifndef MENUGRAPH_H
#define MENUGRAPH_H

#include <QDialog>
#include <QtWidgets>
#include <QtCharts>
#include <QTableWidget>

#include "images.h"
#include "qcustomplot.h"

class Machine;

namespace Ui {
class MenuGraph;
}

class MenuGraph : public QDialog
{
    Q_OBJECT

public:
    explicit MenuGraph(QWidget *parent = nullptr, Machine * machine = nullptr);
    ~MenuGraph();

private slots:
    void openMenuSys(void);
    void openMenuBench(void);
    void openMenuNet(void);
    void realtimePlot(void);

private:
    void updateDiskBrow(void);

private:
    Ui::MenuGraph *ui;
    Machine * m_machine;
    QChart * m_disk_chart;
    QChart * m_ram_chart;
    QPieSeries * m_serie;
    QTableWidget * m_tab_disk;
    QCustomPlot * m_plot;
};

#endif // MENUGRAPH_H
