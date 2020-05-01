/**
 * \file ram.cpp
 * \brief Contains RAM information
 * \author Julien Karecki
 */

/****************************************************
 *                                      INCLUDE
 * **************************************************/
#include <sys/sysinfo.h>
#include <iostream>

#include "ram.h"
#include "files.h"


using namespace std;


/****************************************************
 *                                      CONSTRUCTOR
 * **************************************************/
Ram::Ram()
{
    Ram::readInfo();
}

/****************************************************
 *                                      SIGNALS
 * **************************************************/


/****************************************************
 *                                      SLOTS
 * **************************************************/


/****************************************************
 *                                      PRIVATE FUNCTIONS
 * **************************************************/
int Ram::readInfo(void)
{
    int ret = -1;

    ret = Ram::readTotal();
    if (ret == 0)
        ret = Ram::updateLoad();

    return ret;
}

int Ram::readTotal(void)
{
    int ret = -1;
    struct sysinfo info;

    ret = sysinfo(&info);
    if (ret == 0)
    {
        m_total = info.totalram / MB;
    }

    return ret;
}

/****************************************************
 *                                      PUBLIC FUNCTIONS
 * **************************************************/
int Ram::getLoad(void)
{
    Ram::readInfo();
    return static_cast<int>(m_load);
}

int Ram::getFree(void)
{
    Ram::readInfo();
    return static_cast<int>(m_free);
}

int Ram::getTotal(void)
{    
    Ram::readInfo();
    return static_cast<int>(m_total);
}

int Ram::updateLoad(void)
{
    Files file("/proc/meminfo");
    string data;
    string name;
    int ret = -1;

    ret = file.searchInfo(name, data, ':', "MemAvailable");
    m_free = static_cast<double>(stoi(data, nullptr)) / 1024;   // value in kB => / 1024 B
    if (m_total != 0.0)
    {
        m_load = ((m_total-m_free) / m_total) * 100;
    }
    else
    {
        m_load = 0;
        cout << "RAM : division by 0" << endl;
        ret = -1;
    }

    return ret;
}
