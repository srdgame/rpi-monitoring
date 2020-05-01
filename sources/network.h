#ifndef NETWORK_H
#define NETWORK_H

#include <QVector>
#include <iostream>


using namespace std;


class Network
{
public:
    Network();
    ~Network();

    vector<QString> * getInterfacesName(void);
    vector<QString> * getInterfacesIp(void);
    uint getNbInterfaces(void);

private:
    int readInterfaces(void);

protected:
    uint m_nbInterfaces;
    vector<QString> * m_tabInterfacesName;
    vector<QString> * m_tabInterfacesIp;
};


#endif // NETWORK_H
