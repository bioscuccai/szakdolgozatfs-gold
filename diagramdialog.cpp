#include "diagramdialog.h"
#include "ui_diagramdialog.h"
#include "fajlrendszersingleton.h"
#include "szakdolgozatfs_filehandle.h"
#include "szakdolgozatfs_directoryhandle.h"

#include <stack>
#include <iostream>

using namespace std;

DiagramDialog::DiagramDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::DiagramDialog)
{
    m_ui->setupUi(this);
}

DiagramDialog::~DiagramDialog()
{
    delete m_ui;
}

void DiagramDialog::init(){
    prevInodeCache=FajlrendszerSingleton::getInstance()->bInodeCacheEnabled;
    prevBlockCache=FajlrendszerSingleton::getInstance()->bBlockCacheEnabled;

    FajlrendszerSingleton::getInstance()->bInodeCacheEnabled=false;
    FajlrendszerSingleton::getInstance()->bBlockCacheEnabled=false;


    stack<string> hatraLevo;
    hatraLevo.push("/");
    while(!hatraLevo.empty()){
        string akt=hatraLevo.top();
        hatraLevo.pop();
        SzakdolgozatFs_DirectoryHandle *dh=new SzakdolgozatFs_DirectoryHandle(FajlrendszerSingleton::getInstance(), akt);
        dh->open();
        vector<string> fl=dh->getFileNames();
        if(akt=="/"){
            QTreeWidgetItem *root=new QTreeWidgetItem();
            root->setText(0,"/");
            m_ui->dirTree->addTopLevelItem(root);
            unsigned long ri=FajlrendszerSingleton::getInstance()->resolveNodeOfFile("/");
            wPaths[root]=ri;
            dirs[ri]=root;
        }
        for(int i=0;i<fl.size();i++){
           string filePath=akt+"/"+fl.at(i);
           SzakdolgozatFs_FileHandle *fh=new SzakdolgozatFs_FileHandle(FajlrendszerSingleton::getInstance(), filePath);
           fh->open();

           QTreeWidgetItem *itm=new QTreeWidgetItem(dirs[FajlrendszerSingleton::getInstance()->resolveNodeOfFile(akt)]);
           itm->setText(0,QString::fromStdString( (fh->getType()==PFS_DIR?"[K]":"[F]") + fl.at(i)));
           itm->setStatusTip(0,QString::fromStdString(filePath));
           wPaths[itm]=FajlrendszerSingleton::getInstance()->resolveNodeOfFile(filePath);
           if(fh->getType()==PFS_DIR){
               hatraLevo.push(filePath);
               dirs[fh->nodeBlock]=itm;
           }
           delete fh;
        }

        delete dh;
    }

    FajlrendszerSingleton::getInstance()->bInodeCacheEnabled=prevInodeCache;
    FajlrendszerSingleton::getInstance()->bBlockCacheEnabled=prevBlockCache;

    m_ui->dirTree->expandAll();
}

void DiagramDialog::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


void DiagramDialog::on_dirTree_itemActivated(QTreeWidgetItem* item, int column)
{
    QList<QTreeWidgetItem*> l=m_ui->dirTree->selectedItems();
    foreach(QTreeWidgetItem* i, l){
        //cerr<<wPaths[i]<<endl;
        m_ui->widget->highlightFile=wPaths[i];
        m_ui->widget->update();
    }
}

void DiagramDialog::on_dirTree_clicked(QModelIndex index)
{

}
