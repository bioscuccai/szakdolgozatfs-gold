#include "fsbeallitasdialog.h"
#include "ui_fsbeallitasdialog.h"

FsBeallitasDialog::FsBeallitasDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::FsBeallitasDialog)
{
    m_ui->setupUi(this);
}

FsBeallitasDialog::~FsBeallitasDialog()
{
    delete m_ui;
}

void FsBeallitasDialog::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void FsBeallitasDialog::on_buttonBox_rejected()
{
    this->close();
}

void FsBeallitasDialog::init(MainWindow *mw_){
    mw=mw_;

    m_ui->blockCacheBox->setChecked(mw->bBlockCache);
    m_ui->inodeCacheBox->setChecked(mw->bInodeCache);

    m_ui->blockCacheLine->setText(QString::number(mw->blockCacheSize));
    m_ui->inodeCacheLine->setText(QString::number(mw->inodeCacheSize));

    m_ui->buffLine->setText(QString::number(mw->opBuffSize));
    m_ui->egybenBox->setChecked(mw->bEgyben);
    m_ui->helyCombo->setCurrentIndex(mw->spaceAlg==SZFS_BEST_FIT?0:1);
}

void FsBeallitasDialog::on_buttonBox_accepted()
{
    mw->bBlockCache=m_ui->blockCacheBox->checkState();
    mw->bInodeCache=m_ui->blockCacheBox->checkState();

    mw->blockCacheSize=m_ui->blockCacheLine->text().toULong();
    mw->inodeCacheSize=m_ui->inodeCacheLine->text().toULong();

    mw->bEgyben=m_ui->egybenBox->checkState();
    mw->opBuffSize=m_ui->buffLine->text().toULong();

    mw->spaceAlg=m_ui->helyCombo->currentIndex()==0?SZFS_BEST_FIT:SZFS_FIRST_FIT;
    mw->applySettings();

    this->close();
}
