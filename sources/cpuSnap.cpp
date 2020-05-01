/**
 * \file cpuSnap.cpp
 * \brief Snapshot all CPU cores stats from /proc/stat
 * \author Julien Karecki
 */

/****************************************************
 *                                      INCLUDE
 * **************************************************/
#include "cpuSnap.h"

#include <fstream>


/****************************************************
 *                                      PRIVATE VARIABLES
 * **************************************************/
const int CpuSnapshot::INDEX_TOT = 0;


/****************************************************
 *                                      CONSTRUCTOR
 * **************************************************/
CpuSnapshot::CpuSnapshot()
{
	std::ifstream fileStat("/proc/stat");

	std::string line;

	while(std::getline(fileStat, line))
	{
		// cpu stats line found
        if(CpuData::IsDataCPUStats(line))
		{
            // store entry : all cpu times at a specific moment
            mEntries.emplace_back(CpuData());
            CpuData & entry = mEntries.back();

			entry.ReadData(line);
		}
	}
}
