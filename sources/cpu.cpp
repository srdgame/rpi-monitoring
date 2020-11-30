/**
 * \file cpu.cpp
 * \brief Contains all CPU properties : information, cores and stats
 * \author Julien Karecki
 */

/****************************************************
 *                                      INCLUDE
 * **************************************************/
#include "cpu.h"
#include "files.h"
#include <iostream>
#include <unistd.h>

using namespace std;


/****************************************************
 *                                      CONSTRUCTOR
 * **************************************************/
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


/****************************************************
 *                                      SIGNALS
 * **************************************************/


/****************************************************
 *                                      SLOTS
 * **************************************************/


/****************************************************
 *                                      PRIVATE FUNCTIONS
 * **************************************************/
void Cpu::updateStats(void)
{
    CpuSnapshot snap1;      // 1st snapshot to save cpu stats
    usleep(100000);
    CpuSnapshot snap2;      // 2nd snapshot to save cpu stats after t+100ms
    CpuStats * stats = new CpuStats(snap1, snap2);      // tmp stats objects to calculate a new cpu
                                                        // stats from 2 previous snapshots

    m_snap1 = snap1;
    m_snap2 = snap2;

    swap(m_stats, stats);

    delete stats;
}

int Cpu::read_cpuInfo(string &model, uint32_t &nbCore, string &freq)
{
    Files file("/proc/cpuinfo");
    string data;
    string name;
    int ret = -1;

	std::cerr << "read_cpuInfo" << std::endl;

    // model = "model name: $(CPU_MODEL) @ $(CPU_FREQ)" or
	// model = "model name : $(CPU_MODEL)"
    ret = file.searchInfo(name, data, ':', "model name");
	if (ret)
		return ret;

	if (string.find("@") {
		// data = "$(CPU_MODEL) @ $(CPU_FREQ)"
		if (getline(stringstream(data), model, '@') && getline(stringstream(data), freq))
		{
			// remove "model name : $(CPU_MODEL) " and "@ "
			freq = freq.substr(model.size() + 2, freq.size());
			ret = 0;
		}
		file.countOccur(&nbCore, "cpu cores");
	} else {
		ret = file.searchInfo(name, data, ':', "BogoMIPS");
		freq = data.substr(2, data.size());
		file.countOccur(&nbCore, "processor");
	}

	std::cerr << "read_cpuInfo" << model << "\t" << freq << "\t" << nbCore << std::endl;

    return ret;
}


/****************************************************
 *                                      PUBLIC FUNCTIONS
 * **************************************************/
string Cpu::getModel(void)
{
    return m_model;
}

uint32_t Cpu::getNbCore(void)
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

float Cpu::getStatsCore(uint32_t nbCpu)
{
    float loadCpu = 0.0;

    Cpu::updateStats();

    if (nbCpu < m_nbCore)
    {
        loadCpu = m_stats->GetPercActive(nbCpu);
    }

    return loadCpu;
}
