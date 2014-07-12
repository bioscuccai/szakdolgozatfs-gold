#include "masoldialog.h"
#include "ui_masoldialog.h"

#include "szakdolgozatfs_filehandle.h"

#include "fajlrendszersingleton.h"

#include <QFileInfo>
#include <QProgressDialog>
#include <QMessageBox>

#include <iostream>
#include <cstring>


using namespace std;


MasolDialog::MasolDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::MasolDialog),mw(NULL)
{
    m_ui->setupUi(this);
}

MasolDialog::~MasolDialog()
{
    delete m_ui;
}

void MasolDialog::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MasolDialog::init(QString eFajl, QString uUtvonal){
    eredetiFajl=eFajl;
    ujUtvonal=uUtvonal;

    QFileInfo fi(eredetiFajl);
    QString fajlNev=fi.fileName();
    if(ujUtvonal.size()==0) ujUtvonal="/";
    else if(ujUtvonal.at(ujUtvonal.size()-1)!=QChar('/')) ujUtvonal=ujUtvonal+"/";

    m_ui->eredetiLine->setText(eredetiFajl);
    m_ui->ujLine->setText(ujUtvonal + fajlNev);
}

void MasolDialog::on_buttonBox_accepted()
{
    try{
    SzakdolgozatFs_FileHandle *innen=new SzakdolgozatFs_FileHandle(FajlrendszerSingleton::getInstance(), eredetiFajl.toAscii().constData());
    innen->open();
    SzakdolgozatFs_FileHandle *ide=new SzakdolgozatFs_FileHandle(FajlrendszerSingleton::getInstance(), m_ui->ujLine->text().toAscii().constData());
    ide->touch();
    unsigned long meret=innen->getSize();
    //unsigned char *buff=new unsigned char[meret];
    //innen->getContents(buff);
    ide->open();


    //FajlrendszerSingleton::getInstance()->increaseFileSize(ide->nodeBlock, meret);
    int beolvasva=0;
    int bm=512;
    QProgressDialog pd(this);
    while(beolvasva!=meret){
        int olvasando=(meret-beolvasva)>=bm?bm:(meret-beolvasva);
        unsigned char *b=new unsigned char[bm];

        unsigned char *c=new unsigned char[bm];
        memset(c, 'a', bm);
        innen->read(b, olvasando);
        ide->write(b, olvasando);
        beolvasva+=olvasando;
        pd.setValue( (int)(( (beolvasva+0.0)/meret)*100.0)  );
        //cerr<<beolvasva<<" / "<<olvasando<<" / "<<meret<<endl;
        innen->seekg(beolvasva);
        ide->seekp(beolvasva);
        delete c;
        delete b;
    }
    pd.close();
    //ide->replaceContents(buff, meret);
    } catch(int e){
        QMessageBox::warning(this, "Hiba", QString::fromAscii(strerror(0-e)));
    }
    if(mw!=NULL){
        mw->loadPanel(true);
        mw->loadPanel(false);
    }

    //delete buff;
}
