/**
 * \file cpuStats.cpp
 * \brief Treat all stats of CPU and cores
 * \author Julien Karecki
 */

/****************************************************
 *                                      INCLUDE
 * **************************************************/
#include "cpuStats.h"
#include "cpuSnap.h"

#include <iostream>

/****************************************************
 *                                      PRIVATE VARIABLES
 * **************************************************/
const int CpuStats::CPU_LABEL_W				= 3;
const int CpuStats::STATE_PERC_BASE_W		= 4;

const char * CpuStats::STR_STATES[CpuData::NUM_CPU_STATES]	= {	"usr",
                                                                "sys",
                                                                "nic",
                                                                "idl",
                                                                "iow",
                                                                "hir",
                                                                "sir",
                                                                "ste",
                                                                "gue",
                                                                "gun" };



/****************************************************
 *                                      CONSTRUCTOR
 * **************************************************/
CpuStats::CpuStats(const CpuSnapshot& s1, const CpuSnapshot& s2)
	: mS1(s1)
	, mS2(s2)
	, mPrecision(2)
	, mVerbose(false)
{

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


/****************************************************
 *                                      PUBLIC FUNCTIONS
 * **************************************************/
float CpuStats::GetPercActiveTotal()
{
	const float ACTIVE_TIME		= mS2.GetActiveTimeTotal() - mS1.GetActiveTimeTotal();
	const float IDLE_TIME		= mS2.GetIdleTimeTotal() - mS1.GetIdleTimeTotal();
	const float TOTAL_TIME		= ACTIVE_TIME + IDLE_TIME;

	return 100.f * ACTIVE_TIME / TOTAL_TIME;
}

float CpuStats::GetPercActive(unsigned int cpu)
{
	const float ACTIVE_TIME		= mS2.GetActiveTime(cpu) - mS1.GetActiveTime(cpu);
	const float IDLE_TIME		= mS2.GetIdleTime(cpu) - mS1.GetIdleTime(cpu);
	const float TOTAL_TIME		= ACTIVE_TIME + IDLE_TIME;

	return 100.f * ACTIVE_TIME / TOTAL_TIME;
}
