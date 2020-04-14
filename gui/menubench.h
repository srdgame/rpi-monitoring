#ifndef MENUBENCH_H
#define MENUBENCH_H

#include <QDialog>

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

private slots:
    void openMenuSys(void);
    void openMenuGraph(void);
    void openMenuNet(void);

private:
    Ui::MenuBench *ui;
    Machine * m_machine;
};

#endif // MENUBENCH_H
