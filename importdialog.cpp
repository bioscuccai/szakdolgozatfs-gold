#include "importdialog.h"
#include "ui_importdialog.h"

#include "fajlrendszersingleton.h"

#include "errno.h"

#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>

#include <iostream>

using namespace std;

ImportDialog::ImportDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::ImportDialog), mw(NULL)
{
    m_ui->setupUi(this);

    //m_ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

ImportDialog::~ImportDialog()
{
    delete m_ui;
}

void ImportDialog::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void ImportDialog::init(string utvonal_){
    utvonal=QString::fromStdString(utvonal_);
}

void ImportDialog::on_pushButton_clicked()
{
    kulsoFajl=QFileDialog::getOpenFileName(this);
    /*
    if(kulsoFajl==""){
        m_ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }*/
    m_ui->kulsoLine->setText(kulsoFajl);
    QFileInfo fi(kulsoFajl);
    QString filenev=fi.fileName();
    if(utvonal.size()==0)
        goto gui_tovabb;
    if(utvonal.at(utvonal.size()-1)==QChar('/')){
        belsoFajl=utvonal+filenev;
    } else {
        gui_tovabb:
        belsoFajl=utvonal+"/"+filenev;
    }

    m_ui->belsoLine->setText(belsoFajl);
    //m_ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}

void ImportDialog::on_buttonBox_accepted()
{
    if(m_ui->kulsoLine->text()=="" || m_ui->belsoLine->text()==""){
        QMessageBox::warning(this, "Nincs minden mezo kitoltve", "Nincs minden mezo kitoltve");
        return;
    }
    try{
        FajlrendszerSingleton::getInstance()->copyRealFileToImage(m_ui->kulsoLine->text().toAscii().constData(), m_ui->belsoLine->text().toAscii().constData());
    } catch(int e){
        if(e==-ENOSPC)
            QMessageBox::warning(this, "Nincs eleg hely","Nincs eleg hely az image-en");
        else
            QMessageBox::warning(this, "Valami gaz van",QString::number(e));
    }
    if(mw!=NULL){
        mw->loadPanel(true);
        mw->loadPanel(false);
    }

}
