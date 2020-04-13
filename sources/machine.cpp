#include <stdlib.h>
#include <iostream>
#include <sys/utsname.h>

#include "machine.h"
#include "cpu.h"
#include "ram.h"


using namespace std;


Machine::Machine()
{
    m_user = "";
    m_os = "";
    m_kernel = "";

    if (Machine::read_user(m_user) != 0)
    {
        qDebug("ERR : read current user");
    }

    if (Machine::read_os_kernel(m_os, m_kernel) != 0)
    {
        qDebug("ERR : read current OS and Kernel version");
    }

    m_cpu = new Cpu();

    m_ram = new Ram();
}

Machine::~Machine()
{
    delete m_cpu;
    delete m_ram;
}

QString Machine::getUser(void)
{
    return m_user;
}

QString Machine::getOs(void)
{
    return m_os;
}

QString Machine::getKernel(void)
{
    return m_kernel;
}

Cpu * Machine::getCpu(void)
{
    return m_cpu;
}

Ram * Machine::getRam(void)
{
    return m_ram;
}

int Machine::read_user(QString &user)
{
    int ret = -1;
    QString tmp;

    tmp = getenv("USER");
    if (tmp != nullptr)
    {
        user = tmp;
        ret = 0;
    }

    return ret;
}

int Machine::read_os_kernel(QString &os, QString &kernel)
{
    int ret = -1;
    struct utsname buf;

    ret = uname(&buf);
    if (ret == 0)
    {
        os = buf.nodename;
        kernel = buf.release;
    }

    return ret;
}
