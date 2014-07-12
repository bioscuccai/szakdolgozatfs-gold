#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <cassert>
#include <sys/statfs.h>
#include <queue>
#include <errno.h>
#include <algorithm>
#include <iterator>

#include "szakdolgozatfs_directory.h"
#include "szakdolgozatfs_util.h"
#include "szakdolgozatfs_inode.h"
#include "szakdolgozatfs.h"

#define MAGIC_HEADER "SzAkDoLgOzAtFs"


#define SZAKDOLGFS_FIRST_FIT 0
#define SZAKDOLGFS_BEST_FIT 0

using namespace std;

SzakdolgozatFs::SzakdolgozatFs():bitmap(NULL),superblock(NULL),blockCache(NULL),inodeCache(NULL),bBlockCacheEnabled(false),bInodeCacheEnabled(false),blockEvent(NULL),bcbh(NULL){
    /*
    blockCache=new map<unsigned long, unsigned char*>();
    blockCacheOrder=new queue<int>();*/
    spaceAlg=SZFS_FIRST_FIT;
}

long SzakdolgozatFs::blocksNeededPerSize(unsigned long size){
    return (size/(superblock->sectorSize * superblock->blockSize))
                        +((size%((superblock->sectorSize) * superblock->blockSize))==0?0:1);
}

void SzakdolgozatFs::loadImage(string file){
    char* szFile=new char[file.size()+1];
    strcpy(szFile, file.c_str());
    this->openImage(szFile);
    this->readSuperblock();
    this->calcFsStats();
    this->readBitmap();

    delete szFile;
}

void SzakdolgozatFs::resetImage(string file, unsigned long sectSize, unsigned long bSize){
    char* szFile=new char[file.size()+1];
    strcpy(szFile, file.c_str());
    this->openImage(szFile);
    this->buildSuperblock(sectSize, bSize);
    this->writeSuperblock();
    this->readSuperblock();
    //this->calcFsStats();
    this->buildBitmap();
    this->writeBitmap();
    this->createRootDirectory();
    delete szFile;
}

SzakdolgozatFs::~SzakdolgozatFs(){
    closeImage();
}

void SzakdolgozatFs::closeImage(){
    imageFile->flush();
    imageFile->close();
}

void SzakdolgozatFs::openImage(char *filename){
    imageFile=new fstream(filename, ios::in|ios::out|ios::binary);
    //if(imageFile->is_open()) cout<<"ok\n";
    //assert(imageFile->is_open());
    //if(!(imageFile->is_open())) throw -EIO;
    imageFile->seekg(0,ios::end);
    imageSize=imageFile->tellg();
    imageFile->seekg(0, ios::beg);
}

void SzakdolgozatFs::buildSuperblock(unsigned long sectSize /* =512 */, unsigned long bSize /* = 1 */){
    superblock=new SzakdolgozatFs_Superblock();

    //egyszer rossz fajlt nyitottam meg, ugy kifagyasztotta a gepem, hogy sem a terminalvaltasra, sem a numlockra nem reagalt
    //ezert szukseg van magic stringre
    strcpy((superblock->magic), MAGIC_HEADER);

    superblock->sectorSize=sectSize;
    superblock->blockSize=bSize;
    numberOfBlocks=imageSize / superblock->sectorSize;
    bitmapSizeBytes=(numberOfBlocks/8)+1;
    bitmapSizeBlocks=(bitmapSizeBytes / ((superblock->sectorSize) * superblock->blockSize) )+1;
    //cerr<<"ss: "<<superblock->sectorSize<<" bs: "<<superblock->blockSize<<endl;
}

void SzakdolgozatFs::calcFsStats(){
    numberOfBlocks=imageSize / superblock->sectorSize;
    bitmapSizeBytes=(numberOfBlocks/8)+1;
    bitmapSizeBlocks=(bitmapSizeBytes / ((superblock->sectorSize) * superblock->blockSize) )+1;
    blockSizeBytes=superblock->blockSize*superblock->sectorSize;
    if(blockCache==NULL) blockCache=new BlockCache(100, blockSizeBytes);
    if(inodeCache==NULL) inodeCache=new InodeCache(100);
    empty=new unsigned char[blockSizeBytes];
    memset(empty, 0, blockSizeBytes);
}
void SzakdolgozatFs::writeSuperblock(){
    imageFile->seekp(0,ios::beg);
    imageFile->write((char*)superblock, sizeof(SzakdolgozatFs_Superblock));
}

void SzakdolgozatFs::debugSuperblock(){
    cout<<"Number of blocks: "<<numberOfBlocks<<endl;
    cout<<"Block size in bytes:"<<((superblock->sectorSize) * superblock->blockSize)<<endl;
    cout<<"Bitmap in bytes: "<<bitmapSizeBytes<<endl;
    cout<<"Bitmap in blocks: "<<bitmapSizeBlocks<<endl;
}

//kozvetlen lemezrol olvasas/iras
void SzakdolgozatFs::readBlock(blockAddr start, unsigned char* ptr){
    imageFile->seekg(0, ios::beg);
    imageFile->seekg(start*blockSizeBytes);
    imageFile->read((char*)ptr, blockSizeBytes);
}
void SzakdolgozatFs::writeBlock(blockAddr start, unsigned long size, unsigned char* ptr){
    //charTombKiir(ptr, blockSizeBytes);

    /*(start<=(superblock->rootNodeBlock) && (start+size-1)>=(superblock->rootNodeBlock)){
            cerr<<"breakpoint ide\n";
        }*/

    imageFile->seekp(0, ios::beg);
    imageFile->seekp(start*blockSizeBytes);
    imageFile->write((char*)ptr, size*blockSizeBytes);
    if(start==superblock->rootNodeBlock){
        //cerr<<"breapoint ide\n";
    }
}

//cache engedelyezesetol fuggoen
void SzakdolgozatFs::getBlock_cache(blockAddr start, unsigned long size, unsigned char* ptr){

    unsigned char *buff=new unsigned char[blockSizeBytes*size];
    for(int bi=start, i=0;bi<start+size;bi++,i++){
        if(blockCache->containsKey(bi)){ //benne van a cache-ben
           // cerr<<bi<<" cache-ben\n";
            unsigned char *cacheContent=new unsigned char[blockSizeBytes];
            blockCache->getBejegyzes(bi, cacheContent);
            memcpy(&buff[i*blockSizeBytes], cacheContent, blockSizeBytes);
            delete cacheContent;
        } else {
            readBlock(bi, &buff[i*blockSizeBytes]);
            blockCache->setBejegyzes(bi, &buff[i*blockSizeBytes]);
       }
    }

    memcpy(ptr, buff, size*blockSizeBytes);
    delete buff;


    /*
================================================
================================================
//cache nelkul

    imageFile->seekg(0);
    imageFile->seekg(start*blockSizeBytes);
    imageFile->read((char*)ptr, size*blockSizeBytes);*/
}

void SzakdolgozatFs::setBlock_cache(blockAddr start, unsigned long size, unsigned char* ptr){
//cache-es resz

    unsigned char *buff=new unsigned char[blockSizeBytes];
    for(int i=0;i<size;i++){
        memcpy(buff, &ptr[i*blockSizeBytes], blockSizeBytes);
        blockCache->setBejegyzes(start+i, buff);
    }
    delete buff;
    writeBlock(start, size, ptr);
/*
    imageFile->seekp(0, ios::beg);
    imageFile->seekp(start*blockSizeBytes);
    imageFile->write((char*)ptr, size*blockSizeBytes);
    */
}

