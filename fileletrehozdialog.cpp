#include "fileletrehozdialog.h"
#include "ui_fileletrehozdialog.h"

#include "fajlrendszersingleton.h"

#include "szakdolgozatfs_filehandle.h"


#include <string>
using namespace std;


FileLetrehozDialog::FileLetrehozDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::FileLetrehozDialog),mw(NULL)
{
    m_ui->setupUi(this);
    //m_ui->nevLine->setFocus();
}

FileLetrehozDialog::~FileLetrehozDialog()
{
    delete m_ui;
}

void FileLetrehozDialog::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void FileLetrehozDialog::init(QString utvonal_){
    utvonal=utvonal_;
    if(utvonal.size()!=0) if(utvonal.at(utvonal.size()-1)!=QChar('/')) utvonal=utvonal+"/";
    m_ui->nevLine->setText(utvonal);
}

void FileLetrehozDialog::on_buttonBox_accepted()
{
    string fileNev=m_ui->nevLine->text().toAscii().constData();
    SzakdolgozatFs_FileHandle *fh=new SzakdolgozatFs_FileHandle(FajlrendszerSingleton::getInstance(), fileNev);
    fh->touch();

    if(mw!=NULL){
        mw->loadPanel(true);
        mw->loadPanel(false);
    }
}
