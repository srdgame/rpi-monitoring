#ifndef NETWORK_H
#define NETWORK_H

#include <QVector>
#include <iostream>


using namespace std;


class Network
{
public:
    Network();

    vector<string,string> getInterfaces(void);

private:
    int readInterfaces(void);

protected:
    uint m_nbInterfaces;
    string * m_tabInterfaces;
};

#endif // NETWORK_H