void SzakdolgozatFs::getBlock(blockAddr start, unsigned long size, unsigned char* ptr, bool shouldCache){
    if(shouldCache && bBlockCacheEnabled){
        getBlock_cache(start, size, ptr);
    } else {
        unsigned char *rb=new unsigned char[size*blockSizeBytes];
        for(unsigned long i=0;i<size;i++){
            readBlock(start+i, &rb[i*blockSizeBytes]);
        }
        memcpy(ptr, rb, size*blockSizeBytes);
        delete rb;
    }

    //megfigyeles
    /*
    if(bcbh!=NULL){
        BlockCallbackInfo *bcbi=new BlockCallbackInfo(BEC_GET, shouldCache, start, size);
        bcbh->doCallback(bcbi);
        delete bcbi;
    }*/
    BlockCallbackInfo *bcbi=new BlockCallbackInfo(BEC_GET, shouldCache, start, size);
    for(vector<BlockCallbackHandler*>::iterator it=blockHandlers.begin();it!=blockHandlers.end();it++)
        (*it)->doCallback(bcbi);
    delete bcbi;
}
void SzakdolgozatFs::setBlock(blockAddr start, unsigned long size, unsigned char* ptr, bool shouldCache){
    if(shouldCache && bBlockCacheEnabled){
        setBlock_cache(start, size, ptr);
    } else {
        writeBlock(start, size, ptr);
        //charTombKiir(ptr, size*blockSizeBytes);
    }

    /*
    if(bcbh!=NULL){
        BlockCallbackInfo *bcbi=new BlockCallbackInfo(BEC_SET, shouldCache, start, size);
        bcbh->doCallback(bcbi);
        delete bcbi;
    }*/
    BlockCallbackInfo *bcbi=new BlockCallbackInfo(BEC_GET, shouldCache, start, size);
    for(vector<BlockCallbackHandler*>::iterator it=blockHandlers.begin();it!=blockHandlers.end();it++)
        (*it)->doCallback(bcbi);
    delete bcbi;
}


//it mindenkep az image file-t kell kozvetlen piszkalni, kulonben nem derul ki a blokk meret
void SzakdolgozatFs::readSuperblock(){
    if(superblock==NULL) superblock=new SzakdolgozatFs_Superblock();

    imageFile->seekg(0,ios::beg);
    imageFile->read((char*)superblock, sizeof(SzakdolgozatFs_Superblock));

    //magic string ellenorzes
    //assert(strcmp(superblock->magic, MAGIC_HEADER)==0);
    if(strcmp(superblock->magic, MAGIC_HEADER)!=0) throw -EIO;


/*
    long sbBlockSize=this->blocksNeededPerSize(sizeof(SzakdolgozatFs_Superblock));
    cout<<sbBlockSize<<endl;
    unsigned char* sbBlocks=new unsigned char[sbBlockSize * blockSizeBytes];
    this->getBlock(0,sbBlockSize, sbBlocks);
    memcpy(this->superblock, sbBlocks, sizeof(SzakdolgozatFs_Superblock));
    charTombKiir((unsigned char*)this->superblock, sizeof(SzakdolgozatFs_Superblock));*/
    this->calcFsStats();

    //delete sbBlocks;
}

void SzakdolgozatFs::buildBitmap(){
    bitmap=new unsigned char[bitmapSizeBytes];
    for(int i=0;i<bitmapSizeBytes;i++) bitmap[i]=0;
    setAllocationMapPosition(bitmap, 0, true);
    for(unsigned int i=1;i<1+bitmapSizeBlocks;i++) setAllocationMapPosition(bitmap, i, true);
}
void SzakdolgozatFs::writeBitmap(){
    unsigned char *buff=new unsigned char[bitmapSizeBlocks* blockSizeBytes];
    memset(buff, 0, bitmapSizeBlocks* blockSizeBytes);
    memcpy(buff, bitmap, bitmapSizeBytes);
    this->setBlock(1, bitmapSizeBlocks, buff,true);

    delete buff;
    //eredeti iras
    /*
    imageFile->seekp(0,ios::beg);
    imageFile->seekp(superblock->sectorSize * superblock->blockSize);
    imageFile->write((char*)bitmap, bitmapSizeBytes);*/
}
void SzakdolgozatFs::readBitmap(){
    if(bitmap==NULL) bitmap=new unsigned char[bitmapSizeBytes];

    unsigned char *buff=new unsigned char[bitmapSizeBlocks * blockSizeBytes];
    this->getBlock(1, bitmapSizeBlocks, buff,true);
    memcpy(bitmap, buff, bitmapSizeBytes);
    delete buff;
    //eredeti olvasas
    /*
    imageFile->seekg(0,ios::beg);
    imageFile->seekg(superblock->sectorSize * superblock->blockSize);
    imageFile->read((char*)bitmap, bitmapSizeBytes);*/
}

//az elso blokkot adja vissza
blockAddr SzakdolgozatFs::placeRawFileContentsSingle(unsigned char *content, unsigned long size){
    blockAddr firstBlock;

    if(size==0) return 0;
    long blocksNeeded=blocksNeededPerSize(size);
    firstBlock=lookForSpace(bitmap, blocksNeeded,0, numberOfBlocks-1);
    if(firstBlock==-1) throw -ENOSPC;
    for(unsigned long i=firstBlock;i<firstBlock+blocksNeeded;i++) setAllocationMapPosition(bitmap, i, true);

    unsigned char *buff=new unsigned char[blockSizeBytes * blocksNeededPerSize(size)];
    memset(buff, 0, blockSizeBytes * blocksNeededPerSize(size));
    memcpy(buff, content, size);
    this->setBlock(firstBlock, blocksNeededPerSize(size), buff,true);
    delete buff;

//eredeti iras
/*
    imageFile->seekp(0,ios::beg);
    imageFile->seekp(blockSizeBytes * firstBlock);
    imageFile->write((char*)content, size);*/

    this->writeBitmap();


    return firstBlock;
}

//nincs sehol sem hasznalva
/*void SzakdolgozatFs::allocBitmapSuperblock(){
    superblock=new SzakdolgozatFs_Superblock();
    bitmap=new unsigned char[bitmapSizeBytes];
}*/

void SzakdolgozatFs::createRootDirectory(){
    superblock->rootNodeBlock=createDirectoryFileAndNode("/");
    //cout<<"Root's node's block: "<<superblock->rootNodeBlock<<endl;
    this->writeSuperblock();
}
void SzakdolgozatFs::getInodeFromBlock(blockAddr block, SzakdolgozatFs_Inode *node){
    sendObserverNoticePA("getInode ", block);
    //cache
    if(bInodeCacheEnabled && inodeCache->containsKey(block)){
        inodeCache->getBejegyzes(block, node);
    }
    else{
        //cerr<<"[getinode] no cache: "<<block<<endl;


        unsigned long inodeSizeBlock=blocksNeededPerSize(sizeof(SzakdolgozatFs_Inode));
        unsigned char* buff=new unsigned char[inodeSizeBlock * blockSizeBytes];
        this->getBlock(block, inodeSizeBlock, buff, false);

/*        imageFile->seekg(0,ios::beg);
        imageFile->seekg(block * superblock->blockSize * superblock->sectorSize);
        imageFile->read((char*)node, sizeof(SzakdolgozatFs_Inode));*/

        memcpy(node, buff, sizeof(SzakdolgozatFs_Inode));
        delete buff;


        //cache
        if(bInodeCacheEnabled) inodeCache->setBejegyzes(block, node);
    }
}

