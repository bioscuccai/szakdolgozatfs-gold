//tudom, elirtam
#include "fajlszerkeztdialog.h"
#include "ui_fajlszerkeztdialog.h"

#include "szakdolgozatfs_filehandle.h"

#include "fajlrendszersingleton.h"

#include <string>
#include <iostream>
using namespace std;

FajlSzerkeztDialog::FajlSzerkeztDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::FajlSzerkeztDialog),mw(NULL)
{
    m_ui->setupUi(this);
}

FajlSzerkeztDialog::~FajlSzerkeztDialog()
{
    delete m_ui;
}

void FajlSzerkeztDialog::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void FajlSzerkeztDialog::init(QString utvonal_){
    utvonal=utvonal_;
    string ut=utvonal.toAscii().constData();
    SzakdolgozatFs_FileHandle *fh=new SzakdolgozatFs_FileHandle(FajlrendszerSingleton::getInstance(), ut);
    fh->open();
    m_ui->nevLine->setText(QString::fromStdString(ut));

    unsigned long meret=fh->getSize();
    if(meret!=0){
        unsigned char *tartalom=new unsigned char[meret];
        fh->getContents(tartalom);
        QString qs;
        for(unsigned int i=0;i<meret;i++){
            qs+=QChar::fromAscii(tartalom[i]);
            //cerr<<tartalom[i];
        }

        m_ui->tartalomText->insertPlainText(qs);
        delete tartalom;
    }

    delete fh;
}

void FajlSzerkeztDialog::on_buttonBox_accepted()
{
    QString qTartalom=m_ui->tartalomText->toPlainText();
    unsigned long meret=qTartalom.length();
    unsigned char *buff=new unsigned char[meret];
    for(unsigned long i=0;i<meret;i++){
        buff[i]=qTartalom.at(i).toAscii();
    }
    SzakdolgozatFs_FileHandle *fh=new SzakdolgozatFs_FileHandle(FajlrendszerSingleton::getInstance(), utvonal.toAscii().constData());
    fh->open();
    fh->replaceContents(buff, meret);


    if(mw!=NULL){
        mw->loadPanel(true);
        mw->loadPanel(false);
    }

    delete fh;
    delete buff;
}


