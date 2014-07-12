#ifndef SZAKDOLGOZATFS_UTIL_H
#define SZAKDOLGOZATFS_UTIL_H 1

#include <string>

using namespace std;

typedef unsigned long blockType;

enum SzakdolgozatFs_Filetype{PFS_FILE=0,PFS_DIR=1};

void charTombKiir(unsigned char *t, long n);
void setAllocationMapPosition(unsigned char *bitmap, unsigned long blockNum, bool status);

bool getAllocationMapPosition(unsigned char *bitmap, unsigned long blockNum);
unsigned long lookForSpace(unsigned char *bitmap, unsigned long holeSize, unsigned long firstBlock, unsigned long lastBlock);
int lookForMostExactSpace(unsigned char *bitmap, int holeSize, int firstBlock, int lastBlock);


string sajat_basename(string path);
string sajat_dirname(string path);
string cutFirstAndLastSlashes(string path);
void printBitmap(unsigned char* bitmap, long size);
string parentFromPath(string path);
#endif
