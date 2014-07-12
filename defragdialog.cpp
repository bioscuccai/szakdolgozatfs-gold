#include "defragdialog.h"
#include "ui_defragdialog.h"

#include "szakdolgozatfs_filehandle.h"
#include "szakdolgozatfs_directoryhandle.h"

#include <fstream>
#include <iostream>
#include <stack>

#include <QFileDialog>

using namespace std;

DefragDialog::DefragDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::DefragDialog)
{
    m_ui->setupUi(this);
}

DefragDialog::~DefragDialog()
{
    delete m_ui;
}

void DefragDialog::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void DefragDialog::doDefrag(){
    copyFs=new SzakdolgozatFs();
    fstream fajl(m_ui->pathLine->text().toAscii().constData(), ios::out | ios::binary);
    fajl.seekp(FajlrendszerSingleton::getInstance()->imageSize, ios::beg);
    fajl.put(0);
    fajl.close();
    copyFs->resetImage(m_ui->pathLine->text().toAscii().constData());

    stack<string> hatralevo;
    hatralevo.push("/");
    while(!hatralevo.empty()){
        string akt=hatralevo.top();
        hatralevo.pop();
        SzakdolgozatFs_DirectoryHandle *dh=new SzakdolgozatFs_DirectoryHandle(FajlrendszerSingleton::getInstance(), akt);
        dh->open();
        vector<string> fn=dh->getFileNames();
        foreach(string f, fn){
            string filePath=akt+"/"+f;
            f=cutFirstAndLastSlashes(filePath);
            SzakdolgozatFs_FileHandle *fh=new SzakdolgozatFs_FileHandle(FajlrendszerSingleton::getInstance(), filePath);
            fh->open();
            if(fh->getType()==PFS_FILE){
                if(fh->getSize()!=0){
                    unsigned char *buff=new unsigned char[fh->getSize()];
                    FajlrendszerSingleton::getInstance()->getFileContentsFromInode(fh->nodeBlock,buff);
                    cerr<<"[dfg] create file: "<<filePath<<endl;
                    blockAddr newBlockAddr=copyFs->createFileWithContents(filePath,buff, fh->getSize());

                    //extra inode adatok = regi inode - blokk lista cim
                    SzakdolgozatFs_Inode *regiInode=new SzakdolgozatFs_Inode();
                    SzakdolgozatFs_Inode *ujInode=new SzakdolgozatFs_Inode();
                    FajlrendszerSingleton::getInstance()->getInodeFromBlock(fh->nodeBlock, regiInode);
                    copyFs->getInodeFromBlock(newBlockAddr, ujInode);
                    regiInode->blockListLocation=ujInode->blockListLocation;
                    copyFs->replaceInode(newBlockAddr, regiInode);

                    delete regiInode;
                    delete ujInode;

                    delete buff;
                } else {
                    copyFs->createFileWithContents(filePath, NULL, 0);
                }
            } else if(fh->getType()==PFS_DIR && filePath!="/"){
                try{
                    cerr<<"[dfg] createdir: "<<filePath<<endl;
                    copyFs->createDirectory(filePath);
                    hatralevo.push(filePath);
                }catch(int e){
                    cerr<<"[dfg] cd: "<<endl;
                }
            }
            delete fh;
        }
        delete dh;
    }
    delete copyFs;
}

void DefragDialog::on_inditButton_clicked()
{
    doDefrag();
}

void DefragDialog::on_tallozButton_clicked()
{
    saveHere=QFileDialog::getSaveFileName(this);
    m_ui->pathLine->setText(saveHere);
}

void DefragDialog::closeEvent(QCloseEvent *e){

}
