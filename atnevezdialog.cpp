#include "atnevezdialog.h"
#include "ui_atnevezdialog.h"

#include "fajlrendszersingleton.h"

#include "szakdolgozatfs_filehandle.h"

#include <QFileInfo>

#include <string>
#include <iostream>

using namespace std;
AtnevezDialog::AtnevezDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::AtnevezDialog),mw(NULL)
{
    m_ui->setupUi(this);
}

AtnevezDialog::~AtnevezDialog()
{
    delete m_ui;
}

void AtnevezDialog::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void AtnevezDialog::init(QString regiUtvonal_){
    regiUtvonal=regiUtvonal_;
    QFileInfo fi(regiUtvonal);
    m_ui->eredetiLine->setText(regiUtvonal);
    m_ui->nevLine->setText(fi.fileName());
}

void AtnevezDialog::on_buttonBox_accepted()
{
    /*
    QFileInfo fi(regiUtvonal);
    string ujUtvonal=fi.absolutePath().toAscii().constData();
    cerr<<"[___accept] "<<ujUtvonal<<endl;
    if(ujUtvonal[ujUtvonal.size()-1]!='/') ujUtvonal+="/";
    ujUtvonal+=m_ui->nevLine->text().toAscii().constData();
    cerr<<"[accept]"<<ujUtvonal<<endl;
*/
    SzakdolgozatFs_FileHandle *fh=new SzakdolgozatFs_FileHandle(FajlrendszerSingleton::getInstance(), regiUtvonal.toAscii().constData());
    fh->rename(m_ui->nevLine->text().toAscii().constData());
    if(mw!=NULL){
        mw->loadPanel(true);
        mw->loadPanel(false);
    }

    delete fh;
}
