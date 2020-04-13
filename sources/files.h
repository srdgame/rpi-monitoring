#ifndef FILES_H
#define FILES_H

#include <fstream>
#include <sstream>


using namespace std;


class Files
{
public:
    Files(string path);

    int searchInfo(string &name, string &data, char delimiter, string search);

protected:
    string m_path;
    ifstream m_file;
};

#endif // FILES_H
