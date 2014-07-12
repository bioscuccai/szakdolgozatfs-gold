#include "szakdolgozatfs_lrucache.h"
#include "szakdolgozatfs_inode.h"

#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;


Cache::Cache(int me){
    maxEntries=me;
    sorrend=new int[maxEntries];
    darab=0;
    for(int i=0;i<maxEntries;i++){
        sorrend[i]=-1;
    }
    cerr<<"Konstruktor me: "<<me<<endl;
}

Cache::~Cache(){
    delete sorrend;
}

BlockCache::BlockCache(int me, int bs):Cache(me),blockSize(bs) {}

int Cache::keyIndex(int k){
    for(int i=0;i<maxEntries;i++){
        if(sorrend[i]==k) return i;
    }
    return -1;
}
bool Cache::containsKey(int k){
    return keyIndex(k)!=-1;
}

void Cache::eloreHoz(int ind){
    int *masolat=new int[maxEntries];
    int aktIndex;

    //alapertelemezett tartalom
    for(int i=0;i<maxEntries;i++) masolat[i]=-1;

    //a megelozo reszig kimasoljuk
    for(aktIndex=0;aktIndex<ind;aktIndex++){
        masolat[aktIndex]=sorrend[aktIndex];
    }

    for(int i=ind+1;i<darab;i++,aktIndex++){
        masolat[aktIndex]=sorrend[i];
    }

    masolat[darab-1]=sorrend[ind];
    for(int i=0;i<maxEntries;i++) sorrend[i]=masolat[i];
    delete masolat;
}

void BlockCache::getBejegyzes(int k, unsigned char* ptr){
    memcpy(ptr, buff[k], blockSize);
}

void BlockCache::setBejegyzes(int k, unsigned char* ptr){
    int ind=keyIndex(k);


    //ha még elfér és nem tartalmazza (hely lefoglalása)
    if(darab!=maxEntries && ind==-1){
        unsigned char *block=new unsigned char[blockSize];
        memcpy(block, ptr, blockSize);
        sorrend[darab]=k;
        darab++;
        buff[k]=block;
        //cerr<<k<<" elfer, nem tartalmazza\n";
        return;
    }


    //ha elférne, de már tartalmazza (felülír)
    if(darab!=maxEntries && ind!=-1){
        memcpy(buff[k], ptr, blockSize);
        eloreHoz(ind);
        //cerr<<k<<" elfer, de tartalmazza\n";
        return;
    }

    //ha nem fér el, de tartalmazza (felülír)
    if(ind!=-1){
        eloreHoz(ind);
        memcpy(buff[k], ptr, blockSize);
        //cerr<<k<<" mar tartalmazza\n";
        return;
    }

    //nem fér el, nem tartalmazza
    //->kivesszük az utolsót
    //(utolsót töröljük, újat lefoglaljuk
    {
        unsigned char *block=new unsigned char[blockSize];
        memcpy(block, ptr, blockSize);
        //cerr<<k<<" nem fer el, nem tartalmazza\n";
        int kivenni=sorrend[0];
        if(buff.count(kivenni)!=0){
            delete buff[kivenni];
            buff.erase(kivenni);
        }
        buff[k]=block;
        sorrend[0]=k;
        eloreHoz(0);
        return;
    }
    return;
}


///////////////////////////////////////////
///////////////////////////////////////////
///////////////////////////////////////////


InodeCache::InodeCache(int me):Cache(me){}

void InodeCache::getBejegyzes(int k, SzakdolgozatFs_Inode* ptr){
    memcpy(ptr, buff[k], sizeof(SzakdolgozatFs_Inode));
}

void InodeCache::setBejegyzes(int k, SzakdolgozatFs_Inode* ptr){
    int ind=keyIndex(k);

    //ha még elfér és nem tartalmazza (hely lefoglalása)
    if(darab!=maxEntries && ind==-1){
        SzakdolgozatFs_Inode* node=new SzakdolgozatFs_Inode();
        memcpy(node, ptr, sizeof(SzakdolgozatFs_Inode));
        sorrend[darab]=k;
        darab++;
        buff[k]=node;
        //cerr<<k<<" elfer, nem tartalmazza\n";
        return;
    }



    //ha elférne, de már tartalmazza (felülír)
    if(darab!=maxEntries && ind!=-1){
        memcpy(buff[k], ptr, sizeof(SzakdolgozatFs_Inode));
        eloreHoz(ind);
        //cerr<<k<<" elfer, de tartalmazza\n";
        return;
    }

    //ha nem fér el, de tartalmazza (felülír)
    if(darab==maxEntries && ind!=-1){
        eloreHoz(ind);
        memcpy(buff[k], ptr, sizeof(SzakdolgozatFs_Inode));
        //cerr<<k<<" mar tartalmazza\n";
        return;
    }

    //nem fér el, nem tartalmazza
    //->kivesszük az utolsót
    //(utolsót töröljük, újat lefoglaljuk
    if(darab==maxEntries && ind==-1){
        SzakdolgozatFs_Inode* node=new SzakdolgozatFs_Inode();
        memcpy(node, ptr, sizeof(SzakdolgozatFs_Inode));
        //cerr<<k<<" nem fer el, nem tartalmazza\n";
        int kivenni=sorrend[0];
/*
            for(int i=0;i<maxEntries;i++){
                cerr<<sorrend[i]<<"/";
            }
            cerr<<endl;
*/
        if(buff.count(kivenni)!=0){
            delete buff[kivenni];
            buff.erase(kivenni);
        } else {
            //cerr<<kivenni<<" nincs az inode cache-ben\n";

        }
        //cerr<<"[bejegyzes node] "<<node->name<<endl;
        buff[k]=node;
        sorrend[0]=k;
        eloreHoz(0);
        return;
    }
    return;
}
