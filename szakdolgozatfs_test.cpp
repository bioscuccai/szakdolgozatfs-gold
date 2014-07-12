#include <iostream>
#include <ctime>   //time()
#include <cstdlib> //rand()
#include <cstring> //memcmp()
#include <cassert>


#include "szakdolgozatfs_test.h"
#include "szakdolgozatfs.h"
#include "szakdolgozatfs_util.h"
#include "szakdolgozatfs_filehandle.h"
#include "szakdolgozatfs_directoryhandle.h"

using namespace std;

SzakdolgozatFs_Test::SzakdolgozatFs_Test(SzakdolgozatFs* fs_):fs(fs_){
    srand(time(0));
}
Test_File::Test_File(SzakdolgozatFs* fs):SzakdolgozatFs_Test(fs){}
Test_Directory::Test_Directory(SzakdolgozatFs* fs):SzakdolgozatFs_Test(fs){}

bool Test_File::testDelete(string loc){
    bool ok=true;
    SzakdolgozatFs_FileHandle* fileHandle=new SzakdolgozatFs_FileHandle(fs, loc);
    SzakdolgozatFs_DirectoryHandle* dirHandle=new SzakdolgozatFs_DirectoryHandle(fs, sajat_dirname(loc));
    dirHandle->open();
    fileHandle->touch();
    fileHandle->deleteFile();

    //uresen sikerul-e
    vector<string> dirCont=dirHandle->getFileNames();
    for(unsigned int i=0;i<dirCont.size();i++){
        if(dirCont.at(i)==sajat_basename(loc)){
            cerr<<"ures filet nem sikerult torolni\n";
            ok=false;
        }
    }

    //megnovelve
    delete fileHandle;
    fileHandle=new SzakdolgozatFs_FileHandle(fs, loc); //ujrakezdjuk
    fileHandle->touch();
    fs->increaseFileSize(fileHandle->getNodeBlock(), 1000);
    fileHandle->deleteFile();
    dirCont=dirHandle->getFileNames();
    for(unsigned int i=0;i<dirCont.size();i++){
        if(dirCont.at(i)==sajat_basename(loc)){
            cerr<<"nem ures filet nem sikerult torolni\n";
            ok=false;
        }
    }

    delete fileHandle;
    delete dirHandle;
    return ok;
}

bool Test_File::testFwrite_size(string loc, long fileSize){
    bool ok=true;
    //long fileSize=1024;
    //ebbol akarunk irni
    unsigned char* writeBuff=new unsigned char[fileSize];
    for(long i=0;i<fileSize;i++){
        if(i%3==0) writeBuff[i]='a';
        if(i%3==1) writeBuff[i]='b';
        if(i%3==2) writeBuff[i]='c';
    }
    SzakdolgozatFs_FileHandle* fileHandle=new SzakdolgozatFs_FileHandle(fs, loc);
    //try{
        fileHandle->open();
        fileHandle->touch();

    /*}catch(int e){
        cerr<<"test size: "<<strerror(0-e)<<endl;
        return false;
    }*/
    //fs->increaseFileSize(fileHandle->getNodeBlock(), fileSize);
    //cout<<"meret iras elott: "<<fileHandle->getSize()<<endl;

    //return false;
    for(long i=0;i<100;i++){
        long testSize=rand() % fileSize;
        long testEnd=fileSize - testSize;
        long testStart=rand()%testEnd;
        //cout<<"teszteset: "<<testStart<<" "<<testSize<<" "<<testStart+testSize<<endl;
        assert(testSize+testStart<=fileSize);
        unsigned char* testBuff=new unsigned char[testSize]; //ebbe olvasunk

        fileHandle->seekp(testStart);
        fileHandle->write(writeBuff, testSize);

        if(fileHandle->getSize()<(testSize+ testStart)){
            //cout<<"gaz van: meret: "<<fileHandle->getSize()<<" teszt: "<<testSize+testStart<<endl;
        }

        //cout<<"meret iras utan: "<<fileHandle->getSize()<<endl;


        fileHandle->seekg(testStart);
        fileHandle->read(testBuff, testSize);

        if(memcmp(testBuff, writeBuff, testSize)!=0){
            cerr<<"nem egyezik "<<testStart<<" / "<<testSize<<endl;
            ok=false;
        }
        delete testBuff;
    }
    delete writeBuff;
    return ok;
}

