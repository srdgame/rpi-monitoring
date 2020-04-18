/**
 * \file cpuData.cpp
 * \brief Contains core stats properties at a specific moment
 * \author Julien Karecki
 */

/****************************************************
 *                                      INCLUDE
 * **************************************************/
#include "cpuData.h"
#include <sstream>


/****************************************************
 *                                      PRIVATE VARIABLES
 * **************************************************/
const std::string CpuData::STR_CPU("cpu");
const std::string CpuData::STR_TOT("tot");

const std::size_t CpuData::LEN_STR_CPU = 3;


/****************************************************
 *                                      CONSTRUCTOR
 * **************************************************/
void CpuData::ReadData(const std::string & line)
{
	std::istringstream ss(line);

	// read cpu label
	ss >> mLabel;

	// remove "cpu" from the label when it's a processor number
	if(mLabel.size() > LEN_STR_CPU)
	    mLabel.erase(0, LEN_STR_CPU);
	// replace "cpu" with "tot" when it's total values
	else
	    mLabel = STR_TOT;

	// read times
	for(int i = 0; i < NUM_CPU_STATES; ++i)
    	ss >> mTimes[i];
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
