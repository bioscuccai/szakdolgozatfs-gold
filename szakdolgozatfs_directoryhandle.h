#ifndef SZAKDOLGOZATFS_DIRECTORYHANDLE_H
#define SZAKDOLGOZATFS_DIRECTORYHANDLE_H

#include <vector>
#include <string>

#include "szakdolgozatfs.h"

using namespace std;

class SzakdolgozatFs_DirectoryHandle{
    public:
        blockAddr nodeBlock;
        bool isOpen;
        string path;
        SzakdolgozatFs* fs;
    public:
        vector<string> getFileNames();
        SzakdolgozatFs_DirectoryHandle(SzakdolgozatFs* fs_, string path_);
        void open();
        void create();
};

#endif
