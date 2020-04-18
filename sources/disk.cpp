#include "disk.h"

Disk::Disk()
{
    m_name = "";
    m_mount = "";
    m_size = 0.0;
    m_free = 0.0;
}

Disk::Disk(string name, string mount, long sizeDisk, long freeDisk) :
    m_name(name),
    m_mount(mount),
    m_size(sizeDisk),
    m_free(freeDisk)
{

}

void Disk::setName(string name)
{
    m_name = name;
}

void Disk::setMount(string mount)
{
    m_mount = mount;
}

void Disk::setSize(long sizeDisk)
{
    m_size = sizeDisk;
}

void Disk::setFree(long freeDisk)
{
    m_free = freeDisk;
}

string Disk::getName()
{
    return m_name;
}

string Disk::getMount()
{
    return m_mount;
}

long Disk::getSize()
{
    return m_size;
}

long Disk::getFree()
{
    return m_free;
}
