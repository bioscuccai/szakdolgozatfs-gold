#include "mainwindow.h"
#include "ui_mainwindow.h"


#include "infodialog.h"
#include "atnevezdialog.h"
#include "importdialog.h"
#include "masoldialog.h"
#include "athelyezdialog.h"
#include "fileletrehozdialog.h"
#include "konyvtarletrehozdialog.h"
#include "fajlszerkeztdialog.h"
#include "ujfajlrendszerdialog.h"
#include "unittestdialog.h"
#include "diagramdialog.h"
#include "cachedialog.h"
#include "scandiskdialog.h"
#include "fsbeallitasdialog.h"
#include "defragdialog.h"
#include "blockeventdialog.h"

#include "fajlrendszersingleton.h"

#include "szakdolgozatfs.h"
#include "szakdolgozatfs_filehandle.h"
#include "szakdolgozatfs_directoryhandle.h"

#include <QMessageBox>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QDebug>
#include <QDateTime>

#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>

using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowClass)
{
    ui->setupUi(this);

    leftPath="/";
    rightPath="/";

    setupPanels();

    leftPanelActive=true;
    setActivePanel(true);

    ui->leftTable->setColumnWidth(0,25);
    ui->rightTable->setColumnWidth(0,25);

    ui->mainToolBar->addAction(ui->actionUjImage);
    ui->mainToolBar->addAction(ui->actionImageMegnyit);
    ui->mainToolBar->addAction(ui->actionImageMasolat);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(ui->actionDiagram);
    ui->mainToolBar->addAction(ui->actionCache);
    ui->mainToolBar->addAction(ui->actionKonzisztencia);
    ui->mainToolBar->addAction(ui->actionFilerendszer);
    ui->mainToolBar->addAction(ui->actionToredezettseg);
    ui->mainToolBar->addAction(ui->actionBlokkMuvelet);


    statusCacheLabel=new QLabel(this);
    statusSpaceLabel=new QLabel(this);

    spaceAlg=SZFS_BEST_FIT;

    statusBar()->addWidget(statusSpaceLabel);
    statusBar()->addWidget(statusCacheLabel);
    //FajlrendszerSingleton::getInstance()->resetImage("kep.img");

    setDefaultActionStates();

    initSettings();

    //bed=NULL;
}

void MainWindow::setDefaultActionStates(){
    ui->actionDiagram->setEnabled(false);
    ui->actionCache->setEnabled(false);
    ui->actionKonzisztencia->setEnabled(false);
    ui->actionImageMasolat->setEnabled(false);
    ui->actionToredezettseg->setEnabled(false);
    ui->actionBlokkMuvelet->setEnabled(false);
    //ui->action
}

void MainWindow::setUsableActionStates(){
    ui->actionDiagram->setEnabled(true);
    ui->actionCache->setEnabled(true);
    ui->actionKonzisztencia->setEnabled(true);
    ui->actionImageMasolat->setEnabled(true);
    ui->actionToredezettseg->setEnabled(true);
    ui->actionBlokkMuvelet->setEnabled(true);
/*
    //ideiglenesen
    ui->actionImageMegnyit->setEnabled(false);
    ui->actionUjImage->setEnabled(false);*/
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initSettings(){
    bBlockCache=false;
    bInodeCache=false;
    inodeCacheSize=100;
    blockCacheSize=100;
    bEgyben=false;
    opBuffSize=1024;
}

void MainWindow::applySettings(){
    if(FajlrendszerSingleton::instance!=NULL){
        FajlrendszerSingleton::getInstance()->bBlockCacheEnabled=bBlockCache;
        FajlrendszerSingleton::getInstance()->bInodeCacheEnabled=bInodeCache;
        delete FajlrendszerSingleton::getInstance()->inodeCache;
        delete FajlrendszerSingleton::getInstance()->blockCache;

        FajlrendszerSingleton::getInstance()->spaceAlg=spaceAlg;
        FajlrendszerSingleton::getInstance()->inodeCache=new InodeCache(inodeCacheSize);
        FajlrendszerSingleton::getInstance()->blockCache=new BlockCache(blockCacheSize, FajlrendszerSingleton::getInstance()->blockSizeBytes);
    }
}

void MainWindow::setupPanelModel(QStandardItemModel* model){
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("T")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Nev")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Meret")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("i-node")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QString("Modositva")));
}

