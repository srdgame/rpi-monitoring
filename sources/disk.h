#ifndef DISK_H
#define DISK_H


#include <string>


using namespace std;

class Disk
{
public:
    Disk();
    Disk(string name, string mount, long size, long free);

    void setName(string name);
    void setMount(string mount);
    void setSize(long size);
    void setFree(long free);
    string getName(void);
    string getMount(void);
    long getSize(void);
    long getFree(void);
    string toString(void);
    long getPerc(void);

private:
    string m_name;
    string m_mount;
    long m_size;
    long m_free;
};

#endif // DISK_H
