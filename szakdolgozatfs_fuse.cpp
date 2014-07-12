#define FUSE_USE_VERSION  26

#include <iostream>
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/statvfs.h>
#include <time.h>
#include <unistd.h>

#include <vector>
#include <fstream>
#include <QMutexLocker>
#include <QMutex>
#include <iostream>
#include <cstring>
#include <cstdlib>

#include "szakdolgozatfs.h"
#include "szakdolgozatfs_filehandle.h"
#include "szakdolgozatfs_directoryhandle.h"

using namespace std;

static SzakdolgozatFs *fs=new SzakdolgozatFs();


char *tart="proba tartalom";

QMutex mutex;

namespace SzakdolgozatFs_FuseWrapper{

  static int szfs_statfs(const char *path, struct statvfs *svfs){
QMutexLocker locker(&mutex);
    unsigned long f=0, u=0;
    fs->getFreeAndUsedBlocks(&f, &u);
    svfs->f_bsize=fs->blockSizeBytes;
    svfs->f_frsize=fs->blockSizeBytes;
    
    svfs->f_blocks=fs->numberOfBlocks;
    svfs->f_bfree=f;
    svfs->f_bavail=f;
    
    svfs->f_namemax=256;
    return 0;
  }
  
  static int szfs_chmod(const char *path, mode_t m){
    QMutexLocker locker(&mutex);
    try{
      if(fs->resolveNodeOfFile(path)==-1) return -ENOENT;
      fs->chmod(path, m);
    } catch(int e){
      return e;
    }
    return 0;
  }
  static int szfs_chown(const char *path, uid_t uid, gid_t gid){
    QMutexLocker locker(&mutex);
    try{
      if(fs->resolveNodeOfFile(path)==-1) return -ENOENT;
      fs->chown(path, uid, gid);
    } catch(int e){
      return e;
    }
    return 0;
  }
  
  static int szfs_utimens(const char *path, const struct timespec t[2]){
    QMutexLocker locker(&mutex);
    try{
      if(fs->resolveNodeOfFile(path)==-1) return -ENOENT;
      fs->setMTime(path, t[0].tv_sec);
      fs->setATime(path, t[1].tv_sec);
    } catch(int e){
      return e;
    }
    return 0;
  }
  
