/**
 * \file diskfs.cpp
 * \brief All physical file systems on target
 * \author Julien Karecki
 */

/****************************************************
 *                                      INCLUDE
 * **************************************************/
#include "diskfs.h"

#include <sys/statvfs.h>
#include <mntent.h>
#include <iostream>


using namespace std;


/****************************************************
 *                                      CONSTRUCTOR
 * **************************************************/
DiskFs::DiskFs()
{
    DiskFs::initDiskFs();
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
void DiskFs::initDiskFs(void)
{
    FILE *fp;
    struct mntent *fs;
    int isFs = -1;

    m_nbDisk = 0;
    m_totalSize = 0;
    m_totalFree = 0;

    // open FILE_MTAB
    fp = setmntent(FILE_MTAB, "r");
    if (fp == nullptr)
    {
        fprintf(stderr, "DiskFs: %s: could not open : %s\n",
               FILE_MTAB, strerror(errno));
    }
    else
    {
        // get all field from FILE_MTAB into struct mntent (file system mount properties)
        while( (fs = getmntent(fp)) != nullptr )
        {
            isFs = DiskFs::readFs(fs);
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

    // real physical file system (ex: /dev/sda1)
    if(fs->mnt_fsname[0] == '/')
    {
        // get all FS properties into struct statvfs (size information)
        if (statvfs(fs->mnt_dir, &vfs) != 0)
        {
            fprintf(stderr, "DiskFs: %s: statvfs failed: %s\n",
                        fs->mnt_dir, strerror(errno));
        }
        else
        {
            // add new disk to the target
            DiskFs::addDisk(fs, &vfs);
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

void DiskFs::updateDiskFs(void)
{
    // clear old contents and update
    m_diskFs.clear();

    DiskFs::initDiskFs();

}

/****************************************************
 *                                      PUBLIC FUNCTIONS
 * **************************************************/
QVector<Disk> DiskFs::getDiskFs(void)
{
    DiskFs::updateDiskFs();

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
