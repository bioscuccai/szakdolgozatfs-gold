#include <cstring>
#include <iostream>

#include "szakdolgozatfs_inode.h"
#include "szakdolgozatfs_util.h"

using namespace std;

SzakdolgozatFs_Inode::SzakdolgozatFs_Inode(char *name_, unsigned long blockListLocation_, unsigned long size_, SzakdolgozatFs_Filetype type_):blockListLocation(blockListLocation_),size(size_),type(type_),gid(0),uid(0),mode(0777){
    strcpy(name, name_);
}
SzakdolgozatFs_Inode::SzakdolgozatFs_Inode(){}
void SzakdolgozatFs_Inode::debugInodeInfo(){
    cout<<"Name: "<<name<<endl;
    //cout<<"First block: "<<firstBlock<<endl;
    cout<<"Size: "<<size<<endl;
    switch(type){
        case PFS_DIR: cout<<"Directory\n"; break;
        case PFS_FILE: cout<<"File\n"; break;
        default: cout<<"Other\n";break;
    }
}
/*
long SzakdolgozatFs_Inode::getRawSize(long sizeInBlocks){
    return 256+(2*sizeof(unsigned long))+sizeof(SzakdolgozatFs_Filetype)+( sizeInBlocks * sizeof(unsigned long));
}

void SzakdolgozatFs_Inode::createRawFile(unsigned char *data, long sizeInBlocks){
    unsigned char *buff=new unsigned char[getRawSize(sizeInBlocks)];
    memcpy(buff, &name, 256);
    memcpy(&buff[256], &firstBlock, sizeof(unsigned long));
    memcpy(&buff[256 + sizeof(unsigned long)], &size, sizeof(unsigned long));
    memcpy(&buff[256 + sizeof(unsigned long) + sizeof(unsigned long)], &type, sizeof(SzakdolgozatFs_Filetype));
    //memcpy(buff[256 + sizeof(unsigned long) +sizeof(SzakdolgozatFs_Filetype)], &size, sizeof(unsigned long));
    for(unsigned int i=0;i<blocks.size();i++){
        memcpy(&buff[256 + sizeof(unsigned long)  + sizeof(unsigned long)+sizeof(SzakdolgozatFs_Filetype) + (i*sizeof(unsigned long))], &blocks.at(i), sizeof(unsigned long));
    }
    charTombKiir(buff, getRawSize(sizeInBlocks));
}*/
