#include "allocwidget.h"
#include "szakdolgozatfs.h"
#include "szakdolgozatfs_inode.h"
#include "szakdolgozatfs_filehandle.h"
#include "szakdolgozatfs_directoryhandle.h"

#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

WidgetSquare::WidgetSquare(WidgetSquareType t, unsigned long f, bool u):type(t),file(f), used(u){
}

AllocWidget::AllocWidget(QWidget *parent):QWidget(parent){
    prevInodeCache=FajlrendszerSingleton::getInstance()->bInodeCacheEnabled;
    prevBlockCache=FajlrendszerSingleton::getInstance()->bBlockCacheEnabled;

    FajlrendszerSingleton::getInstance()->bInodeCacheEnabled=false;
    FajlrendszerSingleton::getInstance()->bBlockCacheEnabled=false;

    fillMap();

    FajlrendszerSingleton::getInstance()->bInodeCacheEnabled=prevInodeCache;
    FajlrendszerSingleton::getInstance()->bBlockCacheEnabled=prevBlockCache;
}

QColor AllocWidget::blockColor(WidgetSquareType t){
    switch(t){
        case WST_UK: return Qt::red;
        case WST_SUPER: return Qt::yellow;
        case WST_ALLOC: return Qt::darkYellow;
        case WST_INODE: return Qt::cyan;
        case WST_BL: return Qt::darkBlue;
        case WST_DATA: return Qt::blue;
        default: return Qt::green;
    }
    return Qt::green;
}
void AllocWidget::paintEvent(QPaintEvent *e){
    QPainter painter(this);
    int w=1000;
    int meret=10;
    int sor=0, oszlop=0;
    setFixedWidth(w);
    setFixedHeight(meret * (((nBlocks*meret)/w) +1));

    for(unsigned int i=0;i<nBlocks;i++){
        sor=(i*meret)/w;
        oszlop=((i*meret) - (sor*w))/meret;
        if(squareMap.count(i)!=0){
            //painter.fillRect(oszlop*meret,sor*meret,meret-2, meret-2,(squareMap[i]->used?Qt::red:Qt::blue));
            if(highlightFile==squareMap[i]->file){
                painter.fillRect(oszlop*meret,sor*meret,meret, meret,Qt::green);
                //cerr<<"[alloc] highlight: "<<i<<endl;
            }
            painter.fillRect(oszlop*meret+2,sor*meret+2,meret-4, meret-4,(squareMap[i]->used?blockColor(squareMap[i]->type):Qt::lightGray));

            //ha benne van a cacheben

            if(std::find(cacheMark.begin(), cacheMark.end(), i)!=cacheMark.end())
                painter.drawLine(oszlop*meret, sor*meret, oszlop*meret+meret, sor*meret+meret);
            if(std::find(inodeCacheMark.begin(), inodeCacheMark.end(), i)!=inodeCacheMark.end())
                painter.drawEllipse(oszlop*meret, sor*meret, meret, meret);

        } else {
            cerr<<i<<" nincs\n";
            painter.fillRect(oszlop*18,sor*18,15,15,Qt::green);
        }
    }
}

void AllocWidget::checkFile(string p){
    SzakdolgozatFs_FileHandle *fh=new SzakdolgozatFs_FileHandle(FajlrendszerSingleton::getInstance(), p);
    fh->open();
    unsigned long nodeBlock=fh->nodeBlock;
    SzakdolgozatFs_Inode *inode=new SzakdolgozatFs_Inode();

    FajlrendszerSingleton::getInstance()->getInodeFromBlock(nodeBlock, inode);
    vector<unsigned long> bl=FajlrendszerSingleton::getInstance()->getBlockListFromInodeBlock(nodeBlock);

    //cerr<<"[alloc] "+p+" blokklista: "<<inode->blockListLocation<<endl;

    //inode
    long inodeBlockSizeInBlocks=FajlrendszerSingleton::getInstance()->blocksNeededPerSize(sizeof(SzakdolgozatFs_Inode));
    for(int i=0;i<inodeBlockSizeInBlocks;i++){
        if(squareMap.count(nodeBlock+i)==1){
            squareMap[nodeBlock+i]->type=WST_INODE;
            squareMap[nodeBlock+i]->file=nodeBlock;
            //cerr<<"[alloc] "+p+" inode: "<<nodeBlock+i<<endl;
        } else {
            cerr<<"[alloc widget] inode block "<<(nodeBlock+i)<<" nincs megjelolve\n";
        }
    }


    //lefoglalt blokkok
    for(int i=0;i<bl.size();i++){
        if(squareMap.count(bl.at(i))==1){
            squareMap[bl.at(i)]->type=WST_DATA;
            squareMap[bl.at(i)]->file=nodeBlock;
            //cerr<<"[alloc] "+p+" blokk: "<<bl.at(i)<<endl;
        }
    }

    //blokk lista
    long blocksForBlockList=FajlrendszerSingleton::getInstance()->blocksNeededPerSize(bl.size()*sizeof(unsigned long));
    for(int i=0;i<blocksForBlockList;i++){
        if(squareMap.count(inode->blockListLocation+i)==1){
            squareMap[inode->blockListLocation+i]->type=WST_BL;
            squareMap[inode->blockListLocation+i]->file=nodeBlock;
        }
    }
    delete fh;
}

