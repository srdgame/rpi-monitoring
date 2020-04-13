#ifndef CPU_H
#define CPU_H

#include <QString>
#include <QVector>

#include "machine.h"


using namespace std;


class Core;

class Cpu
{
public:
    Cpu();

    string getModel(void);
    uint getNbCore(void);
    string getFreq(void);

private:
    int read_cpuInfo(string &model, uint &nbCore, string &freq);

protected:
    string m_model;
    string m_freq;
    uint m_nbCore;
    QVector<Core> * m_tabCores();
};

#endif // CPU_H
