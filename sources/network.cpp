/**
 * \file network.cpp
 * \brief Contains all network information : @ip, wifi discovery ...
 * \author Julien Karecki
 */

/****************************************************
 *                                      INCLUDE
 * **************************************************/
#include "network.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <ifaddrs.h>
#include <arpa/inet.h>


/****************************************************
 *                                      CONSTRUCTOR
 * **************************************************/
Network::Network()
{
    m_tabInterfacesName = new vector<QString>;
    m_tabInterfacesIp = new vector<QString>;

    Network::readInterfaces();
    m_nbInterfaces = 0;
}

Network::~Network()
{
    delete m_tabInterfacesIp;
    delete m_tabInterfacesName;
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
int Network::readInterfaces(void)
{
    struct ifaddrs *interfaces = nullptr;
    struct ifaddrs *temp_addr = nullptr;
    int ret = -1;

    m_tabInterfacesName->clear();
    m_tabInterfacesIp->clear();
    m_nbInterfaces = 0;

    ret = getifaddrs(&interfaces);
    if (ret == 0)
    {
       // Loop through linked list of interfaces
       temp_addr = interfaces;
       while(temp_addr != nullptr)
       {
           if(temp_addr->ifa_addr->sa_family == AF_INET)
           {
                   m_tabInterfacesName->push_back(temp_addr->ifa_name);
                   m_tabInterfacesIp->push_back(inet_ntoa(((struct sockaddr_in*)temp_addr->ifa_addr)->sin_addr));
                   m_nbInterfaces++;
           }
           temp_addr = temp_addr->ifa_next;
       }
    }
    // Free memory
    freeifaddrs(interfaces);

    return ret;
}


/****************************************************
 *                                      PUBLIC FUNCTIONS
 * **************************************************/
vector<QString> * Network::getInterfacesName(void)
{
    int ret = -1;

    ret = Network::readInterfaces();
    if (ret == -1)
    {
        qDebug("Error update network interfaces");
    }
    return m_tabInterfacesName;
}

vector<QString> * Network::getInterfacesIp(void)
{
    int ret = -1;

    ret = Network::readInterfaces();
    if (ret == -1)
    {
        qDebug("Error update network interfaces");
    }
    return m_tabInterfacesIp;
}

uint Network::getNbInterfaces(void)
{
    int ret = -1;

    ret = Network::readInterfaces();
    if (ret == -1)
    {
        qDebug("Error update network interfaces");
    }

    return m_nbInterfaces;
}