void AllocWidget::fillMap(){

    nBlocks=FajlrendszerSingleton::getInstance()->numberOfBlocks;
    //a diagram letrehozasakor mi volt a cahceben
    for(unsigned int i=0;i<FajlrendszerSingleton::getInstance()->blockCache->maxEntries;i++){
        if(FajlrendszerSingleton::getInstance()->blockCache->sorrend[i]!=-1)
            cacheMark.push_back(FajlrendszerSingleton::getInstance()->blockCache->sorrend[i]);
    }

    //inode cache
    for(unsigned int i=0;i<FajlrendszerSingleton::getInstance()->inodeCache->maxEntries;i++){
        if(FajlrendszerSingleton::getInstance()->inodeCache->sorrend[i]!=-1)
            inodeCacheMark.push_back(FajlrendszerSingleton::getInstance()->inodeCache->sorrend[i]);
    }

    //helyfoglalas
    for(unsigned long i=0;i<FajlrendszerSingleton::getInstance()->numberOfBlocks;i++){
        squareMap[i]=new WidgetSquare(WST_UK, -1, getAllocationMapPosition(FajlrendszerSingleton::getInstance()->bitmap,i));
        /*
        if(i%100==0) cerr<<endl;
        cerr<<getAllocationMapPosition(FajlrendszerSingleton::getInstance()->bitmap,i);*/
        //cerr<<getAllocationMapPosition(FajlrendszerSingleton::getInstance()->bitmap,i);
        //new WidgetSquare(WST_SUPER, "", getAllocationMapPosition(FajlrendszerSingleton::getInstance()->bitmap,i));
    }

    //superblock
    long superBlockSizeBlocks=FajlrendszerSingleton::getInstance()->blocksNeededPerSize(sizeof(SzakdolgozatFs_Inode));
    for(unsigned long int i=0;i<superBlockSizeBlocks;i++){
        squareMap[i]->type=WST_SUPER;
    }

    //alloc tabla
    for(unsigned long int i=superBlockSizeBlocks;i<FajlrendszerSingleton::getInstance()->bitmapSizeBlocks+1;i++){
        squareMap[i]->type=WST_ALLOC;
    }

    //fajlrendszer bejarasa

    stack<string> hatraLevo;
    hatraLevo.push("/");
    checkFile("/");
    while(!hatraLevo.empty()){
        string akt=hatraLevo.top();
        cerr<<"[bejar]: "<<akt;
        hatraLevo.pop();
        SzakdolgozatFs_DirectoryHandle *dh=new SzakdolgozatFs_DirectoryHandle(FajlrendszerSingleton::getInstance(), akt);
        dh->open();
        vector<string> fl=dh->getFileNames();

        for(int i=0;i<fl.size();i++){
           string filePath=cutFirstAndLastSlashes(akt+"/"+fl.at(i));
           SzakdolgozatFs_FileHandle *fh=new SzakdolgozatFs_FileHandle(FajlrendszerSingleton::getInstance(), filePath);
           fh->open();
           if(fh->nodeBlock==-1){
               cerr<<"[alloc widget]"<<filePath<<" nem okes\n";
               continue;
           }
           if(fh->getType()==PFS_DIR) hatraLevo.push(filePath);

           checkFile(filePath);

           delete fh;
        }

        delete dh;
    }

}
