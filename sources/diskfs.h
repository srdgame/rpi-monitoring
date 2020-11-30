#ifndef DISKFS_H
#define DISKFS_H


#include <QVector>

#include "disk.h"


#define FILE_MTAB   "/etc/mtab"


class DiskFs
{
public:
    DiskFs();

    QVector<Disk> getDiskFs(void);
    uint32_t getNbDisk(void);
    long getTotalSize(void);
    long getFreeSize(void);

private:
    void initDiskFs(void);
    int readFs(const struct mntent *fs);
    void addDisk(const struct mntent *fs, const struct statvfs *vfs);
    void updateDiskFs(void);

protected:
    uint32_t m_nbDisk;
    long m_totalSize;
    long m_totalFree;
    QVector<Disk> m_diskFs;
};

#endif // DISKFS_H
