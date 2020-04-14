#ifndef MENUNET_H
#define MENUNET_H

#include <QDialog>


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

private:
    Ui::MenuNet *ui;
    Machine * m_machine;
};

#endif // MENUNET_H
