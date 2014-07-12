#include "scandiskdialog.h"
#include "ui_scandiskdialog.h"

#include "szakdolgozatfs_filehandle.h"
#include "szakdolgozatfs_directoryhandle.h"
#include "fajlrendszersingleton.h"

#include <QListWidgetItem>
#include <QMessageBox>


ScandiskDialog::ScandiskDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::ScandiskDialog)
{
    m_ui->setupUi(this);
}

ScandiskDialog::~ScandiskDialog()
{
    delete m_ui;
}

void ScandiskDialog::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

FsProblem::FsProblem(ProblemType pt, vector<string> ps, vector<unsigned long> bl):problem(pt),paths(ps),blocks(bl),solved(false),node(-1),dir(-1){
}

FsProblem::FsProblem(ProblemType pt, vector<string> ps, vector<unsigned long> bl, blockAddr d, blockAddr n):problem(pt),paths(ps),blocks(bl),solved(false),node(n),dir(d){
}
void ScandiskDialog::addProblem(ProblemType pt, vector<string> ps, vector<unsigned long> bl){
    problems.push_back(new FsProblem(pt,ps,bl));
}
void ScandiskDialog::addProblem(ProblemType pt, vector<string> ps, vector<unsigned long> bl, blockAddr dir, blockAddr node){
    problems.push_back(new FsProblem(pt,ps,bl, dir, node));
}
void ScandiskDialog::on_problemList_itemActivated(QListWidgetItem* item)
{
    FsProblem *problem=problems.at(item->data(Qt::UserRole).toInt());
    switch(problem->problem){
        case FSP_UNUSED_BLOCK:
            if(QMessageBox::question(this, "Javitas", "Nem hasznalt blokk felszabaditasa?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
            {
                setBlocks(problem->blocks,false);
                problem->solved=true;
                fillProblemList();
            }
            break;

        case FSP_NOT_ALLOCATED_BLOCKLIST:
        case FSP_NOT_ALLOCATED_INODE:
        case FSP_NOT_ALLOCATED_DATA:
            if(QMessageBox::question(this, "Javitas", "Lefoglalatlan blokkok lefoglalasa?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
            {
                setBlocks(problem->blocks,true);
                problem->solved=true;
                fillProblemList();
            }
            break;
        case FSP_INVALID_LOC_BLOCKLIST:
        case FSP_INVALID_LOC_DATA:
        case FSP_INVALID_LOC_INODE:
            if((QMessageBox::question(this, "Javitas", "File torlese? Utanna ujabb ellenorzes szukseges.", QMessageBox::Yes, QMessageBox::No)==QMessageBox::Yes)
                && problem->dir!=-1 && problem->node!=-1)
            {
                FajlrendszerSingleton::getInstance()->removeFileFromDirectory(problem->node, problem->dir);
                problem->solved;
                fillProblemList();

            }
            break;
    }
}
//nagyreszt az allocwidget masolata

void ScandiskDialog::setBlocks(vector<blockAddr> bl, bool to){
    foreach(blockAddr b, bl){
        setAllocationMapPosition(FajlrendszerSingleton::getInstance()->bitmap, b, to);
    }
    FajlrendszerSingleton::getInstance()->writeBitmap();
}

void ScandiskDialog::checkFile(string p, blockAddr dir, blockAddr node){
    SzakdolgozatFs_FileHandle *fh=new SzakdolgozatFs_FileHandle(FajlrendszerSingleton::getInstance(), p);
    fh->open();
    unsigned long nodeBlock=fh->nodeBlock;
    SzakdolgozatFs_Inode *inode=new SzakdolgozatFs_Inode();

    FajlrendszerSingleton::getInstance()->getInodeFromBlock(nodeBlock, inode);
    vector<unsigned long> bl=FajlrendszerSingleton::getInstance()->getBlockListFromInodeBlock(nodeBlock);

    //rossz helyen van az inode
    bool isInodeInvalid=false;
    vector<unsigned long> iiLoc;
    vector<string> iiName;

    //nincs lefoglalva a helye
    bool isInodeNotAllocated=false;
    vector<unsigned long> liLoc;
    vector<string> liName;

    //inode
    long inodeBlockSizeInBlocks=FajlrendszerSingleton::getInstance()->blocksNeededPerSize(sizeof(SzakdolgozatFs_Inode));
    for(int i=0;i<inodeBlockSizeInBlocks;i++){
        if(blockMap.count(nodeBlock+i)==1){
            blockMap[nodeBlock+i]->type=WST_INODE;
            blockMap[nodeBlock+i]->file=nodeBlock;

            //nincs lefoglalva
            if(blockMap[nodeBlock+i]->used==false){
                isInodeNotAllocated=true;
                liLoc.push_back(i);
                liName.push_back(p);
            }

        } else {//nincs jo helyen az inode
            isInodeInvalid=true;
            iiLoc.push_back(nodeBlock+i);
            if(iiName.size()!=1) iiName.push_back(p);
        }
    }
    if(isInodeInvalid) addProblem(FSP_INVALID_LOC_INODE,iiName,iiLoc, dir, node);
    if(isInodeNotAllocated) addProblem(FSP_NOT_ALLOCATED_INODE, liName, liLoc);


    bool isDInvalid=false;
    vector<unsigned long> idLoc;
    vector<string> idName;

    bool isDataNotAllocated=false;
    vector<unsigned long> ldLoc;
    vector<string> ldName;

    //lefoglalt blokkok
    for(int i=0;i<bl.size();i++){
        if(blockMap.count(bl.at(i))==1){
            blockMap[bl.at(i)]->type=WST_DATA;
            blockMap[bl.at(i)]->file=nodeBlock;

            //nincs lefoglalva
            if(blockMap[nodeBlock+i]->used==false){
                isDataNotAllocated=true;
                ldLoc.push_back(i);
                ldName.push_back(p);
            }
        } else {
            isDInvalid=true;
            idLoc.push_back(nodeBlock+i);
            if(idName.size()!=1) idName.push_back(p);
        }
    }
    if(isDInvalid) addProblem(FSP_INVALID_LOC_DATA, idName, idLoc, dir, node);
    if(isDataNotAllocated) addProblem(FSP_NOT_ALLOCATED_DATA, ldName, ldLoc);


    bool isBlInvalid=false;
    vector<unsigned long> ibLoc;
    vector<string> ibName;

    bool isBlNotAllocated=false;
    vector<unsigned long> lbLoc;
    vector<string> lbName;

    //blokk lista
    long blocksForBlockList=FajlrendszerSingleton::getInstance()->blocksNeededPerSize(bl.size()*sizeof(unsigned long));
    for(int i=0;i<blocksForBlockList;i++){
        if(blockMap.count(inode->blockListLocation+i)==1){
            blockMap[inode->blockListLocation+i]->type=WST_BL;
            blockMap[inode->blockListLocation+i]->file=nodeBlock;

            //nincs lefoglalva
            if(blockMap[nodeBlock+i]->used==false){
                isBlNotAllocated=true;
                lbLoc.push_back(i);
                lbName.push_back(p);
            }

        } else {
            isBlInvalid=true;
            ibLoc.push_back(nodeBlock+i);
            if(ibName.size()!=1) ibName.push_back(p);
        }
    }
    if(isBlInvalid) addProblem(FSP_INVALID_LOC_BLOCKLIST, ibName, ibLoc, dir, node);
    if(isBlNotAllocated) addProblem(FSP_NOT_ALLOCATED_BLOCKLIST, lbName, lbLoc);

    delete fh;
}

void ScandiskDialog::fillMap(){
    //osszes blokk
    for(unsigned long i=0;i<FajlrendszerSingleton::getInstance()->numberOfBlocks;i++){
        blockMap[i]=new WidgetSquare(WST_UK, -1, getAllocationMapPosition(FajlrendszerSingleton::getInstance()->bitmap,i));
    }
    //superblock
    long superBlockSizeBlocks=FajlrendszerSingleton::getInstance()->blocksNeededPerSize(sizeof(SzakdolgozatFs_Inode));
    for(unsigned long int i=0;i<superBlockSizeBlocks;i++){
        blockMap[i]->type=WST_SUPER;
    }
    //alloc tabla
    for(unsigned long int i=superBlockSizeBlocks;i<FajlrendszerSingleton::getInstance()->bitmapSizeBlocks+1;i++){
        blockMap[i]->type=WST_ALLOC;
    }



    stack<string> hatraLevo;
    hatraLevo.push("/");
    checkFile("/",-1,-1);
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
           if(fh->getType()==PFS_DIR) hatraLevo.push(filePath);
           checkFile(filePath, dh->nodeBlock, fh->nodeBlock);
           delete fh;
        }

        delete dh;
    }
}

void ScandiskDialog::checkForUnusedBlocks(){
    for(unsigned long i=0;i<FajlrendszerSingleton::getInstance()->numberOfBlocks;i++){
        if(blockMap[i]->type==WST_UK && blockMap.at(i)->used==true){
            vector<unsigned long> bl;
            bl.push_back(i);
            vector<string> nl;
            addProblem(FSP_UNUSED_BLOCK, nl, bl);
        }
    }
}

void ScandiskDialog::fillProblemList(){
    m_ui->problemList->clear();
    for(unsigned int i=0;i<problems.size();i++){
        if(problems.at(i)->solved) continue;
        QString desc;
        switch(problems.at(i)->problem){
            case FSP_UNUSED_BLOCK:
                desc="Kihasznalatlan blokk";
                break;
            case FSP_INVALID_LOC_INODE:
                desc="Ervenytelen inode hely";
                break;
            case FSP_INVALID_LOC_BLOCKLIST:
                desc="Ervenytelen blokk lista hely";
                break;
            case FSP_INVALID_LOC_DATA:
                desc="Ervenytelen adat hely";
                break;
        }


        QString files="( ";
        foreach(string s,problems.at(i)->paths){
            files+=QString::fromStdString(s)+" ";
        }
        files+=")";

        QString blocks="[ ";
        foreach(unsigned long s,problems.at(i)->blocks){
            blocks+=QString::number(s)+" ";
        }
        blocks+="]";

        QString line=desc+" / "+files+" / "+blocks;
        QListWidgetItem *item=new QListWidgetItem(m_ui->problemList);
        item->setText(line);
        item->setData(Qt::UserRole, i);
        m_ui->problemList->addItem(item);
    }
}

void ScandiskDialog::on_inditButton_clicked()
{
    fillMap();
    m_ui->problemList->clear();
    problems.clear();
    checkForUnusedBlocks();
    fillProblemList();
}
