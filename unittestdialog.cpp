#include "unittestdialog.h"
#include "ui_unittestdialog.h"

UnitTestDialog::UnitTestDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::UnitTestDialog)
{
    m_ui->setupUi(this);
    td=new Test_Directory(FajlrendszerSingleton::getInstance());
    tf=new Test_File(FajlrendszerSingleton::getInstance());
}

UnitTestDialog::~UnitTestDialog()
{
    delete m_ui;
}

void UnitTestDialog::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void UnitTestDialog::on_irasButton_clicked()
{
    m_ui->irasBox->setChecked(tf->testFwrite("write test"));
}

void UnitTestDialog::on_olvasasButton_clicked()
{
    m_ui->olvasasBox->setChecked(tf->testFread("read test"));
}

void UnitTestDialog::on_uresButton_clicked()
{
    m_ui->uresBox->setChecked(tf->testIncreaseFile("empty test"));
}

void UnitTestDialog::on_torlesButton_clicked()
{
    m_ui->torlesBox->setChecked(tf->testDelete("delete test"));
}

void UnitTestDialog::on_novelesButton_clicked()
{
    m_ui->novelesBox->setChecked(tf->testIncreaseFile("increase test"));
}

void UnitTestDialog::on_kirasButton_clicked()
{
    m_ui->kirasBox->setChecked(td->testDirectoryCreation("dir creation test"));
}

void UnitTestDialog::on_kletrehozasButton_clicked()
{
    m_ui->kletrehozBox->setChecked(td->testDirectoryNewFile("directory file test/"));
}

void UnitTestDialog::on_csokkentButton_clicked()
{
    m_ui->csokkentBox->setChecked(tf->testDecreaseFile("decrease file"));
}
