#include "athelyezdialog.h"
#include "ui_athelyezdialog.h"

#include "szakdolgozatfs_filehandle.h"

#include "fajlrendszersingleton.h"

#include <QFileInfo>

AthelyezDialog::AthelyezDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::AthelyezDialog),mw(NULL)
{
    m_ui->setupUi(this);
}

AthelyezDialog::~AthelyezDialog()
{
    delete m_ui;
}

void AthelyezDialog::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void AthelyezDialog::init(QString ezt_, QString ide_){
    ezt=ezt_;
    ide=ide_;
    /*QFileInfo fi(ezt);
    if(ide.at(ide.size()-1)!=QChar('/')) ide+=QChar('/');
    ide+=fi.fileName();*/
    m_ui->eztLine->setText(ezt);
    m_ui->ideLine->setText(ide);
}

void AthelyezDialog::on_buttonBox_accepted()
{
    /*
    SzakdolgozatFs_FileHandle *fInnen=new SzakdolgozatFs_FileHandle(FajlrendszerSingleton::getInstance(), m_ui->eztLine->text().toAscii().constData());
    fInnen->open();
    SzakdolgozatFs_FileHandle *fIde=new SzakdolgozatFs_FileHandle(FajlrendszerSingleton::getInstance(), m_ui->ideLine->text().toAscii().constData());
    fIde->touch();
    unsigned long meret=fInnen->getSize();
    unsigned char *buff=new unsigned char[meret];
    fInnen->getContents(buff);
    fIde->open();
    fIde->replaceContents(buff, meret);

    fInnen->deleteFile();
*/
    SzakdolgozatFs_FileHandle *fh=new SzakdolgozatFs_FileHandle(FajlrendszerSingleton::getInstance(), m_ui->eztLine->text().toAscii().constData());
    fh->move(m_ui->ideLine->text().toAscii().constData());
    delete fh;
    if(mw!=NULL){
        mw->loadPanel(true);
        mw->loadPanel(false);
    }
}
