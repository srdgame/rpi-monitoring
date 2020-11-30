/**
 * \file files.cpp
 * \brief Search and count occurence into a file
 * \author Julien Karecki
 */

/****************************************************
 *                                      INCLUDE
 * **************************************************/
#include <iostream>

#include "files.h"


/****************************************************
 *                                      CONSTRUCTOR
 * **************************************************/
Files::Files(string path) : m_path(path)
{
    m_file = ifstream(path);
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

int Files::countOccur(uint32_t * occur, string search)
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


/****************************************************
 *                                      PUBLIC FUNCTIONS
 * **************************************************/
