#ifndef CPUSTATS_H
#define CPUSTATS_H

// CPUStats - object which prints stats extracted by 2 CPUSnapshots.

#include "cpuData.h"

class CpuSnapshot;

class CpuStats
{
public:
    CpuStats(const CpuSnapshot& s1, const CpuSnapshot& s2);

    float GetPercActiveTotal();
	float GetPercActive(unsigned int cpu);

private:
	static const int CPU_LABEL_W;
	static const int STATE_PERC_BASE_W;

    static const char * STR_STATES[CpuData::NUM_CPU_STATES];

private:
    const CpuSnapshot & mS1;
    const CpuSnapshot & mS2;

	unsigned int mPrecision;

	bool mVerbose;
};

#endif