void MainWindow::setupPanels(){
    leftModel=new QStandardItemModel(0,4,this);
    setupPanelModel(leftModel);

    rightModel=new QStandardItemModel(0,4,this);
    setupPanelModel(rightModel);

    ui->leftTable->setModel(leftModel);
    ui->rightTable->setModel(rightModel);

    ui->rightPathLabel->setText(QString::fromStdString(rightPath));
    ui->leftPathLabel->setText(QString::fromStdString(leftPath));

    ui->leftTable->setColumnWidth(0,25);
    ui->rightTable->setColumnWidth(0,25);
}

void MainWindow::on_athelyezButton_clicked()
{
    QString ezt=getSelectedFile(leftPanelActive);
    QString ide=getSelectedPath(!leftPanelActive);
    AthelyezDialog *dialog=new AthelyezDialog(this);
    dialog->mw=this;
    dialog->init(ezt, ide);
    dialog->show();
}

void MainWindow::on_atnevezButton_clicked()
{
    QString fajl=getSelectedFile(leftPanelActive);
    AtnevezDialog *dialog=new AtnevezDialog(this);
    dialog->mw=this;
    dialog->init(fajl);
    dialog->show();
}

void MainWindow::on_infoButton_clicked()
{
    QString fajl=getSelectedFile(leftPanelActive);
    infoDialog *dialog=new infoDialog(this);
    dialog->init(fajl);
    dialog->show();
}


void MainWindow::on_leftTable_clicked(QModelIndex index)
{
    //aktiv oldal kivalasztasa
    leftPanelActive=true;
    setActivePanel(true);
}

void MainWindow::setActivePanel(bool left){
    QLabel *activeLabel, *inactiveLabel;
    string activePath, inactivePath;
    if(left){
        activeLabel=ui->leftPathLabel;
        inactiveLabel=ui->rightPathLabel;
        activePath=leftPath;
        inactivePath=rightPath;
    } else {
        activeLabel=ui->rightPathLabel;
        inactiveLabel=ui->leftPathLabel;
        activePath=rightPath;
        inactivePath=leftPath;
    }
    activeLabel->setText(QString::fromStdString("<b>[" + activePath +"]</b>"));
    inactiveLabel->setText(QString::fromStdString(inactivePath));
}

void MainWindow::on_rightTable_clicked(QModelIndex index)
{
    leftPanelActive=false;
    setActivePanel(false);
}

void MainWindow::on_actionFilerendszer_triggered()
{
    FsBeallitasDialog *dialog=new FsBeallitasDialog();
    dialog->init(this);
    dialog->show();
}

void MainWindow::on_importButton_clicked()
{
    ImportDialog *dialog=new ImportDialog(this);
    dialog->mw=this;
    dialog->init(getSelectedPath(leftPanelActive).toAscii().constData());
    dialog->show();
}

QString MainWindow::getSelectedFile(bool left){
    vector<string> *fList=left?&leftRowPath:&rightRowPath;
    QModelIndexList l=(left?ui->leftTable:ui->rightTable)->selectionModel()->selection().indexes();
    foreach(QModelIndex i, l){
        cerr<<"index: "<<i.row()<<endl;
        if(i.row()>=fList->size()){
            cerr<<"[getSelected] tomb meret: "<<fList->size()<<" kert index: "<<i.row()<<endl;
            return "";
        }
        return QString::fromStdString(fList->at(i.row()));
    }

    {
        QMessageBox *msg=new QMessageBox();
        msg->setText(QString("nincs kijelolt fajl a ")+(left?QString("bal"):QString("jobb"))+QString(" oldalon"));
        msg->exec();
    }
    cerr<<"[getSelected] nincs kijelolt fajl a "<<(left?"bal":"jobb")<<"\n";
    //return left?"/bal/oldali/fajl.nev":"/jobb/oldali/file.nev";
    return "";
}

QString MainWindow::getSelectedPath(bool left){
    return QString::fromStdString(left?leftPath:rightPath);
}
void MainWindow::on_masolButton_clicked()
{
    QString eFajl, uUtvonal;
    if(leftPanelActive){
        eFajl=getSelectedFile(true);
        uUtvonal=QString::fromStdString(rightPath);
    }else{
        eFajl=getSelectedFile(false);
        uUtvonal=QString::fromStdString(leftPath);
    }
    MasolDialog *dialog=new MasolDialog();
    dialog->mw=this;
    dialog->init(eFajl, uUtvonal);
    dialog->show();
}

