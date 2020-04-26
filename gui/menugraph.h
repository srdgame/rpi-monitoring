#ifndef MENUGRAPH_H
#define MENUGRAPH_H

#include <QDialog>
#include <QtWidgets>
#include <QtCharts>
#include <QTableWidget>

#include "images.h"

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

private:
    void updateDiskBrow(void);

private:
    Ui::MenuGraph *ui;
    Machine * m_machine;
    QChart * m_disk_chart;
    QChart * m_ram_chart;
    QPieSeries * m_serie;
    QTableWidget * m_tab_disk;
};

#endif // MENUGRAPH_H
