#include "cpu.h"
#include "files.h"
#include <iostream>
#include <unistd.h>

using namespace std;


Cpu::Cpu()
{
    CpuSnapshot snap;

    m_model = "";
    m_nbCore = 0;
    m_freq = "";

    if (Cpu::read_cpuInfo(m_model, m_nbCore, m_freq) != 0)
    {
        qDebug("ERR : read cpu information");
    }

    m_load = 0.0;
    m_snap1 = snap;
    m_snap2 = m_snap1;
    m_stats = new CpuStats(m_snap1, m_snap2);
}

Cpu::~Cpu()
{
    delete m_stats;
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

float Cpu::getLoad(void)
{
    Cpu::updateStats();

    m_load = m_stats->GetPercActiveTotal();

    return m_load;
}

CpuStats * Cpu::getStats(void)
{
    Cpu::updateStats();
    return m_stats;
}

float Cpu::getStatsCore(uint nbCpu)
{
    float loadCpu = 0.0;

    Cpu::updateStats();

    if (nbCpu < m_nbCore)
    {
        loadCpu = m_stats->GetPercActive(nbCpu);
    }

    return loadCpu;
}

void Cpu::updateStats(void)
{
    CpuSnapshot snap1;
    usleep(100000);
    CpuSnapshot snap2;
    CpuStats * stats = new CpuStats(snap1, snap2);

    m_snap1 = snap1;
    m_snap2 = snap2;

    swap(m_stats, stats);

    delete stats;
}

int Cpu::read_cpuInfo(string &model, uint &nbCore, string &freq)
{
    Files file("/proc/cpuinfo");
    string data;
    string name;
    int ret = -1;

    ret = file.searchInfo(name, data, ':', "model name");

    if (getline(stringstream(data), model, '@') && getline(stringstream(data), freq))
    {
        freq = freq.substr(model.size() + 2, freq.size());
        ret = 0;
    }

    file.countOccur(&nbCore, "cpu cores");

    return ret;
}

