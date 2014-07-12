#include "konyvtarletrehozdialog.h"
#include "ui_konyvtarletrehozdialog.h"

#include "fajlrendszersingleton.h"

#include "szakdolgozatfs_directoryhandle.h"

KonyvtarLetrehozDialog::KonyvtarLetrehozDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::KonyvtarLetrehozDialog),mw(NULL)
{
    m_ui->setupUi(this);
}

KonyvtarLetrehozDialog::~KonyvtarLetrehozDialog()
{
    delete m_ui;
}

void KonyvtarLetrehozDialog::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void KonyvtarLetrehozDialog::init(QString utvonal_){
    utvonal=utvonal_;
    if(utvonal.at(utvonal.size()-1)!=QChar('/')) utvonal+=QChar('/');
    m_ui->utvonalLine->setText(utvonal);
}

void KonyvtarLetrehozDialog::on_buttonBox_accepted()
{
    string path=m_ui->utvonalLine->text().toAscii().constData();
    SzakdolgozatFs_DirectoryHandle *dh=new SzakdolgozatFs_DirectoryHandle(FajlrendszerSingleton::getInstance(), path);
    dh->create();
    if(mw!=NULL){
        mw->loadPanel(true);
        mw->loadPanel(false);
    }
}
