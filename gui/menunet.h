#ifndef MENUNET_H
#define MENUNET_H

#include <QDialog>
#include <QLabel>
#include <QGridLayout>

#include "images.h"

class Machine;

namespace Ui {
class MenuNet;
}

class MenuNet : public QDialog
{
    Q_OBJECT

public:
    explicit MenuNet(QWidget *parent = nullptr, Machine * machine = nullptr);
    ~MenuNet();

private slots:
    void openMenuSys(void);
    void openMenuGraph(void);
    void openMenuBench(void);
    void updateNet(void);

private:
    Ui::MenuNet *ui;
    Machine * m_machine;
    QGridLayout *  m_grid;
};

#endif // MENUNET_H
