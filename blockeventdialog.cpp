#include "blockeventdialog.h"
#include "ui_blockeventdialog.h"

#include "fajlrendszersingleton.h"
#include "szakdolgozatfs.h"

#include <sys/time.h>
#include <ctime>
#include <cstring>
#include <QListWidgetItem>
#include <iostream>
#include <QDateTime>

using namespace std;

BlockEventDialog::BlockEventDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::BlockEventDialog)
{
    m_ui->setupUi(this);

    setupTable();
}

BlockEventDialog::~BlockEventDialog()
{
    delete m_ui;
}

void BlockEventDialog::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void BlockEventDialog::closeEvent(QCloseEvent *e){
    FajlrendszerSingleton::getInstance()->removeBlockHandler(this);
}

void BlockEventDialog::init(MainWindow *mw_){
    mw=mw_;
    //FajlrendszerSingleton::getInstance()->blockEvent=&(BlockEventDialog::blockEventHandler);
    //FajlrendszerSingleton::getInstance()->bcbh=this;
    FajlrendszerSingleton::getInstance()->addBlockHandler(this);
}

void BlockEventDialog::on_BlockEventDialog_destroyed()
{
    //FajlrendszerSingleton::getInstance()->blockEvent=NULL;
    //mw->bed=NULL;
    //FajlrendszerSingleton::getInstance()->bcbh=NULL;
    FajlrendszerSingleton::getInstance()->removeBlockHandler(this);
}

void BlockEventDialog::on_BlockEventDialog_rejected()
{
    //FajlrendszerSingleton::getInstance()->blockEvent=NULL;
    //mw->bed=NULL;
    //FajlrendszerSingleton::getInstance()->bcbh=NULL;
    FajlrendszerSingleton::getInstance()->removeBlockHandler(this);
}


void BlockEventDialog::blockEventHandler(BlockCallbackInfo* i){
    if(i->type==BEC_GET && !m_ui->readBox->isChecked()) return;
    if(i->type==BEC_SET && !m_ui->writeBox->isChecked()) return;
    //QListWidgetItem *item=new QListWidgetItem(m_ui->blockEventList);
    QString muvTipus=i->type==BEC_GET?"[OLV]":"[IR]";
    timespec nt;
    clock_gettime(CLOCK_REALTIME, &nt);
    char szTime[20];
    //strftime(&szTime, 20, "%H:%M:%S:", &(nt));
    //QString t=QString::fromStdString(string(szTime));
    //t+=QString::number(nt.tv_nsec);
    //sprintf(&szTime,"%lld.%.9ld", (long long)nt.tv_sec, nt.tv_nsec);
    QString t;//=QString::fromStdString(szTime);
    QString start=QString::number(i->start);
    QString size=QString::number(i->size);

    QString lineString=muvTipus+"@"+t+" | "+start+" ("+size+")";
/*
    item->setText(lineString);
    m_ui->blockEventList->addItem(item);
    m_ui->blockEventList->scrollToBottom();
*/
    QDateTime tm;
    QList<QStandardItem*> sor;
    sor.append(new QStandardItem(muvTipus));
    sor.append(new QStandardItem(tm.currentDateTime().toString("hh:mm:ss:zzz")));
    sor.append(new QStandardItem(QString::number(i->start)));
    sor.append(new QStandardItem(QString::number(i->size)));
    sor.append(new QStandardItem(i->cached?"I":"N"));
    //sor.append(new QStandardItem("0"));
    tableModel->appendRow(sor);
    int cRow=tableModel->rowCount()-1;
    if(i->cached)
    for(int i=0;i<6;i++){
        QModelIndex c=tableModel->index(cRow,i);
        tableModel->setData(c, Qt::lightGray, Qt::BackgroundColorRole);
    }
    m_ui->eventTable->scrollToBottom();
}


void BlockEventDialog::getNotice(QString mit, bool szf){
    //QListWidgetItem *item=new QListWidgetItem(m_ui->blockEventList);
    //item->setBackground(Qt::cyan);
    //item->setText(mit);
    //m_ui->blockEventList->addItem(item);
    //m_ui->blockEventList->scrollToBottom();
    //cerr<<mit.toStdString()<<endl;
    tableModel->appendRow(new QStandardItem(mit));
    int cRow=tableModel->rowCount()-1;
    tableModel->setData(tableModel->index(cRow,0), szf?Qt::cyan:Qt::yellow, Qt::BackgroundColorRole);
}

void BlockEventDialog::doCallback(BlockCallbackInfo* i){
    blockEventHandler(i);
}

void BlockEventDialog::doNotice(string msg){
    getNotice(QString::fromStdString(msg));
}


void BlockEventDialog::setupTable(){
    tableModel=new QStandardItemModel(0,5,this);
    m_ui->eventTable->setModel(tableModel);
    tableModel->setHorizontalHeaderItem(0, new QStandardItem("Tipus/leiras"));
    tableModel->setHorizontalHeaderItem(1, new QStandardItem("ido"));
    tableModel->setHorizontalHeaderItem(2, new QStandardItem("innen"));
    tableModel->setHorizontalHeaderItem(3, new QStandardItem("ennyi"));
    tableModel->setHorizontalHeaderItem(4, new QStandardItem("cache"));
    //tableModel->setHorizontalHeaderItem(5, new QStandardItem("dt"));
}

void BlockEventDialog::on_clearButton_clicked()
{
    tableModel->clear();
}

void BlockEventDialog::on_commButton_clicked()
{
    getNotice(m_ui->commLine->text(), false);
}
