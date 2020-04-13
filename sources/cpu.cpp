#include "cpu.h"
#include "files.h"
#include <iostream>

using namespace std;


Cpu::Cpu()
{
    m_model = "";
    m_nbCore = 0;
    m_freq = 0.0;

    if (Cpu::read_cpuInfo(m_model, m_nbCore, m_freq) != 0)
    {
        qDebug("ERR : read cpu information");
    }
}


string Cpu::getModel(void)
{
    return m_model;
}

uint Cpu::getNbCore(void)
{
    return m_nbCore;
}

string Cpu::getFreq(void)
{
    return m_freq;
}

int Cpu::read_cpuInfo(string &model, uint &nbCore, string &freq)
{
    Files file("/proc/cpuinfo");
    string data;
    string name;
    int ret = -1;

    ret = file.searchInfo(name, data, ':', "model name");

    if (getline(stringstream(data), model, '@') && getline(stringstream(data), freq))
        ret = 0;

    freq = freq.substr(model.size() + 2, freq.size());

    return ret;
}