void MainWindow::on_exportButton_clicked()
{
    QString belsoNev=getSelectedFile(leftPanelActive);
    if(belsoNev=="") return;
    QString exportNev=QFileDialog::getSaveFileName(this);

/*
    QMessageBox *msg=new QMessageBox();
    msg->setText(belsoNev + "->" + exportNev);
    msg->exec();*/

    fstream ki(exportNev.toAscii().constData(), ios::binary | ios::out);
    SzakdolgozatFs_FileHandle *fh=new SzakdolgozatFs_FileHandle(FajlrendszerSingleton::getInstance(), belsoNev.toAscii().constData());
    fh->open();
    unsigned long meret=fh->getSize();
    unsigned char *buff=new unsigned char[meret];
    fh->getContents(buff);
    ki.write((char*)buff, meret);

    ki.close();
    delete buff;
    delete fh;
}

void MainWindow::on_ujFileButton_clicked()
{
    FileLetrehozDialog *dialog=new FileLetrehozDialog(this);
    dialog->mw=this;
    dialog->init(getSelectedPath(leftPanelActive));
    dialog->show();
}

void MainWindow::setStatusbarInfo(){
    unsigned long f=0, u=0;
    FajlrendszerSingleton::getInstance()->getFreeAndUsedBlocks(&f, &u);
    statusSpaceLabel->setText(QString("Blokkok(sz/f): "+ QString::number(f) +" / "+QString::number(u)+" | "));
    statusCacheLabel->setText("Blokk cache["+
                                      QString(FajlrendszerSingleton::getInstance()->bBlockCacheEnabled?"BE":"KI")+
                                      "] "+
                                      QString::number(FajlrendszerSingleton::getInstance()->blockCache->darab)+"/"+
                                      QString::number(FajlrendszerSingleton::getInstance()->blockCache->maxEntries)+

                                      " | Inode cache ["+
                                      QString(FajlrendszerSingleton::getInstance()->bInodeCacheEnabled?"BE":"KI")+
                                      "]"+
                                      QString::number(FajlrendszerSingleton::getInstance()->inodeCache->darab)+"/"+
                                      QString::number(FajlrendszerSingleton::getInstance()->inodeCache->maxEntries));
}

void MainWindow::on_frissitBalButton_clicked()
{
    if(FajlrendszerSingleton::instance==NULL) return;
/*
    SzakdolgozatFs_DirectoryHandle *dh=new SzakdolgozatFs_DirectoryHandle(FajlrendszerSingleton::getInstance(), "/");
    dh->open();
    vector<string> kl;
    kl=dh->getFileNames();
    QString tartalomLista;

    for(int i=0;i<kl.size();i++){
        string utvonal="/"+kl.at(i);
        long nodeBlock=FajlrendszerSingleton::getInstance()->resolveNodeOfFile(utvonal);
        tartalomLista+=QString::fromStdString(utvonal) +" "+QString::number(nodeBlock)+"\n";
    }

    QMessageBox *msg=new QMessageBox();
    msg->setText(tartalomLista);
    msg->exec();

*/
    loadPanel(true);
    loadPanel(false);
    /*
    ui->leftTable->setColumnWidth(0,25);
    ui->rightTable->setColumnWidth(0,25);*/

    setStatusbarInfo();
}

void MainWindow::on_ujKonyvtarButton_clicked()
{
    KonyvtarLetrehozDialog *dialog=new KonyvtarLetrehozDialog(this);
    dialog->mw=this;
    dialog->init(getSelectedPath(leftPanelActive));
    dialog->show();
}

