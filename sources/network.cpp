#include "network.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <ifaddrs.h>
#include <arpa/inet.h>


Network::Network()
{
    Network::readInterfaces();
    m_nbInterfaces = 0;
}

string * Network::getInterfaces(void)
{
    int ret = -1;

    ret = Network::readInterfaces();
    if (ret == -1)
    {
        qDebug("Error update network interfaces");
    }
    return m_tabInterfaces;
}

int Network::readInterfaces(void)
{
    struct ifaddrs *interfaces = nullptr;
    struct ifaddrs *temp_addr = nullptr;
    int ret = -1;

    m_tabInterfaces.clear();
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
                   m_tabInterfaces.push_back(temp_addr->ifa_name, (inet_ntoa(((struct sockaddr_in*)temp_addr->ifa_addr)->sin_addr)));
                   m_nbInterfaces++;
           }
           temp_addr = temp_addr->ifa_next;
       }
    }
    // Free memory
    freeifaddrs(interfaces);

    return ret;
}