bool Test_File::testFread(string loc){
    long testSize;
    bool ok=true;
    //kisebb mint 1 blokk
    testSize=(rand()%(fs->blockSizeBytes-1)) +1;
    if(!this->testFread_size(loc, testSize)){
        ok=false;
        cerr<<"kis file meret nem stimmel("<<testSize<<")\n";
    }

    //pont 1 blokk
    testSize=fs->blockSizeBytes;
    if(!this->testFread_size(loc, testSize)){
        ok=false;
        cerr<<"1 blokk meret nem stimmel\n";
    }

    //tobb egesz blokk
    testSize=((rand()%30)+1)*(fs->blockSizeBytes);
    if(!this->testFread_size(loc, testSize)){
        ok=false;
        cerr<<"egesz blokk meretu nem stimmel("<<testSize<<")\n";
    }

    //nem egesz meretu blokk
    testSize=((rand()%30)+1)*(fs->blockSizeBytes);
    testSize+=(rand()%(fs->blockSizeBytes - 1))+1;
    if(!this->testFread_size(loc, testSize)){
        ok=false;
        cerr<<"nagy meretu nem stimmel nem stimmel("<<testSize<<")\n";
    }
    return ok;
}
//testFread()-rol masolva
bool Test_File::testFwrite(string loc){
    bool ok=true;
    try{
        assert(loc!="");
        long testSize;
        //kisebb mint 1 blokk
        testSize=(rand()%(fs->blockSizeBytes-1)) +1;
        if(!this->testFwrite_size(loc, testSize)){
            ok=false;
            cerr<<"kis file meret iras nem stimmel("<<testSize<<")\n";
        }

        //pont 1 blokk
        testSize=fs->blockSizeBytes;
        if(!this->testFwrite_size(loc, testSize)){
            ok=false;
            cerr<<"1 blokk meret iras nem stimmel\n";
        }

        //tobb egesz blokk
        testSize=((rand()%30)+1)*(fs->blockSizeBytes);
        if(!this->testFwrite_size(loc, testSize)){
            ok=false;
            cerr<<"egesz blokk meretu iras nem stimmel("<<testSize<<")\n";
        }

        //nem egesz meretu blokk
        testSize=((rand()%30)+1)*(fs->blockSizeBytes);
        testSize+=(rand()%(fs->blockSizeBytes - 1))+1;
        if(!this->testFwrite_size(loc, testSize)){
            ok=false;
            cerr<<"nagy meretu iras nem stimmel("<<testSize<<") "<<loc<<"\n";
        }
    }catch(int e){
        cerr<<strerror(0-e)<<endl;
        return false;
    }
    return ok;
}

bool Test_File::testFread_size(string loc, long fileSize){
    bool ok=true;
    SzakdolgozatFs_FileHandle *fileHandle=new SzakdolgozatFs_FileHandle(fs, loc);
    //SzakdolgozatFs_FileHandle *fileHandle;
    fileHandle->open();
    fileHandle->touch();

    unsigned char *buff=new unsigned char[fileSize];
    for(long i=0;i<fileSize;i++){
        /*if(i%3==0) buff[i]='a';
        if(i%3==1) buff[i]='b';
        if(i%3==2) buff[i]='c';*/
        buff[i]='a'+(i%('z'-'a'));
    }
    fileHandle->replaceContents(buff, fileSize);

    //cout<<"//////////////////////////////////////\n";
    //unsigned char* bt=new unsigned char[fileSize];
    //fs->getFileContentsFromInode(fileHandle->getNodeBlock(), bt);
    //charTombKiir(bt, fileSize);

    //fileHandle->seekg(0);
    //fileHandle->read(bt, 1023);
    //fs->doFread(fileHandle->getNodeBlock(), 0,1023,buff);
    //charTombKiir(bt, 1023);

    //return true;
    //veletlen helyen mukodik-e
    for(int i=0;i<100;i++){
        //long testSize=rand() % fileSize;
        long testSize=10;
        long testEnd=fileSize - testSize;
        long testStart=rand()%testEnd;
        assert(testStart+testSize<=fileSize);
        unsigned char* testBuff=new unsigned char[testSize];
       // cout<<testStart<<": ";
        fileHandle->seekg(testStart);
        fileHandle->read(testBuff, testSize);
        //charTombKiir(testBuff, testSize);
        //cout<<endl;

        if(memcmp(&buff[testStart], testBuff, testSize)!=0){
            cout<<"nem egyezik "<<testStart<<" / "<<testSize<<endl;
            charTombKiir(&buff[testStart], testSize);
            cout<<endl;
            charTombKiir(testBuff, testSize);
            cout<<endl;
            ok=false;
        }

        delete testBuff;
    }

    //delete bt;
    delete fileHandle;
    return ok;
}

