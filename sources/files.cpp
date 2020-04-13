#include <iostream>

#include "files.h"


Files::Files(string path) : m_path(path)
{
    m_file = ifstream(path);
}

int Files::searchInfo(string &name, string &data, char delimiter, string search)
{
    int ret = -1;
    string line;

    while(getline(m_file, line))
    {
        stringstream str(line);
        if ( getline( str, name, delimiter ) && getline(str, data) && name.substr(0, search.length()) == search )
        {
            ret = 0;
            break;
        }
    }

    return ret;
}

int Files::countOccur(uint * occur, string search)
{
    int ret = -1;
    string line;

    *occur = 0;

    while(getline(m_file, line))
    {
        ret = 0;
        if ( line.find(search) == 0 )
        {
            (*occur)++;
        }
    }

    return ret;
}

