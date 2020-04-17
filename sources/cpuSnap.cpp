#include "cpuSnap.h"

#include <fstream>

const int CpuSnapshot::INDEX_TOT = 0;

// == PUBLIC FUNCTIONS ==

CpuSnapshot::CpuSnapshot()
{
	std::ifstream fileStat("/proc/stat");

	std::string line;

	while(std::getline(fileStat, line))
	{
		// cpu stats line found
        if(CpuData::IsDataCPUStats(line))
		{
			// store entry
            mEntries.emplace_back(CpuData());
            CpuData & entry = mEntries.back();

			entry.ReadData(line);
		}
	}
}