bool Test_File::testEmptyFileCreation(string loc){
    bool ok=true;
    SzakdolgozatFs_FileHandle *fileHandle=new SzakdolgozatFs_FileHandle(fs, loc);
    fileHandle->touch();

    unsigned long fileBlock=fs->resolveNodeOfFile(loc);
    if(fileBlock==-1){
        cout<<"blokk nincs lefoglalva\n";
        ok=false;
    }

    SzakdolgozatFs_Inode* fileNode=new SzakdolgozatFs_Inode();
    fs->getInodeFromBlock(fileBlock, fileNode);
    if(fileNode->type!=PFS_FILE){
        cout<<"nem file tipusu\n";
        ok=false;

    }
    if(fileNode->size!=0){
        cout<<"nem 0 meretu\n";
        ok=false;
    }


    delete fileNode;
    delete fileHandle;
    return ok;
}


bool Test_File::testIncreaseFile(string loc){
    bool ok=true;
    //unsigned long fileBlock=fs->createFileWithContents(loc, NULL, 0);
    //SzakdolgozatFs_Inode *fileNode=new SzakdolgozatFs_Inode();
    SzakdolgozatFs_FileHandle *fh=new SzakdolgozatFs_FileHandle(fs, loc);
    fh->open();
    fh->touch();
    //kerek blokk meret
    for(unsigned int i=1;i<200;i++){
        unsigned long fileSize=(fs->blockSizeBytes)*i;
        fs->increaseFileSize(fh->nodeBlock, fileSize);
        //fs->getInodeFromBlock(fh->nodeBlock, fileNode);
        vector<unsigned long>blocks=fs->getBlockListFromInodeBlock(fh->nodeBlock);

        //inode meret stimmel
        if(fh->getSize()!=fileSize){
            cout<<"inodeban feltuntetett meret nem stimmel\n";
            ok=false;
        }

        //blokk lista merete
        if(blocks.size() != fs->blocksNeededPerSize(fileSize)){
            cout<<"blokk lista merete nem stimmel\n";
            ok=false;
        }
    }

    //nem kerek blokk meret
    fh->touch();
    for(unsigned int i=1;i<200;i++){
        unsigned long minusSize=(rand()%(fs->blockSizeBytes-3));
        //fs->getInodeFromBlock(fileBlock, fileNode);
        long fileSize=((fs->blockSizeBytes)*i) -minusSize;
        //cerr<<"curr size: "<<fileNode->size<<" new size: "<<fileSize<<endl;
        fs->increaseFileSize(fh->nodeBlock, fileSize);
        //fs->getInodeFromBlock(fh->nodeBlock, fileNode);
        vector<unsigned long>blocks=fs->getBlockListFromInodeBlock(fh->nodeBlock);
        //inode meret stimmel
        if(fh->getSize()!=fileSize){
            cout<<"rand inodeban feltuntetett meret nem stimmel\n";
            ok=false;
        }
        //blokk lista merete
        if(blocks.size() != fs->blocksNeededPerSize(fileSize)){
            cout<<"rand blokk lista merete nem stimmel\n";
            ok=false;
        }
    }
    //delete fileNode;
    delete fh;
    return ok;
}