void SzakdolgozatFs::readDirectoryFromInodeBlock(blockAddr block, SzakdolgozatFs_Directory *dir){
    sendObserverNoticePA("readDir ",block);
    SzakdolgozatFs_Inode *node=new SzakdolgozatFs_Inode();

    getInodeFromBlock(block, node);
    //node->debugInodeInfo();
    if(node->type!=PFS_DIR){
        //cerr<<"nem kv: "<<block<<endl;
        //if(block==superblock->rootNodeBlock) cerr<<"gaz a gyokerrel\n";
    }
    assert(node->type==PFS_DIR);
    /*imageFile->seekg(ios::beg);
    imageFile->seekg(superblock->blockSize * superblock->sectorSize * (node->firstBlock));*/

    unsigned char *dirImage=new unsigned char[node->size];
    //imageFile->read((char*)dirImage, node->size);
    this->getFileContentsFromInode(block, dirImage);
    //charTombKiir(dirImage, node->size);

    SzakdolgozatFs_Directory_Ondisk *dirOndisk;
    dirOndisk=(SzakdolgozatFs_Directory_Ondisk*)dirImage;

    dir->entryNumber=dirOndisk->entryNumber;
    //cerr<<"all elements b: "<<block<<" n: "<<dir->entryNumber<<endl;
    for(unsigned long i=0;i<dir->entryNumber;i++){
        //cerr<<"[readDirectoryFromInodeBlock] element "<<i<<": "<<dirOndisk->blocks[i]<<endl;
        dir->blocks.push_back(dirOndisk->blocks[i]);
    }

    delete dirImage;
    delete node;
}
void SzakdolgozatFs::printDirectoryContents(string p){
    SzakdolgozatFs_Inode *fileNode=new SzakdolgozatFs_Inode();
    SzakdolgozatFs_Directory *dir=new SzakdolgozatFs_Directory();

    long dirBlock=this->resolveNodeOfFile(p);
    this->readDirectoryFromInodeBlock(dirBlock, dir);
    cout<<dir->entryNumber<<". elements\n";
    for(unsigned int i=0;i<dir->blocks.size();i++){
        this->getInodeFromBlock(dir->blocks.at(i), fileNode);
        cout<<i<<": "<<dir->blocks.at(i)<<" / "<<fileNode->name<<" / "<<fileNode->size<<endl;
    }
    delete dir;
    delete fileNode;
}

blockAddr SzakdolgozatFs::placeInode(SzakdolgozatFs_Inode *node){
    sendObserverNotice("placeNode");
    blockAddr nodePos=lookForSpace(bitmap, blocksNeededPerSize(sizeof(SzakdolgozatFs_Inode)),0, numberOfBlocks-1);
    //long nodePos=lookForSpace(bitmap, 1,0, numberOfBlocks-1);
    //long nodePos=lookForSpace(bitmap, sizeof(SzakdolgozatFs_Inode),0, numberOfBlocks-1);
    setAllocationMapPosition(bitmap, nodePos,true);
    this->writeBitmap();


    unsigned char *buff=new unsigned char[blockSizeBytes * blocksNeededPerSize(sizeof(SzakdolgozatFs_Inode))];
    memset(buff, 0, blockSizeBytes * blocksNeededPerSize(sizeof(SzakdolgozatFs_Inode)));
    memcpy(buff, node, sizeof(SzakdolgozatFs_Inode));
    this->setBlock(nodePos, blocksNeededPerSize(sizeof(SzakdolgozatFs_Inode)), buff, false);
    delete buff;

    //cache
    if(bInodeCacheEnabled) inodeCache->setBejegyzes(nodePos, node);

    return nodePos;
}

blockAddr SzakdolgozatFs::placeFileAndInode(char *name, unsigned char *content, long size){
    long fileBlockListStart;
    long nodeFirstBlock;
    fileBlockListStart=placeRawFileContentsMulti(content, size);
    SzakdolgozatFs_Inode *node=new SzakdolgozatFs_Inode(name,fileBlockListStart,size,PFS_FILE);

    nodeFirstBlock=placeInode(node);

    return nodeFirstBlock;
}

//TODO: overhead az inode lekerese miatt
vector<blockAddr> SzakdolgozatFs::getBlockListFromInodeBlock(unsigned long inodeBlock){
    SzakdolgozatFs_Inode *node=new SzakdolgozatFs_Inode();
    unsigned long* blockList;
    vector<blockAddr> blockVector;

    this->getInodeFromBlock(inodeBlock, node);

    if(node->blockListLocation==0) return blockVector; //ures file eseten
    blockVector.reserve(blocksNeededPerSize(node->size));
    blockList=new unsigned long[blocksNeededPerSize(node->size)];

    //olvalas
    unsigned char* buff=new unsigned char[ blocksNeededPerSize(node->size) * blockSizeBytes];
    this->getBlock(node->blockListLocation, blocksNeededPerSize(node->size), buff, true);
    memcpy(blockList, buff, blocksNeededPerSize(node->size) * sizeof(blockAddr));

    delete buff;
    //olvasas vege
/*
    imageFile->seekg(0,ios::beg);
    imageFile->seekg(node->blockListLocation * blockSizeBytes);
    imageFile->read((char*)blockList, blocksNeededPerSize(node->size)*sizeof(long));
*/

    for(unsigned int i=0;i<blocksNeededPerSize(node->size);i++){
        blockVector.push_back(blockList[i]);
    }

    return blockVector;
}
long SzakdolgozatFs::getFileContentsFromInode(blockAddr nodeBlock, unsigned char* content){
    SzakdolgozatFs_Inode* node=new SzakdolgozatFs_Inode();
    this->getInodeFromBlock(nodeBlock,node);
    unsigned int beolvasva=0;
    unsigned int bm=1024;
    if(node->size==0) return 0;
    while(beolvasva!=node->size){
        unsigned int olvasando=((node->size)-beolvasva)<bm?((node->size)-beolvasva):bm;
        //cerr<<"olvasando: "<<olvasando<<endl;
        doFread(nodeBlock, beolvasva, olvasando, &(content[beolvasva]));
        beolvasva+=olvasando;
    }
    //cerr<<"get contents vegzett\n";
    //delete node;
    return 0;
}
long SzakdolgozatFs::getFileContentsFromInode_2(blockAddr nodeBlock, unsigned char* content){
    SzakdolgozatFs_Inode *node=new SzakdolgozatFs_Inode();
    //unsigned long* blockList;

    long buffSize;
    long bytesRead=0;;
    getInodeFromBlock(nodeBlock, node);

    //0 meretu fajlok eseten
    if(node->size==0){
        content=NULL;
        delete node;
    }

    //cout<<"---------------\n";
    vector<blockAddr> blockVector=this->getBlockListFromInodeBlock(nodeBlock);
    for(unsigned int i=0;i<blockVector.size();i++){
        buffSize=blockSizeBytes;
        //if(i==blockVector.size()-1) buffSize=((node->size) % blockSizeBytes); //utolso blokk
        if(i==blockVector.size()-1){  //ugy tunik a maradek itt nem ugy mukodik ahogy kellene
            buffSize=(node->size - (i*blockSizeBytes));
        }

        bytesRead+=buffSize;

        //cout<<"kell a "<<blockVector.at(i)<<". blokk ("<<buffSize<<")\n";
        //cout<<"bytes to read: "<<buffSize<<endl;
        //cout<<"from: "<<imageFile->tellg()<<endl;




        /*
        imageFile->seekg(0,ios::beg);
        imageFile->seekg(blockVector.at(i)*blockSizeBytes);
        imageFile->read((char*)&content[i*blockSizeBytes], buffSize);
        */
        unsigned char* buff=new unsigned char[blockSizeBytes];
        this->getBlock(blockVector.at(i), 1, buff, true);
        memcpy(&content[i*blockSizeBytes], buff, buffSize);
        delete buff;
    }
    //cout<<"----------------\n";
    //charTombKiir(content, node->size);

    //delete blockList;
    delete node;

    //cout<<"read: "<<bytesRead<<" size: "<<node->size<<endl;
    //assert(bytesRead==node->size);
    if(bytesRead!=node->size) throw -EIO;

    //this->doFread(nodeBlock, 0, (node->size), content);
    return 0;
}