  static int szfs_getattr(const char *path, struct stat *stbuf){
      QMutexLocker locker(&mutex);
      int res = -ENOENT;
      memset(stbuf, 0, sizeof(struct stat));
      SzakdolgozatFs_Inode* node=new SzakdolgozatFs_Inode();
      //naploz("eddig minden ok <"+string(path)+">");
      long nodeBlock=fs->resolveNodeOfFile(string(path));
      //naploz("node lefutott");
      if(nodeBlock==-1) goto vege;
      if(nodeBlock==0){
//	naploz("0 eredmeny");
	goto vege;
      }
      fs->getInodeFromBlock(nodeBlock, node);
      stbuf->st_atime=node->lastModification;
      stbuf->st_mtime=node->lastModification;
      stbuf->st_ctime=node->lastModification;
      if(node->type==PFS_DIR){
	  //naploz("konyvtar");
	  int hardLink=2;
	  //hardlinkek szama -> benne levo konyvtarak
	  SzakdolgozatFs_DirectoryHandle *dir=new SzakdolgozatFs_DirectoryHandle(fs, string(path));
	  dir->open();
	  vector<string> dc=dir->getFileNames();
	  string pathAsString=string(path);
	  if(pathAsString.at(pathAsString.size()-1)!='/') pathAsString+="/";
	  for(int i=0;i<dc.size();i++){
	    SzakdolgozatFs_FileHandle *fh=new SzakdolgozatFs_FileHandle(fs, pathAsString+dc.at(i));
	    fh->open();
	    if(fh->getType()==PFS_DIR) hardLink++;
	    delete fh;
	  }
	  
	  delete dir;
	  
	  stbuf->st_mode = S_IFDIR | 0755;
	  //stbuf->st_mode = S_IFDIR | node->mode;
          stbuf->st_nlink = hardLink;
	  res=0;
	  
	  
      }else if(node->type==PFS_FILE){
	 // naploz("fajl");
	  //stbuf->st_mode = S_IFREG | 0444;
	  stbuf->st_mode = S_IFREG | node->mode;
          stbuf->st_nlink = 1;
	  stbuf->st_size=node->size;
	  res=0;
      }
      stbuf->st_uid=node->uid;
      stbuf->st_gid=node->gid;
      vege:
      delete node;
      return res;
  }
  static int szfs_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi){
      QMutexLocker locker(&mutex);
      try{
	(void) offset;
	(void) fi;
	if(fs->resolveNodeOfFile(path)==-1) return -ENOENT;
	filler(buf, ".", NULL, 0);
	filler(buf, "..", NULL, 0);
	
	SzakdolgozatFs_DirectoryHandle *dir=new SzakdolgozatFs_DirectoryHandle(fs, string(path));
	dir->open();
	vector<string> dc=dir->getFileNames();
	
	
	for(int i=0;i<dc.size();i++){
	  filler(buf, dc.at(i).c_str(), NULL, 0);
	}
	delete dir;
      } catch(int e){
      return e;
    }
    return 0;
  }
  
  static int szfs_open(const char *path, struct fuse_file_info *fi){
    QMutexLocker locker(&mutex);
    try{
      SzakdolgozatFs_FileHandle *fh=new SzakdolgozatFs_FileHandle(fs, string(path));
      fh->open();
      if(!fh->isOpen) return -ENOENT;
    } catch(int e){
      return e;
    }
    return 0;
  }
  
  static int szfs_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi){
      QMutexLocker locker(&mutex);
      try{
	size_t len;
	  (void) fi;
	  
	SzakdolgozatFs_FileHandle *fh=new SzakdolgozatFs_FileHandle(fs, string(path));
	fh->open();
	if(!fh->isOpen){
	  delete fh;
	  return -ENOENT;
	}
	if(fh->getSize()==0){
	  delete fh;
	  return 0;
	}
	//naploz("olvas :"+string(path)+" "+lts(offset)+" "+lts(size));
	if(offset+size>fh->getSize()){

	  size=fh->getSize()-offset;
	}
	char *tart=new char[size];
	fh->seekg(offset);
	fh->read((unsigned char*)tart, size);
	memcpy(buf, tart, size);
	len=size;
	delete tart;
	delete fh;
	return len;
    } catch(int e){
      return e;
    }
  }
  
  static int szfs_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    QMutexLocker locker(&mutex);
    try{
	(void)fi;
	SzakdolgozatFs_FileHandle *fh=new SzakdolgozatFs_FileHandle(fs, string(path));
	fh->open();
	if(!fh->isOpen){
	  fh->touch();
	  fh->open();
	}
	fh->seekp(offset);
	fh->write((unsigned char*)buf, size);
	return size;
    } catch(int e){
      return e;
    }
  }
  
  static int szfs_mkdir(const char * path, mode_t mode){
    try{
      SzakdolgozatFs_DirectoryHandle* dir=new SzakdolgozatFs_DirectoryHandle(fs, string(path));
      dir->create();
      fs->chown(dir->path, getuid(), getgid());
      delete dir;
    } catch(int e){
      return e;
    }
    return 0;
  }
  
  static int szfs_create(const char * path, mode_t, struct fuse_file_info *fi){
QMutexLocker locker(&mutex);
    try{
      SzakdolgozatFs_FileHandle* fh=new SzakdolgozatFs_FileHandle(fs, string(path));
      fh->touch();
      fs->chown(fh->path, getuid(), getgid());
      delete fh;
    } catch(int e){
	return e;
    }
    return 0;
  }
  
  static int szfs_truncate(const char * path, off_t size) {
    QMutexLocker locker(&mutex);
    try{
      unsigned long nodeBlock=fs->resolveNodeOfFile(string(path));
      if(nodeBlock==-1) return -ENOENT;
      SzakdolgozatFs_Inode *node=new SzakdolgozatFs_Inode();
      fs->getInodeFromBlock(nodeBlock, node);
      if(node->type!=PFS_FILE) return -ENOENT;
      if(size==node->size) return 0;
      if(size>node->size){
	  fs->increaseFileSize(nodeBlock, size);
	  return 0;
      }
      if(size<node->size){
	  fs->decreaseFileSize(nodeBlock, size);
	  return 0;
      }
      delete node;
    } catch(int e){
	return e;
    }
    return 0;
  }
  
  static int szfs_unlink(const char *path){
QMutexLocker locker(&mutex);
      try{
	SzakdolgozatFs_FileHandle *fh=new SzakdolgozatFs_FileHandle(fs, string(path));
	fh->open();
	if(!fh->isOpen) return -ENOENT;
	fh->deleteFile();
	delete fh;
      } catch(int e){
	return e;
      }
      return 0;
  }
  
  //ua mint az unlink
  static int szfs_rmdir(const char *path){
      QMutexLocker locker(&mutex);
      try{
	SzakdolgozatFs_FileHandle *fh=new SzakdolgozatFs_FileHandle(fs, string(path));
	fh->open();
	if(!fh->isOpen) return -ENOENT;
	fh->deleteFile();
	delete fh;
      } catch(int e){
	return e;
      }
      return 0;
  }
}


