#ifndef CORE_H
#define CORE_H

#include <QtGlobal>
#include "cpu.h"

class Core : public Cpu
{
public:
    Core();

private :
    qreal m_load;
};

#endif // CORE_H