blockAddr SzakdolgozatFs::replaceFileContentsFromInodeMulti(blockAddr nodeBlock, unsigned char *content, long size){
    SzakdolgozatFs_Inode *node=new SzakdolgozatFs_Inode();
    this->getInodeFromBlock(nodeBlock, node);

    vector<unsigned long> blockVector=this->getBlockListFromInodeBlock(nodeBlock);
    //blokk lista torlese
    if(node->blockListLocation!=0){
        for(unsigned long i=0;i<blocksNeededPerSize(blockVector.size()*sizeof(blockAddr));i++){
            setAllocationMapPosition(bitmap, (node->blockListLocation)+i, false);
            if(nodeBlock==(i+node->blockListLocation)){
                //cerr<<"gaz van\n";
            }
        }
        this->writeBitmap();
    }
    //fajl jelenlegi tartalmanak torlese
    for(unsigned long i=0;i<blockVector.size();i++){
        setAllocationMapPosition(bitmap, blockVector.at(i), false);
    }
    this->writeBitmap();

    unsigned long newBlockList=this->placeRawFileContentsMulti(content, size);
    node->blockListLocation=newBlockList;
    node->size=size;
    this->replaceInode(nodeBlock, node);

    delete node;
    return nodeBlock;
}

void SzakdolgozatFs::replaceInode(blockAddr nodeBlock, SzakdolgozatFs_Inode *node){
    //cache
    /*
    if(this->inodeCache.count(nodeBlock)==0){
        SzakdolgozatFs_Inode newNode;
        inodeCache[nodeBlock]=newNode;
    }
    memcpy(&inodeCache[nodeBlock], node, sizeof(SzakdolgozatFs_Inode));
*/
    if(nodeBlock==superblock->rootNodeBlock){
        //cerr<<"breakpoint ide\n";
    }
    unsigned char *buff=new unsigned char[blocksNeededPerSize(sizeof(SzakdolgozatFs_Inode))*blockSizeBytes];
    memset(buff,0,blocksNeededPerSize(sizeof(SzakdolgozatFs_Inode))*blockSizeBytes);
    memcpy(buff, node, sizeof(SzakdolgozatFs_Inode));
    this->setBlock(nodeBlock,blocksNeededPerSize(sizeof(SzakdolgozatFs_Inode)), buff, false);
    delete buff;
    //cache
    if(bInodeCacheEnabled) inodeCache->setBejegyzes(nodeBlock, node);
}
//ezt meg a readDirectoryFromInodeBlock() alapjan
void SzakdolgozatFs::assignInodeToDirectory(blockAddr fileBlock, blockAddr dirBlock){
    SzakdolgozatFs_Directory *dir=new SzakdolgozatFs_Directory();
    unsigned char *newDirImage;
    long newDirSize;

    this->readDirectoryFromInodeBlock(dirBlock, dir);
    dir->blocks.push_back(fileBlock);

    dir->entryNumber++;
    newDirSize=dir->getRawSize();

    newDirImage=new unsigned char[newDirSize];
    newDirImage=dir->createRawFile();

/*
    for(unsigned int i=0;i<dir->firstNodeBlocks.size();i++){
        cout<<">>>uj elem: "<<dir->firstNodeBlocks.at(i)<<endl;
    }
    cout<<">>>uj tartalom: "<<dir->getRawSize()<<endl;
    cout<<">>>uj tomb meret: "<<dir->firstNodeBlocks.size()<<endl;
    cout<<">>>uj raw : ";
    charTombKiir(newDirImage, newDirSize);
*/
    this->replaceFileContentsFromInodeMulti(dirBlock, newDirImage, newDirSize);

    delete newDirImage;
    delete dir;

}

blockAddr SzakdolgozatFs::createDirectoryFileAndNode(char *name){
    SzakdolgozatFs_Directory *dir=new SzakdolgozatFs_Directory();
    unsigned char *db=new unsigned char[dir->getRawSize()];
    db=dir->createRawFile();
    long nodeStart=this->placeFileAndInode(name, db, dir->getRawSize());
    delete db;

    //alapbol file tipusu lesz az uj inode, ezt atirjuk
    SzakdolgozatFs_Inode *node=new SzakdolgozatFs_Inode();

    this->getInodeFromBlock(nodeStart,node);
    node->type=PFS_DIR;
    this->replaceInode(nodeStart, node);

    delete node;
    delete dir;
    return nodeStart;
}

// kezdo es befejezo /-ek nelkul
blockAddr SzakdolgozatFs::resolveNodeOfFile(string name){
    int cikl=0;
    long foundBlock=-1;
    string token;
    //cerr<<"root block: "<<superblock->rootNodeBlock<<" name: "<<name<<endl;
    //cerr<<"eredeti: "<<name<<endl;
    name=cutFirstAndLastSlashes(name);
    //cerr<<"levagva: "<<name<<endl;
    stringstream nameStream(name);
    blockAddr lastDirectory=superblock->rootNodeBlock;

    SzakdolgozatFs_Inode *tempNode=new SzakdolgozatFs_Inode();

    if(name=="/" || name=="") return superblock->rootNodeBlock;

    int nPs=std::count(name.begin(), name.end(), '/');
    string dbp;
    //a tokenben szereplo filet keressuk
    while(getline(nameStream, token, '/')){
        foundBlock=-1;
        if(lastDirectory==-1){
            break;
        }
        //felette levo konyvtar beolvasasa
        SzakdolgozatFs_Directory *tempDir=new SzakdolgozatFs_Directory();
        memset(tempDir,0, sizeof(SzakdolgozatFs_Directory));
        this->readDirectoryFromInodeBlock(lastDirectory, tempDir);
        lastDirectory=-1;
        //ennek a konyvtarnak elemeinek vegigolvasasa

        for(unsigned int i=0;i<tempDir->blocks.size();i++){
            getInodeFromBlock(tempDir->blocks.at(i), tempNode);
            //ha a neve egyezik a token-ben levovel
            if(strcmp(token.c_str(), tempNode->name)==0){
                dbp+="/"+token;
                if(cikl==nPs) foundBlock=tempDir->blocks.at(i);
                //ha konyvtar, akkor ez lesz a kovetkezo amiben szetnezunk
                if(tempNode->type==PFS_DIR){
                    lastDirectory=tempDir->blocks.at(i);
                }
            }
        }
        delete tempDir;

        cikl++;
    }

    delete tempNode;
    //delete tempDir;

    //cout<<"[resolve] eredmeny: "<<foundBlock<<name<<" ---- "<<dbp<<endl;
    return foundBlock;
}

