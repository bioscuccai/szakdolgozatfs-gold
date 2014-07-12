#include "szakdolgozatfs_directory.h"
#include "szakdolgozatfs_util.h"

#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

unsigned char* SzakdolgozatFs_Directory::createRawFile(){
    int size=sizeof(entryNumber)+(sizeof(unsigned long)*entryNumber);
    unsigned char *raw=(unsigned char*)malloc(size);
    memcpy(&raw[0], &entryNumber, sizeof(entryNumber));
    for(unsigned int i=0;i<blocks.size();i++){
        memcpy(&raw[sizeof(unsigned long) + i*sizeof(unsigned long)], &blocks.at(i),sizeof(unsigned long));
    }
    //charTombKiir(raw, getRawSize());
    return raw;
}
unsigned long SzakdolgozatFs_Directory::getRawSize(){
    return sizeof(entryNumber)+(sizeof(unsigned long)*entryNumber);
}
SzakdolgozatFs_Directory::SzakdolgozatFs_Directory():entryNumber(0){}
