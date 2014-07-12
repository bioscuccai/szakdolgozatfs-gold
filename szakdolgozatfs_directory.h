#ifndef SZAKDOLGOZATFS_DIRECTORY_H
#define SZAKDOLGOZATFS_DIRECTORY_H

#include <vector>
using namespace std;

class SzakdolgozatFs_Directory_Ondisk{
    public:
        unsigned long entryNumber;
        unsigned long blocks[];
};
class SzakdolgozatFs_Directory{
    public:
        unsigned long entryNumber;
        vector<unsigned long> blocks;

    public:
        unsigned char* createRawFile();
        unsigned long getRawSize();
        SzakdolgozatFs_Directory();
};

#endif