//TODO: nem fix meret
blockAddr SzakdolgozatFs::createFileWithContents(string path, unsigned char *content, long size){
    sendObserverNotice("createFile "+path);
    string fileName=sajat_basename(path);
    string dirName=sajat_dirname(path);
    //gyoker eseten bajok vannak
    if(dirName!="/") dirName=cutFirstAndLastSlashes(dirName);

    blockAddr n=resolveNodeOfFile(path);
    if(n!=-1){
        //cerr<<"[cfqc] "<<n<<" "<<path<<endl;
        throw -EEXIST;
    }

    long dirNode=this->resolveNodeOfFile(dirName);

    long fileNode=this->placeFileAndInode(const_cast<char*>(fileName.c_str()), content, size);
    this->assignInodeToDirectory(fileNode, dirNode);
    return fileNode;
}

vector<blockAddr> SzakdolgozatFs::lookForSpaceMult(long size){
    long blocksNeeded, blocksLeft;
    vector<blockAddr> blocks;
    blocksNeeded=blocksNeededPerSize(size);

    blocks=this->lookForSpaceMultBlocks(blocksNeeded);
    return blocks;
}

vector<blockAddr> SzakdolgozatFs::lookForSpaceMultBlocks(long num){
    unsigned char* bitmapCopy=new unsigned char[bitmapSizeBytes];
    long blocksLeft=num;
    vector<blockAddr> blocks;
    memcpy(bitmapCopy, bitmap, bitmapSizeBytes);
/*
    if(SZAKDOLGFS_FIRST_FIT){
        //elso talalat

        long testSize=num;
        while(blocksLeft!=0){
            long currBlock;
            currBlock=lookForSpace(bitmapCopy, testSize, 0, numberOfBlocks-1);
            if(currBlock!=-1){
                for(long i=0;i<testSize;i++){
                    blocks.push_back(currBlock+i);
                    setAllocationMapPosition(bitmapCopy, currBlock+i, true);
                }
            }
            blocksLeft-=testSize;
        }

    } else if(SZAKDOLGFS_BEST_FIT){
        //legjobb illeszkedes, most mar tenyleg
        long testSize=num;
        while(blocksLeft!=0){
            long currBlock;
            currBlock=lookForMostExactSpace(bitmapCopy, testSize, 0, numberOfBlocks-1);
            if(currBlock!=-1){
                for(long i=0;i<testSize;i++){
                    blocks.push_back(currBlock+i);
                    setAllocationMapPosition(bitmapCopy, currBlock+i, true);
                }
            }
        }
        blocksLeft-=testSize;
    } else {
        //legjobb illeszkedes
        for(long i=0;i<num;i++){
            long currBlock;
            currBlock=lookForSpace(bitmapCopy, 1, 0, numberOfBlocks-1);
            if(currBlock==-1){
                //cerr<<"assert elso talalat i="<<i<<" num="<<num<<endl;
            }

            //TODO: exception ...
            if(currBlock==-1) throw -ENOSPC;

            //assert(currBlock!=-1);
            setAllocationMapPosition(bitmapCopy, currBlock, true);
            blocks.push_back(currBlock);
        }
    }*/

    ///hely algoritmus
    if(spaceAlg==SZFS_FIRST_FIT){
        for(long i=0;i<num;i++){
            long currBlock;
            currBlock=lookForSpace(bitmapCopy, 1, 0, numberOfBlocks-1);
            if(currBlock==-1){
                //cerr<<"assert elso talalat i="<<i<<" num="<<num<<endl;
            }

            if(currBlock==-1) throw -ENOSPC;

            setAllocationMapPosition(bitmapCopy, currBlock, true);
            blocks.push_back(currBlock);
        }
    }

    if(spaceAlg==SZFS_BEST_FIT){
        long testSize=num;
        while(blocksLeft!=0){
            long currBlock;
            currBlock=lookForSpace(bitmapCopy, testSize, 0, numberOfBlocks-1);
            if(currBlock!=-1){
                for(long i=0;i<testSize;i++){
                    blocks.push_back(currBlock+i);
                    setAllocationMapPosition(bitmapCopy, currBlock+i, true);
                }
            } else throw -ENOSPC;
            blocksLeft-=testSize;
        }
    }

    delete bitmapCopy;
    if(blocks.size()!=num){
        //cerr<<"gaz van a asserttel: num="<<num<<"->"<<num*blockSizeBytes <<" size="<<blocks.size()<<endl;
    }
    //assert(blocks.size()==num);
    if(blocks.size()!=num) throw -EIO;
    return blocks;
}

void SzakdolgozatFs::writeBitmapFromBlockList(vector<blockAddr> places){
    for(unsigned int i=0;i<places.size();i++){
        setAllocationMapPosition(bitmap, places.at(i), true);
    }
    this->writeBitmap();
}

blockAddr SzakdolgozatFs::placeBlockList(vector<blockAddr> places){
    long blockListSizeBytes=places.size()*sizeof(blockAddr);
    unsigned char* rawBlockList=new unsigned char[blockListSizeBytes];
    for(unsigned int i=0;i<places.size();i++){
        memcpy(&rawBlockList[i*sizeof(blockAddr)], (unsigned char*)&places.at(i), sizeof(blockAddr));
        //cout<<"blokk elem: "<<(unsigned long)rawBlockList[i*sizeof(unsigned long)]<<endl;
    }
    blockAddr blockListStart=placeRawFileContentsSingle(rawBlockList, blockListSizeBytes);
    //assert(blockListStart!=-1);
    if(blockListStart==-1) throw -ENOSPC;
    delete rawBlockList;
    return blockListStart;
}

//a blokklista kezdopontjat adja vissza
blockAddr SzakdolgozatFs::placeRawFileContentsMulti(unsigned char *content, long size){

    //0 meret eseten
    if(size==0) return 0;

    vector<blockAddr> places;
    places.reserve(blocksNeededPerSize(size));
    places=lookForSpaceMult(size);
    //long blockSize=superblock->blockSize*superblock->sectorSize;
    if(std::count(places.begin(), places.end(), -1)!=0) throw -ENOSPC;


    unsigned char* buff=new unsigned char[blockSizeBytes];
    for(unsigned int i=0;i<places.size();i++){
        long moveable=blockSizeBytes;
        //if(i==places.size()-1) moveable=(size % blockSizeBytes);
        if(i==places.size()-1) moveable=size - (i*blockSizeBytes);
        assert(moveable<=blockSizeBytes);
        memcpy(buff, (unsigned char*)&content[i * blockSizeBytes], moveable);
        //cout<<"File blokk itt: "<<places.at(i)<<endl;

        this->setBlock(places.at(i), 1, buff,true); //a blokk elozo tartalma ugyis elveszne, nem kell atirni az elozot

        //eredeti iras
/*
        imageFile->seekp(0,ios::beg);
        imageFile->seekp(blockSizeBytes * places.at(i));
        imageFile->write((char*)buff, moveable);*/

        //charTombKiir(buff, moveable);

        setAllocationMapPosition(bitmap, places.at(i), true);
        this->writeBitmap();
    }
    delete buff;
    long blockListStart=this->placeBlockList(places);

    return blockListStart;
}