void MainWindow::loadPanel(bool left){
    QStandardItemModel *model=left?leftModel:rightModel;
    vector<string> *rowPathList=left?&leftRowPath:&rightRowPath;
    string uv=left?leftPath:rightPath;
    if(uv.at(uv.size()-1)!='/') uv+="/";
    SzakdolgozatFs_DirectoryHandle *dh=new SzakdolgozatFs_DirectoryHandle(FajlrendszerSingleton::getInstance(), uv);
    dh->open();
    vector<string> fileNevek=dh->getFileNames();
    rowPathList->clear();

    if(ui->leftTable->model()!=NULL){
        leftPanelWidths.clear();
        rightPanelWidths.clear();
        for(int i=0;i<ui->leftTable->model()->columnCount();i++){
            leftPanelWidths.push_back(ui->leftTable->columnWidth(i));
            rightPanelWidths.push_back(ui->rightTable->columnWidth(i));
        }
    }

    model->clear();
    setupPanelModel(model);

    //..
    {
        QList<QStandardItem *> sor;
        sor.append(new QStandardItem(QString("..")));
        sor.append(new QStandardItem(QString("..")));
        sor.append(new QStandardItem(QString("..")));
        sor.append(new QStandardItem(QString("..")));
        sor.append(new QStandardItem(QString("..")));
        model->appendRow(sor);
        cerr<<"szulo: "<<parentFromPath(uv)<<endl;
        rowPathList->push_back(parentFromPath(uv));
    }
    for(unsigned int i=0;i<fileNevek.size();i++){
        string teljesUt=uv + fileNevek.at(i);
        cerr<<teljesUt<<endl;
        rowPathList->push_back(teljesUt);
        unsigned long nodeBlock=FajlrendszerSingleton::getInstance()->resolveNodeOfFile(teljesUt);
        SzakdolgozatFs_Inode* node=new SzakdolgozatFs_Inode();
        if(nodeBlock==-1){
            cerr<<"minusz egy\n";
            continue;
        }
        FajlrendszerSingleton::getInstance()->getInodeFromBlock(nodeBlock, node);
        QDateTime ts;
        ts.setTime_t(node->lastModification);

        QList<QStandardItem *> sor;
        //tipus
        sor.append(new QStandardItem(QString::fromAscii((node->type == PFS_FILE)?"F":"K")));
        //nev
        sor.append(new QStandardItem(QString::fromStdString(fileNevek.at(i))));
        //meret
        sor.append(new QStandardItem(QString::number(node->size)));
        //inode
        sor.append(new QStandardItem(QString::number(nodeBlock)));
        //modositva
        sor.append(new QStandardItem(ts.toString(Qt::SystemLocaleShortDate)));
        model->appendRow(sor);

        delete node;
    }
/*
    ui->leftTable->setColumnWidth(0,25);
    ui->rightTable->setColumnWidth(0,25);*/

    for(int i=0;i<leftPanelWidths.size();i++){
        ui->leftTable->setColumnWidth(i,leftPanelWidths.at(i));
        ui->rightTable->setColumnWidth(i,rightPanelWidths.at(i));
    }
    setStatusbarInfo();

}

void MainWindow::on_frissitJobbButton_clicked()
{
    if(FajlrendszerSingleton::instance==NULL) return;
    loadPanel(false);
    loadPanel(true);
    setStatusbarInfo();
}


void MainWindow::switchDirectory(bool left, unsigned int index){

    if(left){
        SzakdolgozatFs_FileHandle *fh=new SzakdolgozatFs_FileHandle(FajlrendszerSingleton::getInstance(), leftRowPath.at(index));
        fh->open();
        SzakdolgozatFs_Filetype ft=fh->getType();
        delete fh;
        if(ft!=PFS_DIR) return;
        leftPath=leftRowPath.at(index);
    } else {
        SzakdolgozatFs_FileHandle *fh=new SzakdolgozatFs_FileHandle(FajlrendszerSingleton::getInstance(), rightRowPath.at(index));
        fh->open();
        SzakdolgozatFs_Filetype ft=fh->getType();
        delete fh;
        if(ft!=PFS_DIR) return;
        rightPath=rightRowPath.at(index);
    }
    loadPanel(left);
    setActivePanel(left);
}
void MainWindow::on_leftTable_doubleClicked(QModelIndex index)
{
    switchDirectory(true, index.row());
}

void MainWindow::on_rightTable_doubleClicked(QModelIndex index)
{
    switchDirectory(false, index.row());
}

void MainWindow::on_leftTable_activated(QModelIndex index)
{
    leftPanelActive=true;
    setActivePanel(true);
}

void MainWindow::on_rightTable_activated(QModelIndex index)
{
    leftPanelActive=false;
    setActivePanel(false);
}

void MainWindow::on_szerkeztButton_clicked()
{
    FajlSzerkeztDialog *dialog=new FajlSzerkeztDialog();
    dialog->mw=this;
    dialog->init(getSelectedFile(leftPanelActive));
    dialog->show();
}

