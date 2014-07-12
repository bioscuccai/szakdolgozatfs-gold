#ifndef SZAKDOLGOZATFS_H
#define SZAKDOLGOZATFS_H

#include <vector>
#include <fstream>
#include <map>
#include <queue>
#include <sys/stat.h>

#include "szakdolgozatfs_inode.h"
#include "szakdolgozatfs_directory.h"
#include "szakdolgozatfs_lrucache.h"

using namespace std;

typedef unsigned long blockAddr;

enum BlockCallbackType{BEC_GET, BEC_SET};
enum SpaceAlg{SZFS_BEST_FIT=0, SZFS_FIRST_FIT=1};


class BlockCallbackInfo{
    public:
        BlockCallbackType type;
        bool cached;
        blockAddr start;
        blockAddr size;
    public:
        BlockCallbackInfo(BlockCallbackType t, bool c, blockAddr st, blockAddr si);
};


class BlockCallbackHandler{
    public:
        virtual void doCallback(BlockCallbackInfo* i);
        virtual void doNotice(string msg);
};
class SzakdolgozatFs_Superblock{
    public:
        char magic[15];
        unsigned int sectorSize;
        unsigned int blockSize;
        unsigned long diskSize;
        blockAddr rootNodeBlock;
};

class SzakdolgozatFs{
    public:
        fstream *imageFile;
        unsigned char *bitmap;
        SzakdolgozatFs_Superblock *superblock;
        unsigned long imageSize;
        unsigned long numberOfBlocks;
        unsigned long bitmapSizeBytes;
        unsigned long bitmapSizeBlocks;
        unsigned long blockSizeBytes;

        unsigned char *empty;

        /*map<unsigned long, unsigned char*> *blockCache;
        queue<int> *blockCacheOrder;*/

        BlockCache *blockCache;
        InodeCache *inodeCache;

        bool bBlockCacheEnabled;
        bool bInodeCacheEnabled;

        void (*blockEvent)(BlockCallbackInfo);
        BlockCallbackHandler *bcbh;
        vector<BlockCallbackHandler*> blockHandlers;

        bool lastAccessTimeLogged;
        SpaceAlg spaceAlg;

    public:

        void addBlockHandler(BlockCallbackHandler* b);
        void removeBlockHandler(BlockCallbackHandler* b);

        SzakdolgozatFs();
        ~SzakdolgozatFs();
        void openImage(char *fileName);
        void calcFsStats();
        //void allocBitmapSuperblock();
        void loadImage(string file);     //meglevo image betoltese
        void resetImage(string file, unsigned long sectSize=512, unsigned long bSize=1);    //image lenullazasa
        void closeImage();

        void readBlock(unsigned long start, unsigned char* ptr);
        void writeBlock(unsigned long start, unsigned long size, unsigned char* ptr);

        void getBlock_cache(unsigned long start, unsigned long size, unsigned char* ptr);
        void setBlock_cache(unsigned long start, unsigned long size, unsigned char* ptr);

        void getBlock(unsigned long start, unsigned long size, unsigned char* ptr, bool shouldCache);
        void setBlock(unsigned long start, unsigned long size, unsigned char* ptr, bool shouldCache);

        vector<blockAddr> lookForSpaceMult(long size);
        vector<blockAddr> lookForSpaceMultBlocks(long blocks);

        long blocksNeededPerSize(unsigned long size);
        void buildSuperblock(unsigned long sectSize=512, unsigned long bSize=1);
        void writeSuperblock();
        void debugSuperblock();
        void readSuperblock();

        void createRootDirectory();

        void buildBitmap();
        void writeBitmap();
        void readBitmap();


        void doFread(blockAddr nodeBlock, unsigned long start, unsigned long size, unsigned char *content);
        void doFwrite(blockAddr nodeBlock, unsigned long start, unsigned long size, unsigned char *content);
        //inodehoz es blokk listahoz
        blockAddr placeRawFileContentsSingle(unsigned char* content, unsigned long size);
        //minden mashoz
        blockAddr placeRawFileContentsMulti(unsigned char *content, long size);
        blockAddr placeFileAndInode(char* name, unsigned char* contents, long size);
        blockAddr placeInode(SzakdolgozatFs_Inode *node);

        void printDirectoryContents(string d);
        void readDirectoryFromInodeBlock(blockAddr block, SzakdolgozatFs_Directory *dir);
        void assignInodeToDirectory(blockAddr fileBlock, blockAddr dirBlock);
        blockAddr createDirectoryFileAndNode(char *name);


        void getInodeFromBlock(blockAddr block, SzakdolgozatFs_Inode *node);
        long getFileContentsFromInode(blockAddr nodeBlock,unsigned char* content);
        long getFileContentsFromInode_2(blockAddr nodeBlock,unsigned char* content);
        //inode es blokk lista
        blockAddr replaceFileContentsFromInodeSingle(blockAddr nodeBlock, unsigned char* content, long size);
        //minden mas
        blockAddr replaceFileContentsFromInodeMulti(blockAddr nodeBlock, unsigned char* content, long size);
        void replaceInode(blockAddr nodeBlock, SzakdolgozatFs_Inode *node);

        blockAddr resolveNodeOfFile(string name);

        blockAddr createFileWithContents(string path, unsigned char *content, long size);

        void writeBitmapFromBlockList(vector<unsigned long> places);

        vector<blockAddr> getBlockListFromInodeBlock(blockAddr inodeBlock);

        void removeFileFromDirectory(blockAddr fileBlock, blockAddr dirBlock);
        void deleteFile(blockAddr fileBlock);

        long copyRealFileToImage(string realName, string imageName);

        void updateFileSizeAndBlockList(long nodeBlock, long size, vector<unsigned long> blockList);

        blockAddr placeBlockList(vector<blockAddr> places);


        void increaseFileSize(blockAddr nodeBlock, unsigned long size);
        void decreaseFileSize(blockAddr nodeBlock, long size);

        blockAddr replaceFileBlockList(blockAddr nodeBlock, vector<blockAddr> places);

        void touch(string filePath);

        blockAddr createDirectory(string path);
        void renameFile(string oldPath, string newName);

        void getFreeAndUsedBlocks(unsigned long *f, unsigned long *u);

        void setATime(string p, time_t newTime);
        void setMTime(string p, time_t newTime);
        void chmod(string p, mode_t newMode);
        void chown(string p, uid_t uid, gid_t gid);

        void sendObserverNotice(string msg);
        void sendObserverNoticePA(string msg, blockAddr a);

        void moveFile(string filePath, string dirPath);
};


#endif
