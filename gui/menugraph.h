#ifndef MENUGRAPH_H
#define MENUGRAPH_H

#include <QDialog>
#include <QtWidgets>

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
    Ui::MenuGraph *ui;
    Machine * m_machine;
};

#endif // MENUGRAPH_H
