#include "cachedialog.h"
#include "ui_cachedialog.h"

#include "szakdolgozatfs_filehandle.h"
#include "szakdolgozatfs_directoryhandle.h"
#include "fajlrendszersingleton.h"

#include <map>
#include <stack>
#include <vector>
#include <iostream>
#include <string>

#include <QStringListModel>

using namespace std;

CacheDialog::CacheDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::CacheDialog)
{
    m_ui->setupUi(this);


    blockCacheSize=FajlrendszerSingleton::getInstance()->blockCache->maxEntries;
    inodeCacheSize=FajlrendszerSingleton::getInstance()->inodeCache->maxEntries;

    blockCacheCopy=new unsigned int[blockCacheSize];
    inodeCacheCopy=new unsigned int[inodeCacheSize];

    for(int i=0;i<blockCacheSize;i++) blockCacheCopy[i]=FajlrendszerSingleton::getInstance()->blockCache->sorrend[i];
    for(int i=0;i<inodeCacheSize;i++) inodeCacheCopy[i]=FajlrendszerSingleton::getInstance()->inodeCache->sorrend[i];

    prevInodeCache=FajlrendszerSingleton::getInstance()->bInodeCacheEnabled;
    prevBlockCache=FajlrendszerSingleton::getInstance()->bBlockCacheEnabled;

    FajlrendszerSingleton::getInstance()->bInodeCacheEnabled=false;
    FajlrendszerSingleton::getInstance()->bBlockCacheEnabled=false;

    fillNodeOwners();

    createInodeModel();
    QStringListModel *inodeModel=new QStringListModel();
    inodeModel->setStringList(inodeList);
    cerr<<"inodelist elemszam: "<<inodeList.length()<<endl;
    m_ui->inodeListWidget->setModel(inodeModel);

    createBlockModel();
    QStringListModel *blockModel=new QStringListModel();
    blockModel->setStringList(blockList);
    m_ui->blockListWidget->setModel(blockModel);

    FajlrendszerSingleton::getInstance()->bInodeCacheEnabled=prevInodeCache;
    FajlrendszerSingleton::getInstance()->bBlockCacheEnabled=prevBlockCache;
}

CacheDialog::~CacheDialog()
{
    delete m_ui;
}

void CacheDialog::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }

}

void CacheDialog::checkFile(string p){
    SzakdolgozatFs_FileHandle *fh=new SzakdolgozatFs_FileHandle(FajlrendszerSingleton::getInstance(), p);
    fh->open();
    unsigned long nodeBlock=fh->nodeBlock;
    SzakdolgozatFs_Inode *inode=new SzakdolgozatFs_Inode();
    FajlrendszerSingleton::getInstance()->getInodeFromBlock(nodeBlock, inode);

    vector<unsigned long> bl=FajlrendszerSingleton::getInstance()->getBlockListFromInodeBlock(nodeBlock);

    //inode
    long inodeBlockSizeInBlocks=FajlrendszerSingleton::getInstance()->blocksNeededPerSize(sizeof(SzakdolgozatFs_Inode));
    for(int i=0;i<inodeBlockSizeInBlocks;i++){
        nodeOwner[nodeBlock+i]=p;
    }


    //lefoglalt blokkok
    for(int i=0;i<bl.size();i++){
        nodeOwner[bl.at(i)]=p;
    }

    //blokk lista
    long blocksForBlockList=FajlrendszerSingleton::getInstance()->blocksNeededPerSize(bl.size()*sizeof(unsigned long));
    for(int i=0;i<blocksForBlockList;i++){
        nodeOwner[inode->blockListLocation+i]=p;
    }
    delete fh;
}

void CacheDialog::fillNodeOwners(){
    unsigned int nBlocks=FajlrendszerSingleton::getInstance()->numberOfBlocks;

    //helyfoglalas
    for(unsigned long i=0;i<FajlrendszerSingleton::getInstance()->numberOfBlocks;i++){
        nodeOwner[i]="<helyfoglalas>";
    }

    //superblock
    long superBlockSizeBlocks=FajlrendszerSingleton::getInstance()->blocksNeededPerSize(sizeof(SzakdolgozatFs_Inode));
    for(unsigned long int i=0;i<superBlockSizeBlocks;i++){
        nodeOwner[i]="<szuperblokk>";
    }

    //alloc tabla
    for(unsigned long int i=superBlockSizeBlocks;i<FajlrendszerSingleton::getInstance()->bitmapSizeBlocks;i++){
        nodeOwner[i]="<helyfoglalas>";
    }

    //fajlrendszer bejarasa

    stack<string> hatraLevo;
    hatraLevo.push("/");
    checkFile("/");
    while(!hatraLevo.empty()){
        string akt=hatraLevo.top();
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


void CacheDialog::createInodeModel(){
    for(int i=0;i<inodeCacheSize;i++){
        if(inodeCacheCopy[i]!=-1){
            if(nodeOwner.count(i)!=0){
                inodeList.append(QString::fromStdString(nodeOwner[inodeCacheCopy[i]])+" | "+QString::number(FajlrendszerSingleton::getInstance()->inodeCache->sorrend[i]));
            } else {
                inodeList<<("<ervenytelen> | "+QString::number(i));
            }
        }
    }
}


void CacheDialog::createBlockModel(){
    cerr<<"[createBlockModel]\n";
    vector<string> filesInCache;
    std::map<string, string> listTemp;
    for(int i=0;i<blockCacheSize;i++){
        if(blockCacheCopy[i]!=-1){
            unsigned int aktBlokk=blockCacheCopy[i];
            string aktTulaj=nodeOwner[aktBlokk];
            /*
            if(listTemp.count(aktTulaj)==1){
                QString sb=QString::fromStdString(listTemp[aktTulaj]);
                sb+=" ";
                sb+=QString::number(aktBlokk);
                listTemp[aktTulaj]=sb.toStdString();
            } else {
                listTemp[aktTulaj]=aktBlokk+" ";
                filesInCache.push_back(aktTulaj);
                cerr<<"[new file:]"<<aktTulaj<<endl;
            }*/

            if(listTemp.count(aktTulaj)==0){
                filesInCache.push_back(aktTulaj);
                listTemp[aktTulaj]="";
            }
            listTemp[aktTulaj]=listTemp[aktTulaj]+" "+QString::number(aktBlokk).toStdString();

        }
    }

    foreach(string fn, filesInCache){
        cerr<<"fic: "<<fn<<endl;
        blockList<<(QString::fromStdString(fn)+" | "+QString::fromStdString(listTemp[fn]));
    }
}