static struct szfs_operations : fuse_operations{
    szfs_operations(){
      getattr   = SzakdolgozatFs_FuseWrapper::szfs_getattr;
      readdir = SzakdolgozatFs_FuseWrapper::szfs_readdir;
      open   = SzakdolgozatFs_FuseWrapper::szfs_open;
      read   = SzakdolgozatFs_FuseWrapper::szfs_read;
      mkdir= SzakdolgozatFs_FuseWrapper::szfs_mkdir;
      create= SzakdolgozatFs_FuseWrapper::szfs_create;
      utimens=SzakdolgozatFs_FuseWrapper::szfs_utimens;
      write=SzakdolgozatFs_FuseWrapper::szfs_write;
      truncate=SzakdolgozatFs_FuseWrapper::szfs_truncate;
      unlink=SzakdolgozatFs_FuseWrapper::szfs_unlink;
      rmdir=SzakdolgozatFs_FuseWrapper::szfs_rmdir;
      statfs=SzakdolgozatFs_FuseWrapper::szfs_statfs;
      utimens=SzakdolgozatFs_FuseWrapper::szfs_utimens;
      chown=SzakdolgozatFs_FuseWrapper::szfs_chown;
      chmod=SzakdolgozatFs_FuseWrapper::szfs_chmod;
    }
  }szfs_oper;
  
//g++ `pkg-config fuse --cflags --libs` szakdolgozatfs*.cpp -o szd -I/usr/include/qt4/QtCore -I/usr/include/qt4 -lQtCore
int main(int argc, char *argv[]){
  //dd bs=1M count=4 if=/dev/zero of=aures1.img
  
  //fs->loadImage("aures1.img");
  
  /*
  string fileName=string(argv[3]);
  bool reset=(strcmp(argv[2], "-r")==0);
  bool inodeCache=(strcmp(argv[9], "-icb")==0);
  bool blockCache=(strcmp(argv[8], "-bcb")==0);
  
  */
  //fs->resetImage("aures1.img");
  //./szd mnt r/o image.img 100 100 b/k b/k
  //0     1   2   3         4   5   6   7
  cerr<<argc<<endl;
  
  
  ///////////////////////////
  ////debug
  ////////////////////////////
  /*
  if(argc!=9){
    cerr<<"./szd MOUNTPOINT -d r/o IMAGE INODE_CACHE_MERET BLOKK_CACHE_MERET b/k b/k\n";
    cerr<<"./szd mnt -d r aures1.img 100 100 b b\n";
    exit(-1);
  }
  string fileName=string(argv[4]);
  cerr<<fileName<<endl;
  bool reset=(strcmp(argv[3], "r")==0);
  bool inodeCache=(strcmp(argv[7], "b")==0);
  bool blockCache=(strcmp(argv[8], "b")==0);
  int inodeCacheSize=atoi(argv[5]);
  int blockCacheSize=atoi(argv[6]);
  
  if(reset){
    fs->resetImage(fileName);
  } else {
    fs->loadImage(fileName);
  }
  argc=3;
*/

  /////////////////////////////
  ///nem debug
  ////////////////////////////

  if(argc!=8){
    cerr<<"./szd MOUNTPOINT r/o IMAGE INODE_CACHE_MERET BLOKK_CACHE_MERET b/k b/k\n";
    cerr<<"./szd mnt r aures1.img 100 100 b b\n";
    exit(-1);
  }
  string fileName=string(argv[3]);
  cerr<<fileName<<endl;
  bool reset=(strcmp(argv[2], "r")==0);
  bool inodeCache=(strcmp(argv[6], "b")==0);
  bool blockCache=(strcmp(argv[7], "b")==0);
  int inodeCacheSize=atoi(argv[4]);
  int blockCacheSize=atoi(argv[5]);
  
  if(reset){
    fs->resetImage(fileName);
  } else {
    fs->loadImage(fileName);
  }
  argc=2;

/*
  fs->bInodeCacheEnabled=true;
  fs->bBlockCacheEnabled=true;*/
  
  fs->bInodeCacheEnabled=inodeCache;
  fs->bBlockCacheEnabled=blockCache;
  
  delete fs->inodeCache;
  delete fs->blockCache;
  
  fs->inodeCache=new InodeCache(inodeCacheSize);
  fs->blockCache=new BlockCache(blockCacheSize, fs->blockSizeBytes);
  
  fuse_main(argc, argv, &szfs_oper, NULL);
  cerr<<"lefutott\n";
  return 0;
}
