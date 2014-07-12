#ifndef SZAKDOLGOZATFS_INODE_H
#define SZAKDOLGOZATFS_INODE_H 1

#include "szakdolgozatfs_util.h"
#include <vector>
#include <ctime>
#include <sys/stat.h>

using namespace std;

class SzakdolgozatFs_Inode{
    public:
        char name[256];
        //unsigned long firstBlock;
        unsigned long blockListLocation;
        unsigned long size;
        SzakdolgozatFs_Filetype type;


        time_t lastModification;
        time_t lastAccess;
        mode_t mode;
        uid_t uid;
        gid_t gid;

        //vector<unsigned long> blocks;
    public:
        SzakdolgozatFs_Inode(char *name_, unsigned long blockListLocation_, unsigned long size_, SzakdolgozatFs_Filetype type_);
        SzakdolgozatFs_Inode();
        void debugInodeInfo();
        /*void createRawFile(unsigned char* data, long blockSizeInBytes);
        long getRawSize(long blockSizeInBytes);*/
};
/*
class SzakdolgozatFs_Inode_Ondisk{
    public:
        char name[256];
        unsigned long firstBlock;
        unsigned long size;
        SzakdolgozatFs_Filetype type;
        unsigned long blocks[];
};*/
#endif
