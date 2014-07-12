#include <cassert>
#include <iostream>
#include <algorithm>

#include "szakdolgozatfs_directoryhandle.h"
#include "szakdolgozatfs_util.h"

using namespace std;

vector<string> SzakdolgozatFs_DirectoryHandle::getFileNames(){
    SzakdolgozatFs_Directory* dir=new SzakdolgozatFs_Directory();
    fs->readDirectoryFromInodeBlock(nodeBlock, dir);
    vector<string> dirs;
    vector<string> files;
    for(unsigned int i=0;i<dir->blocks.size();i++){
        SzakdolgozatFs_Inode* node=new SzakdolgozatFs_Inode();
        fs->getInodeFromBlock(dir->blocks.at(i), node);
        if(node->type==PFS_DIR) dirs.push_back(node->name);
            else files.push_back(node->name);
        //names.push_back(node->name);
        //cerr<<"[getFileNames]"<<(node->name)<<"  "<<(dir->firstNodeBlocks.at(i))<<endl;
        //cout<<dir->firstNodeBlocks.at(i)<<"["<<i<<"]("<<node->name<<")";
        //names.push_back("aaa");
        delete node;
    }
    std::sort(dirs.begin(), dirs.end());
    std::sort(files.begin(), files.end());
    //cout<<endl;
    dirs.insert(dirs.end(), files.begin(), files.end());
    return dirs;
}

void SzakdolgozatFs_DirectoryHandle::create(){
    assert(nodeBlock==-1);
    nodeBlock=fs->createDirectory(path);
    //cout<<"uj konyvtar node-ja: "<<nodeBlock<<endl;

    SzakdolgozatFs_Inode* n=new SzakdolgozatFs_Inode();
    fs->getInodeFromBlock(nodeBlock, n);
    //cout<<"path: "<<path<<endl;
    //cout<<"kv neve: "<<n->name<<endl;
}

void SzakdolgozatFs_DirectoryHandle::open(){
    //cerr<<"[dirhandle open] "<<path<<endl;
    nodeBlock=fs->resolveNodeOfFile(path);
    assert(nodeBlock!=-1);
    SzakdolgozatFs_Inode* node=new SzakdolgozatFs_Inode();
    fs->getInodeFromBlock(nodeBlock,node);
    isOpen=true;
    cerr<<"[utvonal]"<<path<<"   "<<nodeBlock<<"   "<<node->type<<endl;
    assert(node->type==PFS_DIR);

    delete node;
}

SzakdolgozatFs_DirectoryHandle::SzakdolgozatFs_DirectoryHandle(SzakdolgozatFs* fs_, string path_):nodeBlock(-1),isOpen(false),fs(fs_),path(path_){
}
