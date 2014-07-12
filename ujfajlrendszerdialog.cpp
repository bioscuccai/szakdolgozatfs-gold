#include "ujfajlrendszerdialog.h"
#include "ui_ujfajlrendszerdialog.h"

#include <QIntValidator>
#include <QFileDialog>

#include <fajlrendszersingleton.h>

#include <fstream>
#include <iostream>

using namespace std;

UjFajlrendszerDialog::UjFajlrendszerDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::UjFajlrendszerDialog),mw(NULL)
{
    m_ui->setupUi(this);

    QIntValidator *blokkValidator=new QIntValidator(this);
    blokkValidator->setBottom(1);
    m_ui->blokkLine->setValidator(blokkValidator);

    QIntValidator *szektorValidator=new QIntValidator(this);
    szektorValidator->setBottom(1);
    m_ui->szektorLine->setValidator(szektorValidator);

    QIntValidator *meretValidator=new QIntValidator(this);
    meretValidator->setBottom(1024);
    m_ui->meretLine->setValidator(meretValidator);
}

UjFajlrendszerDialog::~UjFajlrendszerDialog()
{
    delete m_ui;
}

void UjFajlrendszerDialog::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void UjFajlrendszerDialog::on_tallozButton_clicked()
{
    QString fajlNev=QFileDialog::getSaveFileName(this);
    m_ui->fajlLine->setText(fajlNev);
}

void UjFajlrendszerDialog::on_buttonBox_accepted()
{
    string fajlNev=m_ui->fajlLine->text().toAscii().constData();
    unsigned long meret=m_ui->meretLine->text().toULong()*1024;
    fstream fajl(fajlNev.c_str(), ios::out | ios::binary);
    fajl.seekp(meret-1, ios::beg);
    fajl.put(0);
    fajl.close();
    try{
        FajlrendszerSingleton::reset();
        FajlrendszerSingleton::getInstance()->resetImage(fajlNev, m_ui->szektorLine->text().toULong(), m_ui->blokkLine->text().toULong());
    } catch(int e){
        cerr<<"kivetel: "<<e<<endl;
        exit(-1);
    }
        if(mw!=NULL){
        mw->loadPanel(true);
        mw->loadPanel(false);
        mw->setWindowTitle("SzakdolgozatFs Commander - "+QString::fromStdString(fajlNev));
        mw->setUsableActionStates();
        mw->applySettings();
    }
}
