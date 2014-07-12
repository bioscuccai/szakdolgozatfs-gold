#include "infodialog.h"
#include "ui_infodialog.h"
#include <sys/stat.h>

#include "fajlrendszersingleton.h"

infoDialog::infoDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::infoDialog)
{
    m_ui->setupUi(this);
}

infoDialog::~infoDialog()
{
    delete m_ui;
}

void infoDialog::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void infoDialog::init(QString utvonal_){
    utvonal=utvonal_;

    m_ui->nevLine->setText(utvonal);

    unsigned long nodeBlock=FajlrendszerSingleton::getInstance()->resolveNodeOfFile(utvonal.toAscii().constBegin());
    SzakdolgozatFs_Inode *node=new SzakdolgozatFs_Inode();
    FajlrendszerSingleton::getInstance()->getInodeFromBlock(nodeBlock, node);
    vector<unsigned long> blockList=FajlrendszerSingleton::getInstance()->getBlockListFromInodeBlock(nodeBlock);
    QString blokkListaString;
    foreach(unsigned long i, blockList){
        blokkListaString+=QString::number(i)+" ";
    }
    if(node->type==PFS_DIR) m_ui->konyvtarRadio->setChecked(true);
    if(node->type==PFS_FILE) m_ui->fajlRadio->setChecked(true);
    m_ui->meretLine->setText(QString::number(node->size));
    m_ui->blokkKezdLine->setText(QString::number(node->blockListLocation));
    m_ui->blokkListaText->insertPlainText(blokkListaString);
    m_ui->inodeText->setText(QString::number(nodeBlock));

    m_ui->uidLine->setText(QString::number(node->uid));
    m_ui->gidLine->setText(QString::number(node->gid));

    //chmod
    QString modeStr;
    //u
    if(node->mode&S_IRUSR) modeStr+="r"; else modeStr+="-";
    if(node->mode&S_IWUSR) modeStr+="w"; else modeStr+="-";
    if(node->mode&S_IXUSR) modeStr+="x"; else modeStr+="-";
    //g
    if(node->mode&S_IRGRP) modeStr+="r"; else modeStr+="-";
    if(node->mode&S_IWGRP) modeStr+="w"; else modeStr+="-";
    if(node->mode&S_IXGRP) modeStr+="x"; else modeStr+="-";
    //o
    if(node->mode&S_IROTH) modeStr+="r"; else modeStr+="-";
    if(node->mode&S_IWOTH) modeStr+="w"; else modeStr+="-";
    if(node->mode&S_IXOTH) modeStr+="x"; else modeStr+="-";

    m_ui->modeLine->setText(modeStr);
}
