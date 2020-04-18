#include <sys/statvfs.h>
#include <mntent.h>

#include "diskfs.h"

#include <iostream>

using namespace std;


DiskFs::DiskFs()
{
    initDiskFs();
}


QVector<Disk> DiskFs::getDiskFs(void)
{
    m_diskFs.clear();

    initDiskFs();

    return m_diskFs;
}

uint DiskFs::getNbDisk(void)
{
    return m_nbDisk;
}

long DiskFs::getTotalSize(void)
{
    return m_totalSize;
}

long DiskFs::getFreeSize(void)
{
    return m_totalFree;
}

void DiskFs::updateDiskFs(void)
{
    m_diskFs.clear();

    initDiskFs();

}

void DiskFs::initDiskFs(void)
{
    FILE *fp;
    struct mntent *fs;
    int isFs = -1;

    m_nbDisk = 0;
    m_totalSize = 0;
    m_totalFree = 0;

    fp = setmntent(FILE_MTAB, "r");
    if (fp == nullptr)
    {
        fprintf(stderr, "DiskFs: %s: could not open : %s\n",
               FILE_MTAB, strerror(errno));
    }
    else
    {
        while( (fs = getmntent(fp)) != nullptr )
        {
            isFs = readFs(fs);
            if (isFs == 0)
            {
                m_nbDisk++;
            }
        }
    }
}

int DiskFs::readFs(const struct mntent *fs)
{
    int isFs = -1;
    struct statvfs vfs;

    if(fs->mnt_fsname[0] == '/')
    {
        if (statvfs(fs->mnt_dir, &vfs) != 0)
        {
            fprintf(stderr, "DiskFs: %s: statvfs failed: %s\n",
                        fs->mnt_dir, strerror(errno));
        }
        else
        {
             addDisk(fs, &vfs);
             isFs = 0;
        }
    }

    return isFs;
}

void DiskFs::addDisk(const struct mntent *fs, const struct statvfs *vfs)
{
    string name = fs->mnt_fsname;;
    string mount = fs->mnt_dir;
    long sizeDisk = (vfs->f_blocks * vfs->f_frsize) / (1024*1024);     // in MB
    long freeDisk = (vfs->f_bsize * vfs->f_bfree) / (1024*1024);

    Disk disk(name, mount, sizeDisk, freeDisk);
    m_diskFs.push_back(disk);
    m_totalSize += sizeDisk;
    m_totalFree += freeDisk;
}