void MainWindow::on_actionUjImage_triggered()
{
    UjFajlrendszerDialog *dialog=new UjFajlrendszerDialog();
    dialog->mw=this;
    dialog->show();
}

void MainWindow::on_actionImageMegnyit_triggered()
{
    QString fajlNev=QFileDialog::getOpenFileName(this);
    if(fajlNev=="") return;
    FajlrendszerSingleton::reset();
    FajlrendszerSingleton::getInstance()->loadImage(fajlNev.toAscii().constData());
    loadPanel(true);
    loadPanel(false);
    setWindowTitle("SzakdolgozatFs Commander - "+fajlNev);
    setUsableActionStates();
    applySettings();
}

void MainWindow::on_leftUpButton_clicked()
{
    if(FajlrendszerSingleton::instance==NULL) return;
    gotoParent(true);
}

void MainWindow::on_rightUpButton_clicked()
{
    if(FajlrendszerSingleton::instance==NULL) return;
    gotoParent(false);
}


void MainWindow::gotoParent(bool left){
    string ujUtvonal=parentFromPath(left?leftPath:rightPath);
    if(left) leftPath=ujUtvonal;
            rightPath=ujUtvonal;
    setActivePanel(left);
    loadPanel(left);
}

void MainWindow::on_actionKilep_triggered()
{
    qApp->exit();
}

void MainWindow::on_actionUnitTest_triggered()
{
    UnitTestDialog *dialog=new UnitTestDialog();
    dialog->show();
}

void MainWindow::on_torolButton_clicked()
{
    string torlendo=getSelectedFile(leftPanelActive).toAscii().constData();
    if(torlendo=="") return;
    try{
        SzakdolgozatFs_FileHandle *fh=new SzakdolgozatFs_FileHandle(FajlrendszerSingleton::getInstance(), torlendo);
        fh->open();
        fh->deleteFile();
        delete fh;
    }catch(int e){
        QMessageBox::warning(this,"Hiba", QString::fromAscii(strerror(0-e)));
    }
    loadPanel(true);
    loadPanel(false);
}

void MainWindow::on_actionDiagram_triggered()
{
    DiagramDialog *dd=new DiagramDialog();
    dd->init();
    dd->show();
}

void MainWindow::on_actionCache_triggered()
{
    CacheDialog *dialog=new CacheDialog();
    dialog->show();
}

void MainWindow::on_actionKonzisztencia_triggered()
{
    ScandiskDialog *dialog=new ScandiskDialog();
    dialog->show();
}

void MainWindow::on_actionImageMasolat_triggered()
{
    QString nev=QFileDialog::getSaveFileName(this);
    ofstream of(nev.toAscii().constData(), fstream::binary|fstream::trunc);

    //of<<(FajlrendszerSingleton::getInstance()->imageFile->rdbuf());
    int beolvasva=0;
    char *buff=new char[opBuffSize];
    while(beolvasva!=FajlrendszerSingleton::getInstance()->imageSize){
        int olvasando=(((FajlrendszerSingleton::getInstance()->imageSize)-opBuffSize)>=0)?opBuffSize:(FajlrendszerSingleton::getInstance()->imageSize);
        FajlrendszerSingleton::getInstance()->imageFile->seekg(beolvasva, ios::beg);
        FajlrendszerSingleton::getInstance()->imageFile->read(buff, olvasando);
        of.seekp(beolvasva, ios::beg);
        of.write(buff, olvasando);
        beolvasva+=olvasando;
    }
    delete buff;
    of.flush();
    of.close();
}

void MainWindow::on_actionToredezettseg_triggered()
{
    DefragDialog *dialog=new DefragDialog();
    dialog->show();
}

void MainWindow::on_actionBlokkMuvelet_triggered()
{
    BlockEventDialog *dialog=new BlockEventDialog();
    dialog->init(this);
    //bed=dialog;
    dialog->show();
}

/*
void MainWindow::blockNotice(QString mit){

}

void MainWindow::setupBlockEvents(){
    CallbackWorkaroundImpl *wa=new CallbackWorkaroundImpl();
    wa->mw=this;
    FajlrendszerSingleton::getInstance()->wa=wa;
}
void CallbackWorkaroundImpl::doCallback(BlockCallbackInfo i){
    if(mw->bed!=NULL) mw->bed->blockEventHandler(i);
}
*/
void MainWindow::closeEvent(QCloseEvent *e){
    FajlrendszerSingleton::reset();
}