void SzakdolgozatFs::doFread(blockAddr nodeBlock, unsigned long start, unsigned long size, unsigned char *content){
    //try{
    SzakdolgozatFs_Inode *node=new SzakdolgozatFs_Inode();  //csak a hibakezeleshez szukseges az inode
    this->getInodeFromBlock(nodeBlock, node);
    //cout<<"node size: "<<node->size<<endl;
    //assert(node->size>=size);
    //cerr<<"fs: "<<node->size<<endl;
    if(node->size<size) throw -ESPIPE;

    //assert(node->size>=(start+size));
    if(node->size<(start+size)) throw -ESPIPE;


    vector<blockAddr> blockList=this->getBlockListFromInodeBlock(nodeBlock);
    //assert(blockList.size()==blocksNeededPerSize(node->size));
    /*
    if(blockList.size()!=blocksNeededPerSize(node->size)){
        cerr<<"file size: "<<(node->size)<<"list size: "<<blockList.size()<<" needed: "<<blocksNeededPerSize(node->size)<<endl;
        exit(-1);
    }*/
    /*for(unsigned int i=0;i<blockList.size();i++){
        cout<<blockList.at(i)<<" ";
    }


    cout<<endl;*/
    long startingBlock=start / blockSizeBytes;       //a fajl ennyiedik blokkjanal kezdodik
    long startingOffset=start % blockSizeBytes;      //a blokk kezdetetol vett offset

    long endingBlock=(start+size) / blockSizeBytes;  //itt vegzodik
    long endingOffset=(start+size) % blockSizeBytes; //ennyi marad le a vegerol

    //cerr<<"meret: "<<node->size<<"("<<blocksNeededPerSize(node->size)<<") start+size: "<<(start+size)<<"("<<blocksNeededPerSize(start+size)<<")\n";
/*
    if(endingBlock>=blockList.size()){
        cerr<<"eb meret "<<endingBlock<<" "<<blockList.size()<<"\n";
    }*/

    if(endingBlock==blockList.size()){
        endingBlock--;
        endingOffset=blockSizeBytes;
    }
    unsigned int i=0;
    unsigned long bytesRead=0;
    for(long currBlock=startingBlock;currBlock<=endingBlock;currBlock++){
        //cerr<<"c\n";
        if(currBlock>=blockList.size()) break;
        long buffStartOffset=0;
        long buffEndOffset=blockSizeBytes;
        long bytesToRead=blockSizeBytes;

        if(currBlock==startingBlock){
            buffStartOffset=startingOffset;
            bytesToRead-=buffStartOffset;
        }
        if(currBlock==endingBlock){
            buffEndOffset=endingOffset;
            bytesToRead-=(blockSizeBytes-buffEndOffset);
        }

        //cout<<"reading block ["<<currBlock<<"]("<<blockList.at(i)<<") "<<buffStartOffset<<" - "<<buffEndOffset<<endl;
        /*cout<<"reading block ["<<currBlock<<" / "<<blockList.at(currBlock)<<"]("<<bytesToRead<<") "<<buffStartOffset<<" - "<<buffEndOffset<<endl;
        cout<<bytesRead<<endl;
        cout<<"reading from: "<<(blockList.at(currBlock)*blockSizeBytes) + buffStartOffset<<endl;*/

        unsigned char* buff=new unsigned char[blockSizeBytes];

        this->getBlock(blockList.at(currBlock), 1, buff,true);
        memcpy(&content[bytesRead], &buff[buffStartOffset], bytesToRead);
/*
        imageFile->seekg(0,ios::beg);
        imageFile->seekg((blockList.at(currBlock)*blockSizeBytes)+buffStartOffset);
        imageFile->read((char*)(&content[bytesRead]), bytesToRead);
*/
        bytesRead+=bytesToRead;
        i++;

        delete buff;
        //cerr<<"c vege\n";
    }

    delete node;
/*
    } catch(...){
        cerr<<"doFread\n";
        exit(-1);
    }*/
}

void SzakdolgozatFs::increaseFileSize(blockAddr nodeBlock, unsigned long size){
    //meret kibovitese
    SzakdolgozatFs_Inode *node=new SzakdolgozatFs_Inode();
    vector<blockAddr> blockList=this->getBlockListFromInodeBlock(nodeBlock);
    this->getInodeFromBlock(nodeBlock, node);

    //cout<<"[inc]old size: "<<(node->size)<<" new size: "<<size<<endl;
    assert(size>=(node->size));

    //utolso nem teljesen lefoglalt blokk vegen levo szemet letorlese
    long leftover=this->blockSizeBytes - (node->size % this->blockSizeBytes);
    if(leftover!=blockSizeBytes && node->blockListLocation!=0){  //0 meret eseten a blockList ures, meg amugy sincs feleslegesen lefoglalt hely
        long lastBlockOffset=(node->size % this->blockSizeBytes);
       // cerr<<"[incr] hozzafuzes "<<leftover<<endl;
        unsigned char *buff=new unsigned char[blockSizeBytes];
        this->getBlock(blockList.at(blockList.size()-1), 1, buff,true); //eredeti tartalma
        memcpy(&buff[lastBlockOffset], this->empty, leftover); //veget kinullazuk
        this->setBlock(blockList.at(blockList.size()-1), 1, buff,true);
        delete buff;
        //eredeti iras
        /*
        imageFile->seekp(0, ios::beg);
        imageFile->seekp((blockList.at(blockList.size()-1) * this->blockSizeBytes) + lastBlockOffset );
        imageFile->write((char*)this->empty, leftover);*/
    }

    //tobbi blokk lefoglalasa
    long oldSizeInBlocks=this->blocksNeededPerSize(node->size);
    long newSizeInBlocks=this->blocksNeededPerSize(size);

    long sizeDiff=newSizeInBlocks - oldSizeInBlocks;
    if(sizeDiff!=0){
        vector<blockAddr> extraBlocks=lookForSpaceMultBlocks(sizeDiff);
        //cerr<<"[incr] "<<sizeDiff<<" blokk hozzafuzese\n";
        //eredeti blokk lista letorlese
        /*long blockListSizeInBlocks=this->blocksNeededPerSize(this->blocksNeededPerSize(node->size)*sizeof(unsigned long));
        for(unsigned long i=0;i<blockListSizeInBlocks;i++){
            setAllocationMapPosition(bitmap, node->blockListLocation+i, false);
        }
        this->writeBitmap();*/

        //uj blokkok hozzafuzese es a terulet lenullazasa
        for(unsigned int i=0;i<extraBlocks.size();i++){
            assert(extraBlocks.at(i)!=-1);
            blockList.push_back(extraBlocks.at(i));
            //cout<<"nullaz "<<extraBlocks.at(i)<<endl;

            this->setBlock(extraBlocks.at(i), 1, empty,true);
            //eredeti blokk nullazas
            /*
            imageFile->seekp(0, ios::beg);
            imageFile->seekp(extraBlocks.at(i) * blockSizeBytes);
            imageFile->write((char*)empty, blockSizeBytes);*/
        }
        this->writeBitmapFromBlockList(blockList);

        assert(blockList.size()==blocksNeededPerSize(size));

        //long blockListStart=this->placeBlockList(blockList);
        blockAddr blockListStart=this->replaceFileBlockList(nodeBlock, blockList);

        //for(unsigned int i=0;i<blockList.size();i++) cout<<"---"<<blockList.at(i)<<endl;
        //cout<<"bl start: "<<blockListStart<<endl;
        node->blockListLocation=blockListStart;
    }
    node->size=size;
    this->replaceInode(nodeBlock, node);


    delete node;
    assert(this->blocksNeededPerSize(node->size) == blockList.size());
}


