#include <cassert>
#include <iostream>
#include <cerrno>

using namespace std;

#include "szakdolgozatfs_filehandle.h"
#include "szakdolgozatfs_util.h"

void SzakdolgozatFs_FileHandle::read(unsigned char *ptr, unsigned long size){
    assert(nodeBlock!=-1);
    fs->doFread(nodeBlock, seekGetPos, size, ptr);
}

void SzakdolgozatFs_FileHandle::write(unsigned char *ptr, unsigned long size){
    assert(nodeBlock!=-1);
    fs->doFwrite(nodeBlock, seekPutPos, size, ptr);
}

void SzakdolgozatFs_FileHandle::seekg(unsigned long pos){
    seekGetPos=pos;
}

void SzakdolgozatFs_FileHandle::seekp(unsigned long pos){
    seekPutPos=pos;
}

unsigned long SzakdolgozatFs_FileHandle::tellg(){
    return seekGetPos;
}

unsigned long SzakdolgozatFs_FileHandle::tellp(){
    return seekPutPos;
}

void SzakdolgozatFs_FileHandle::touch(){
    if(fs->resolveNodeOfFile(path)==-1){
    //if(nodeBlock==-1){
        //cerr<<"[touch fn] "<<path<<endl;
        nodeBlock=fs->createFileWithContents(path,NULL,0);
        //cerr<<"[touch] "<<nodeBlock<<endl;
        isOpen=true;
    } else {
        fs->decreaseFileSize(nodeBlock, 0);
    }
}

void SzakdolgozatFs_FileHandle::open(){
    nodeBlock=fs->resolveNodeOfFile(path);
    if(nodeBlock!=-1) isOpen=true;
    else isOpen=false;
}

unsigned long SzakdolgozatFs_FileHandle::getSize(){
    //cerr<<"[getSize] "<<path<<endl;
    assert(nodeBlock!=-1);
    SzakdolgozatFs_Inode* node=new SzakdolgozatFs_Inode();
    fs->getInodeFromBlock(nodeBlock, node);
    unsigned long size=node->size;
    delete node;
    return size;
}

void SzakdolgozatFs_FileHandle::replaceContents(unsigned char* ptr, long size){
    assert(nodeBlock!=-1);
    fs->replaceFileContentsFromInodeMulti(nodeBlock, ptr, size);
}
void SzakdolgozatFs_FileHandle::getContents(unsigned char* ptr){
    assert(nodeBlock!=-1);
    fs->getFileContentsFromInode(nodeBlock, ptr);
}

void SzakdolgozatFs_FileHandle::deleteFile(){
    assert(nodeBlock!=-1);
    unsigned long dirBlock=fs->resolveNodeOfFile(sajat_dirname(path));
    assert(dirBlock!=-1);
    if(getType()==PFS_DIR && getSize()!=sizeof(unsigned long)) throw -ENOTEMPTY;
    fs->removeFileFromDirectory(nodeBlock, dirBlock);
    fs->deleteFile(nodeBlock);

    nodeBlock=-1;
    isOpen=false;
}

SzakdolgozatFs_Filetype SzakdolgozatFs_FileHandle::getType(){
    if(nodeBlock==-1) cerr<<"[fopen] -1 inode "<<path<<endl;
    assert(nodeBlock!=-1);
    SzakdolgozatFs_Inode* node=new SzakdolgozatFs_Inode();
    fs->getInodeFromBlock(nodeBlock, node);
    SzakdolgozatFs_Filetype ftype=node->type;

    delete node;
    return ftype;
}

unsigned long SzakdolgozatFs_FileHandle::getNodeBlock(){
    return nodeBlock;
}

void SzakdolgozatFs_FileHandle::rename(string newName){
    fs->renameFile(path, newName);
}

void SzakdolgozatFs_FileHandle::setATime(time_t newTime){
    fs->setATime(path, newTime);
}
void SzakdolgozatFs_FileHandle::setMTime(time_t newTime){
    fs->setMTime(path, newTime);
}
void SzakdolgozatFs_FileHandle::chmod(mode_t newMode){
    fs->chmod(path, newMode);
}
void SzakdolgozatFs_FileHandle::chown(uid_t uid, gid_t gid){
    fs->chown(path, uid, gid);
}

void SzakdolgozatFs_FileHandle::move(string newDir){
    fs->moveFile(path, newDir);
}

SzakdolgozatFs_FileHandle::SzakdolgozatFs_FileHandle(SzakdolgozatFs* fs_, string path_):nodeBlock(-1),isOpen(false),fs(fs_),path(path_),
    seekGetPos(0),seekPutPos(0){}
