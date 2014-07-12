#ifndef SZAKDOLGOZATFS_FILEHANDLE_H
#define SZAKDOLGOZATFS_FILEHANDLE_H

#include "szakdolgozatfs.h"
#include "szakdolgozatfs_util.h"

class SzakdolgozatFs_FileHandle{
    public:
        SzakdolgozatFs *fs;
        bool isOpen;
        string mode;
        unsigned long seekGetPos;
        unsigned long seekPutPos;
        blockAddr nodeBlock;
        string path;

    public:
        void read(unsigned char *ptr, unsigned long size);
        void write(unsigned char *ptr, unsigned long size);
        unsigned long tellg();
        unsigned long tellp();
        void seekg(unsigned long pos);
        void seekp(unsigned long pos);
        SzakdolgozatFs_FileHandle(SzakdolgozatFs* fs_, string path_);
        void touch();
        void open();
        unsigned long getSize();
        void getContents(unsigned char* ptr);
        void replaceContents(unsigned char* ptr, long size);
        void deleteFile();
        SzakdolgozatFs_Filetype getType();
        blockAddr getNodeBlock();
        void rename(string newName);
        void move(string newDir);

        void setATime(time_t newTime);
        void setMTime(time_t newTime);
        void chmod(mode_t newMode);
        void chown(uid_t uid, gid_t gid);

        //static bool fileExists(SzakdolgozatFs* fs_, string path);
};
#endif