void SzakdolgozatFs::decreaseFileSize(blockAddr nodeBlock, long size){
    SzakdolgozatFs_Inode *node=new SzakdolgozatFs_Inode();
    vector<blockAddr> blockList=this->getBlockListFromInodeBlock(nodeBlock);
    vector<blockAddr> keptBlocks;
    keptBlocks.reserve(blocksNeededPerSize(size));
    this->getInodeFromBlock(nodeBlock, node);

    long newSizeInBlocks=this->blocksNeededPerSize(size);

    assert(size<=node->size);
    if(size==node->size) return;

    blockAddr blockListStart=0;
    if(size!=0){
        //megmaradt blokkok megtartasa
        try{
        for(unsigned int i=0;i<newSizeInBlocks;i++){
            keptBlocks.push_back(blockList.at(i));
        }
        }catch(...){
            //cerr<<"itt\n";
            return;
        }
        //torlendo blokkok felszabaditasa
        for(unsigned int i=newSizeInBlocks;i<blocksNeededPerSize(node->size);i++){
            setAllocationMapPosition(bitmap, blockList.at(i), false);
        }

        this->writeBitmap();
        //blockListStart=this->placeBlockList(keptBlocks);
        blockListStart=this->replaceFileBlockList(nodeBlock, keptBlocks);

    } else if(node->blockListLocation!=0){ //fajl urites eseten nullazza a blokklistat es a blokkokat
        //blokkok
        for(unsigned int i=0;i<blocksNeededPerSize(node->size);i++){
            setAllocationMapPosition(bitmap, blockList.at(i),false);
        }
        //blokklista
        for(int i=0;i<blocksNeededPerSize(sizeof(blockAddr)*blockList.size());i++){
            setAllocationMapPosition(bitmap, (node->blockListLocation) + i, false);
        }
        this->writeBitmap();
    }
    node->size=size;
    node->blockListLocation=blockListStart;

    //node->debugInodeInfo();

    this->replaceInode(nodeBlock, node);

    delete node;
}

void SzakdolgozatFs::doFwrite(blockAddr nodeBlock, unsigned long start, unsigned long size, unsigned char* content){
    SzakdolgozatFs_Inode *node=new SzakdolgozatFs_Inode();

    this->getInodeFromBlock(nodeBlock, node);

    unsigned long newSize=((start+size) > node->size)?(start+size):(node->size);
    long oldSizeInBlocks=this->blocksNeededPerSize(node->size);
    long newSizeInBlocks=this->blocksNeededPerSize(newSize);

    assert(newSizeInBlocks>=oldSizeInBlocks);
    //if(newSizeInBlocks>=oldSizeInBlocks) throw -1;

    //cout<<"old / new size in blocks: "<<this->blocksNeededPerSize(node->size)<<" / "<<this->blocksNeededPerSize(newSize)<<endl;

    //ez csak a blokk meretevel foglalkozik
    long sizeDiff=newSizeInBlocks - oldSizeInBlocks;
    if(sizeDiff!=0){
        //cout<<"size diff: "<<sizeDiff<<"old size: "<<node->size<<"new size:"<<newSize<<endl;
        this->increaseFileSize(nodeBlock, newSize);
        this->getInodeFromBlock(nodeBlock, node);

        //cout<<"#meret iras utan: "<<node->size<<endl;
        assert(node->size==start+size);
        //cerr<<"[FWRITE] sizediff nem 0\n";
    } else if(newSize>node->size){ //ha a fajl merete no, de a blokkok szama nem
        node->size=newSize;
        this->replaceInode(nodeBlock, node);
    }

    vector<blockAddr> blockList=this->getBlockListFromInodeBlock(nodeBlock);
    long startingBlock=start / blockSizeBytes; //a fajl ennyiedik blokkjanal kezdodik
    long startingOffset=start % blockSizeBytes;

    long endingBlock=(start+size) / blockSizeBytes;
    long endingOffset=(start+size) % blockSizeBytes;

    unsigned int i=0;
    unsigned long bytesWritten=0;

    for(long currBlock=startingBlock;currBlock<=endingBlock;currBlock++){

        if(currBlock>=blockList.size()) break;

        long buffStartOffset=0;
        long buffEndOffset=blockSizeBytes;
        long bytesToWrite=blockSizeBytes;

        if(currBlock==startingBlock){
            buffStartOffset=startingOffset;
            bytesToWrite-=buffStartOffset;
        }
        if(currBlock==endingBlock){
            buffEndOffset=endingOffset;
            bytesToWrite-=(blockSizeBytes-buffEndOffset);
        }

        //cout<<"writing block ["<<currBlock<<"]("<<bytesToWrite<<") "<<buffStartOffset<<" - "<<buffEndOffset<<endl;

        //ha nem a blokk elejerol kezdodik az iras
        if(bytesToWrite!=blockSizeBytes){
            unsigned char* writeBuff=new unsigned char[blockSizeBytes];
            this->getBlock(blockList.at(currBlock), 1, writeBuff,true);//atmasoljuk a jelenlegi tartalmat, hogy a tobbi reszt megtartsuk
            memcpy(&(writeBuff[buffStartOffset]),&(content[bytesWritten]), bytesToWrite); //amit eredetileg masolni akartunk

            this->setBlock(blockList.at(currBlock), 1, writeBuff,true);
            delete writeBuff;
        }else{
            unsigned char* wb=new unsigned char[bytesToWrite];
            memcpy(&(wb[0]), &(content[bytesWritten]), bytesToWrite);
            this->setBlock(blockList.at(currBlock), 1, wb, true);
            delete wb;
            //charTombKiir(&content[bytesWritten], bytesToWrite);
        }

        //eredeti iras
/*
        imageFile->seekp(0,ios::beg);
        imageFile->seekp((blockList.at(currBlock)*blockSizeBytes) + buffStartOffset);
        imageFile->write((char*)&content[bytesWritten], bytesToWrite);
*/

        bytesWritten+=bytesToWrite;
        i++;
    }


}

blockAddr SzakdolgozatFs::replaceFileBlockList(blockAddr nodeBlock, vector<blockAddr> places){
    SzakdolgozatFs_Inode *node=new SzakdolgozatFs_Inode();

    this->getInodeFromBlock(nodeBlock, node);
    vector<blockAddr> blockList=this->getBlockListFromInodeBlock(nodeBlock);
    long blockListSizeInBlocks=this->blocksNeededPerSize(blockList.size() * sizeof(blockAddr));

    //ha nem ures a file akkor a blokk listat lenullazzuk
    if(node->size!=0){
        for(unsigned int i=0;i<blockListSizeInBlocks;i++){
            setAllocationMapPosition(this->bitmap, node->blockListLocation+i, false);
        }
        this->writeBitmap();
    }

    //ha nem akarjuk lenullazni a filet, akkor kiirjuk a blokklistat
    long blockListStart=0;
    if(places.size()!=0){
        blockListStart=this->placeBlockList(places);
    }

    node->blockListLocation=blockListStart;

    this->replaceInode(nodeBlock, node);

    delete node;

    return blockListStart;

}

