#ifndef CPU_H
#define CPU_H

#include <QString>
#include <QVector>

#include "machine.h"
#include "cpuStats.h"
#include "cpuSnap.h"

using namespace std;


class Core;

class Cpu
{
public:
    Cpu();
    ~Cpu();

    string getModel(void);
    uint getNbCore(void);
    string getFreq(void);
    float getLoad(void);
    CpuStats * getStats(void);
    float getStatsCore(uint nbCpu);

private:
    int read_cpuInfo(string &model, uint &nbCore, string &freq);
    void updateStats(void);

protected:
    string m_model;
    string m_freq;
    uint m_nbCore;
    CpuStats * m_stats;
    CpuSnapshot m_snap1;
    CpuSnapshot m_snap2;
    float m_load;
};

#endif // CPU_H