bool Test_File::testDecreaseFile(string loc){
    bool ok=true;
    unsigned long initFileSize=(rand()%1000000)+100000;
    SzakdolgozatFs_FileHandle *fh=new SzakdolgozatFs_FileHandle(fs, loc);
   // SzakdolgozatFs_Inode *fileNode=new SzakdolgozatFs_Inode();

    fh->open();
    fh->touch();
    fs->increaseFileSize(fh->nodeBlock, initFileSize);
/*
    //veleten meret
    for(int i=1;i<200;i++){
        unsigned long minusSize=(rand()%(fs->blockSizeBytes-3));
        unsigned long newSize=fh->getSize()-minusSize;
        if(newSize < 0) break;
        fs->decreaseFileSize(fh->nodeBlock, newSize);
        vector<unsigned long>blocks=fs->getBlockListFromInodeBlock(fh->nodeBlock);
        //inode meret stimmel
        if(fh->getSize()!=newSize){
            cout<<"rand inodeban feltuntetett meret nem stimmel\n";
            ok=false;
        }
        //blokk lista merete
        if(blocks.size() != fs->blocksNeededPerSize(newSize)){
            cout<<"rand blokk lista merete nem stimmel\n";
            ok=false;
        }
    }*/

    fh->touch();
    fs->increaseFileSize(fh->nodeBlock, initFileSize);
    //fix blokkmeret
    for(int i=1;i<200;i++){
        unsigned long newSize=fh->getSize()-(i*fs->blockSizeBytes);
        if(newSize>fh->getSize()) break; //unsigned tulcsordulas miatt
        cerr<<"old size: "<<fh->getSize()<<" new size: "<<newSize<<endl;
        if(newSize<0) break;

        fs->decreaseFileSize(fh->nodeBlock,newSize);

        vector<unsigned long>blocks=fs->getBlockListFromInodeBlock(fh->nodeBlock);
        //inode meret stimmel
        if(fh->getSize()!=newSize){
            cout<<"rand inodeban feltuntetett meret nem stimmel\n";
            ok=false;
        }
        //blokk lista merete
        if(blocks.size() != fs->blocksNeededPerSize(newSize)){
            cout<<"rand blokk lista merete nem stimmel\n";
            ok=false;
        }
    }
    delete fh;
    //delete fileNode;
    return ok;
}

bool Test_Directory::testDirectoryCreation(string loc){
    bool ok=true;
    long dirBlock=fs->createDirectory(loc);
    if(dirBlock==-1){
        cout<<"nem lett blokk lefoglalva\n";
        ok=false;
    }
    SzakdolgozatFs_Inode *dirNode=new SzakdolgozatFs_Inode();
    fs->getInodeFromBlock(dirBlock, dirNode);

    //konyvtar-e
    if(dirNode->type!=PFS_DIR){
        cout<<"nem konyvtar tipusu az inode\n";
        ok=false;
    }

    //ures-e
    SzakdolgozatFs_DirectoryHandle *dirHandle=new SzakdolgozatFs_DirectoryHandle(fs, loc);
    dirHandle->open();
    vector<string> dirContents=dirHandle->getFileNames();
    if(dirContents.size()!=0){
        cout<<"nem ures\n";
        ok=false;
    }



    delete dirHandle;
    delete dirNode;

    return ok;
}

bool Test_Directory::testDirectoryNewFile(string loc){
    bool ok=true;
    SzakdolgozatFs_DirectoryHandle *d=new SzakdolgozatFs_DirectoryHandle(fs, loc);
    d->create();
    d->open();
    vector<string> c=d->getFileNames();

    SzakdolgozatFs_FileHandle *f=new SzakdolgozatFs_FileHandle(fs, loc+"a");
    f->touch();
    for(int i=0;i<100;i++){
        char *szNum=new char[10];
        sprintf(szNum, "%d", i);
        string *fName=new string(szNum);
        string fPath;
        fPath=loc+*fName;
        cout<<"testing path: "<<fPath<<endl;

        SzakdolgozatFs_FileHandle* fh=new SzakdolgozatFs_FileHandle(fs, fPath);
        fh->touch();

        vector<string> fn=d->getFileNames();
        bool fileValid=false;
        for(unsigned int j=0;j<fn.size();j++){
            if(fn.at(j) == (*fName)) fileValid=true;

            //cout<<fn.at(j)<<" ";
        }

        if(!fileValid){
            cout<<"!!!!!!!!!!!!!!!!"<<*fName<<" nem letezik\n";
            return false;
            ok=false;
        }
        //cout<<endl;

        delete fName;
        delete szNum;
    }
    cerr<<"ok-e "<<(ok?1:0)<<endl;
    return ok;
}
