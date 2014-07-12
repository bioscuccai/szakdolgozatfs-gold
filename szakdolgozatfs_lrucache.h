#ifndef SZAKDOLGOZATFS_LRUBLOCKCACHE_H
#define SZAKDOLGOZATFS_LRUBLOCKCACHE_H

#include <map>

#include "szakdolgozatfs_inode.h"
//#include "szakdolgozatfs.h"

using namespace std;

class Cache{
    public:
        int* sorrend;
        int maxEntries;
        int darab;
    public:
        Cache(int me);
        bool containsKey(int k);
        int keyIndex(int k);
        void eloreHoz(int ind);
        ~Cache();
};
class BlockCache: public Cache{
    public:
        //void betesz(int k, int t);

        map<int, unsigned char*> buff;
        //SzakdolgozatFs *fs;
        unsigned long blockSize;
    public:
        BlockCache(int me, int bs);
        void getBejegyzes(int k, unsigned char* ptr);
        void setBejegyzes(int k, unsigned char* e);

};

class InodeCache: public Cache{
    public:
        //void betesz(int k, int t);
        map<int, SzakdolgozatFs_Inode*> buff;
    public:
        InodeCache(int me);
        void getBejegyzes(int k, SzakdolgozatFs_Inode* ptr);
        void setBejegyzes(int k, SzakdolgozatFs_Inode* e);
};


#endif // SZAKDOLGOZATFS_LRUBLOCKCACHE_H
