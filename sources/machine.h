#ifndef MACHINE_H
#define MACHINE_H

#include <QString>

class Cpu;
class Ram;
class DiskFs;

class Machine
{
public:
    Machine();
    ~Machine();

    QString getUser(void);
    QString getOs(void);
    QString getKernel(void);
    Cpu * getCpu(void);
    Ram * getRam(void);
    DiskFs * getDiskFs(void);

private:
    int read_user(QString &user);
    int read_os_kernel(QString &os, QString &kernel);

protected:
    QString m_user;
    QString m_os;
    QString m_kernel;
    Cpu * m_cpu;
    Ram * m_ram;
    DiskFs * m_diskFs;
};

#endif