void SzakdolgozatFs::removeFileFromDirectory(blockAddr fileBlock, blockAddr dirBlock){
    //konyvtarbol kivetel az assign alapjan
    SzakdolgozatFs_Directory *dir=new SzakdolgozatFs_Directory();
    unsigned int fileIndex=-1;

    this->readDirectoryFromInodeBlock(dirBlock, dir);
    for(unsigned int i=0;i<dir->blocks.size();i++){
        if(dir->blocks.at(i) == fileBlock) fileIndex=i;
    }
    if(fileIndex!=-1){
        dir->blocks.erase(dir->blocks.begin() +fileIndex);
        dir->entryNumber--;
    }
    unsigned char* db=new unsigned char[dir->getRawSize()];
    db=dir->createRawFile();
    this->replaceFileContentsFromInodeMulti(dirBlock, db, dir->getRawSize());
    delete db;
    //vector<blockAddr> fileBlockList=this->getBlockListFromInodeBlock(fileBlock);

}

void SzakdolgozatFs::deleteFile(blockAddr fileBlock){
    sendObserverNoticePA("delete ",fileBlock);
    SzakdolgozatFs_Inode *node=new SzakdolgozatFs_Inode();
    this->getInodeFromBlock(fileBlock, node);
    long fileSizeInBlocks=blocksNeededPerSize(node->size);
    long blockListSizeInBlocks=blocksNeededPerSize( fileSizeInBlocks* sizeof(blockAddr) );

    vector<blockAddr> blockList=this->getBlockListFromInodeBlock(fileBlock);

    //blokk lista torlese
    for(int i=0;i<blockListSizeInBlocks;i++){
        setAllocationMapPosition(bitmap, i + node->blockListLocation,false);
    }
    this->writeBitmap();

    //file blokkok torlese
    for(int i=0;i<blockList.size();i++){
        setAllocationMapPosition(bitmap, blockList.at(i), false);
    }
    this->writeBitmap();

    //inode blokk torlese
    setAllocationMapPosition(bitmap, fileBlock, false);
    this->writeBitmap();

    delete node;
}

long SzakdolgozatFs::copyRealFileToImage(string realName, string imageName){
    char *szReal=new char[realName.size()+1];
    strcpy(szReal, realName.c_str());
    fstream *f=new fstream(szReal, ios::in|ios::binary);
    f->seekg(0,ios::end);
    long size=f->tellg();
    f->seekg(0,ios::beg);
    unsigned char* content=new unsigned char[size];
    f->read((char*)content, size);
    f->close();
    long newNode=this->createFileWithContents(imageName, content, size);
    //long fileNode=this->placeFileAndInode("k", content, size);
    delete content;
    return  newNode;
}

blockAddr SzakdolgozatFs::createDirectory(string path){
    sendObserverNotice("createDir "+path);
    string parentDirName=sajat_dirname(path);
    string dirName=sajat_basename(path);

    //cout<<"parent: '"<<parentDirName<<"'\n";
    //cout<<"dirName: "<<dirName<<endl;

    long parentDirBlock=this->resolveNodeOfFile(parentDirName);
    assert(parentDirBlock!=-1);
    char* szDirName=new char[dirName.length()+1];
    strcpy(szDirName, dirName.c_str());
    //cout<<"szDirName: "<<szDirName<<endl;
    long dirBlock=this->createDirectoryFileAndNode(szDirName);
    assert(dirBlock!=-1);

    this->assignInodeToDirectory(dirBlock, parentDirBlock);

    delete szDirName;
    return dirBlock;
}

void SzakdolgozatFs::renameFile(string oldPath, string newName){
    blockAddr nodeBlock=this->resolveNodeOfFile(oldPath);
    assert(nodeBlock!=-1);
    SzakdolgozatFs_Inode* node=new SzakdolgozatFs_Inode();
    this->getInodeFromBlock(nodeBlock, node);
    strcpy(node->name, newName.c_str());
    this->replaceInode(nodeBlock, node);

    delete node;
}

void SzakdolgozatFs::getFreeAndUsedBlocks(unsigned long *f, unsigned long *u){
    for(unsigned int i=0;i<numberOfBlocks;i++){
        if(getAllocationMapPosition(bitmap, i)) (*u)++;
        else (*f)++;
    }
}

void SzakdolgozatFs::setMTime(string p, time_t newTime){
    SzakdolgozatFs_Inode *node=new SzakdolgozatFs_Inode();
    blockAddr nodeBlock=resolveNodeOfFile(p);
    getInodeFromBlock(nodeBlock, node);
    node->lastModification=newTime;
    replaceInode(nodeBlock, node);

    delete node;
}

void SzakdolgozatFs::setATime(string p, time_t newTime){
    if(!lastAccessTimeLogged) return;
    SzakdolgozatFs_Inode *node=new SzakdolgozatFs_Inode();
    blockAddr nodeBlock=resolveNodeOfFile(p);
    getInodeFromBlock(nodeBlock, node);
    node->lastAccess=newTime;
    replaceInode(nodeBlock, node);

    delete node;
}

void SzakdolgozatFs::chmod(string p, mode_t newMode){
    SzakdolgozatFs_Inode *node=new SzakdolgozatFs_Inode();
    blockAddr nodeBlock=resolveNodeOfFile(p);
    getInodeFromBlock(nodeBlock, node);
    node->mode=newMode;
    replaceInode(nodeBlock, node);

    delete node;
}
void SzakdolgozatFs::chown(string p, uid_t uid, gid_t gid){
    SzakdolgozatFs_Inode *node=new SzakdolgozatFs_Inode();
    blockAddr nodeBlock=resolveNodeOfFile(p);
    getInodeFromBlock(nodeBlock, node);
    node->uid=uid;
    node->gid=gid;
    replaceInode(nodeBlock, node);

    delete node;
}
void SzakdolgozatFs::sendObserverNotice(string msg){
    if(bcbh!=NULL) bcbh->doNotice(msg);
}

void SzakdolgozatFs::sendObserverNoticePA(string msg, blockAddr a){
    stringstream ss;
    ss<<msg;
    ss<<a;
    for(vector<BlockCallbackHandler*>::iterator it=blockHandlers.begin();it!=blockHandlers.end();it++)
        (*it)->doNotice(ss.str());
}
BlockCallbackInfo::BlockCallbackInfo(BlockCallbackType t, bool c, blockAddr st, blockAddr si):type(t),cached(c),start(st),size(si){
}

void BlockCallbackHandler::doCallback(BlockCallbackInfo* i){}
void BlockCallbackHandler::doNotice(string msg){}

void SzakdolgozatFs::addBlockHandler(BlockCallbackHandler* b){
    blockHandlers.push_back(b);
}

void SzakdolgozatFs::removeBlockHandler(BlockCallbackHandler* b){
    for(vector<BlockCallbackHandler*>::iterator it=blockHandlers.begin();it!=blockHandlers.end();it++){
        if(*it==b){
            blockHandlers.erase(it);
            break;
        }
    }
}

void SzakdolgozatFs::moveFile(string filePath, string dirPath){
    blockAddr fileNode=  this->resolveNodeOfFile(filePath);
    blockAddr newDirNode=this->resolveNodeOfFile(dirPath);
    blockAddr oldDirNode=this->resolveNodeOfFile(parentFromPath(filePath));
    this->removeFileFromDirectory(fileNode, oldDirNode);
    this->assignInodeToDirectory(fileNode, newDirNode);
}
