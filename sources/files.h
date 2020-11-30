#ifndef FILES_H
#define FILES_H

#include <fstream>
#include <sstream>


using namespace std;


class Files
{
public:
    Files(string path);

    /**
     * @brief searchInfo
     *          Search in a file with a formatted format (delimiter) a word
     * @param[out] name: ref to field name
     * @param[out] data: ref to data from field name
     * @param[in] delimiter: char delimiter between field name and data
     * @param[in] search: word to search
     * @return
     *      0: word found
     *      -1: word not found
     */
    int searchInfo(string &name, string &data, char delimiter, string search);
    /**
     * @brief countOccur
     *          Count in a file a word
     * @param[out] occur: number of time word occured
     * @param[in] search: word to search
     * @return
     *      0: correct file
     *      -1: err to open the file
     */
    int countOccur(uint32_t * occur, string search);

protected:
    string m_path;
    ifstream m_file;
};

#endif // FILES_H
