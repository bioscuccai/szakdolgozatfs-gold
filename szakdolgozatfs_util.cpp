#include "szakdolgozatfs_util.h"
#include <iostream>
#include <sstream>

using namespace std;

void charTombKiir(unsigned char *t, long n){
    cout<<"[";
    for(long i=0;i<n;i++){
        if((i%512)==0) cout<<" | ";
        if(t[i]<' ') cout<<"("<<(int)t[i]<<")";
        else cout<<t[i];
    }
    cout<<"]\n";
}
void setAllocationMapPosition(unsigned char *bitmap, unsigned long blockNum, bool status){
    unsigned char* cell;
    //cout<<(blockNum/8)<<". elem "<<(blockNum%8)<<". bitje\n";
    cell=&bitmap[blockNum/8];
    if(status) *cell |= 1<<(blockNum%8);
    else       *cell &= ~(1<<(blockNum%8));
    /*
    if(blockNum==11){
        cerr<<"breakpoint ide\n";
    }*/
}

bool getAllocationMapPosition(unsigned char *bitmap, unsigned long blockNum){
    unsigned char* cell;
    cell=&bitmap[blockNum/8];
    return *cell & (1<<(blockNum%8));
}
unsigned long lookForSpace(unsigned char *bitmap, unsigned long holeSize, unsigned long firstBlock, unsigned long lastBlock){
    unsigned long firstFit=-1;
    unsigned long bytesOk=0;
    for(unsigned long i=firstBlock;i<=lastBlock;i++){
        if(getAllocationMapPosition(bitmap, i)){
            firstFit=-1;
            bytesOk=0;
            continue;
        } else {
            if(firstFit==-1){
                firstFit=i;
                bytesOk=1;
            } else {
                bytesOk++;
            }
            if(bytesOk==holeSize) return firstFit;
        }
    }
    return (holeSize==bytesOk)?firstFit:-1;
}

unsigned long lookForMostExactSpace(unsigned char *bitmap, unsigned long holeSize, unsigned long firstBlock, unsigned long lastBlock){
    unsigned long bestFit=-1;
    unsigned long bytesOk=0;
    unsigned long minSize=lastBlock+firstBlock+1;
    bool prevType=true; //a megelozo blokk foglalt-e
    int currStart=-1;
    for(unsigned long i=firstBlock;i<=lastBlock;i++){
        //lefoglalhato terulet
        //cout<<i<<endl;
        if(!getAllocationMapPosition(bitmap, i)){
            cout<<"szabad: "<<i<<endl;
            if(prevType){
                currStart=i;  //ha az elozo blokk foglalt, akkor uj lehetseges kezdopont
            }
            bytesOk++;
            prevType=false;
        //lefoglalt terulet
        } else {
            cout<<"nem szabad: "<<i<<endl;
            if(!prevType){
                cout<<i<<" elozo terulet merete: "<<bytesOk<<" kezdete: "<<currStart<<endl;
                if(bytesOk>=holeSize){ //elozo terulet ervenyese
                    if(bytesOk<minSize){
                        cout<<"legjobb talalat: "<<currStart<<" / "<<minSize<<endl;
                        bestFit=currStart;
                        minSize=holeSize;
                    }
                }
            }
            bytesOk=0;
            prevType=true;
        }
    }
    //cout<<bestFit<<endl;
    return bestFit;
}


string sajat_basename(string path_){
    string path=cutFirstAndLastSlashes(path_);
    string fileName;
    string token;
    stringstream pathStream(path);
    while(getline(pathStream, token, '/'));
    fileName=token;
    return fileName;
}
string sajat_dirname(string path_){
    string path=cutFirstAndLastSlashes(path_);
    string dirName;
    string token;
    string prevToken;
    stringstream dirStream(path);
    while(getline(dirStream, token, '/')){
        dirName+=prevToken+"/";
        prevToken=token;
    }
    if(dirName=="") dirName="/";
    return dirName;
}/*
string cutFirstAndLastSlashes(string path){
    int first, size;
    first=0;
    size=path.length();
    if(path.length()==0) return "";
    if(path.at(0)=='/'){
        first=1;
        size--;
    }
    if(path.at(path.length()-1)=='/') size--;
    return path.substr(first, size);
}*/

string cutFirstAndLastSlashes(string path){
    int first=0, size=path.length();
    string lc=path;
    if(lc.length()==0) return 0;
    for(first=0;first<lc.length();first++){
        if(lc.at(first)=='/'){
            size--;
        } else
            break;
    }
    if(size==0) return "";
    lc=lc.substr(first, size);

    int last=lc.size()-1;
    for(;last!=0;last--){
        if(lc.at(last)!='/') break;

    }
    lc=lc.substr(0, last+1);

    return lc;
}

void printBitmap(unsigned char* bitmap, long size){
    for(unsigned long i=0;i<size;i++){
        cout<<(getAllocationMapPosition(bitmap, i)?"|":"_");
    }
    cout<<endl;
}

string parentFromPath(string path){
    if(path=="" || path=="/") return "/";
    string trimPath=cutFirstAndLastSlashes(path);
    string ret="/";
    stringstream ss(trimPath);
    string token;
    string prevToken="";
    while(getline(ss, token, '/')){
        if(prevToken!="") ret=ret+prevToken+"/";
        prevToken=token;
    }
    ret=cutFirstAndLastSlashes(ret);
    ret="/"+ret;
    cerr<<"[parent]"<<ret<<endl;
    return ret;
}
