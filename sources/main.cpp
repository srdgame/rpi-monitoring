#include "menusystem.h"
#include <QApplication>
#include "radialbar.h"
#include "machine.h"


using namespace std;


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qmlRegisterType<RadialBar>("RadialBar", 1, 0, "RadialBar");

    Machine * machine = new Machine;

    MenuSystem * win_sys = new MenuSystem(nullptr, machine);
    win_sys->show();

    return app.exec();
}
