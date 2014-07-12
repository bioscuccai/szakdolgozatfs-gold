/********************************************************************************
** Form generated from reading ui file 'atnevezdialog.ui'
**
** Created: Fri Mar 15 21:34:29 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_ATNEVEZDIALOG_H
#define UI_ATNEVEZDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AtnevezDialog
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLineEdit *eredetiLine;
    QLineEdit *nevLine;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *AtnevezDialog)
    {
        if (AtnevezDialog->objectName().isEmpty())
            AtnevezDialog->setObjectName(QString::fromUtf8("AtnevezDialog"));
        AtnevezDialog->resize(396, 143);
        gridLayout = new QGridLayout(AtnevezDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        eredetiLine = new QLineEdit(AtnevezDialog);
        eredetiLine->setObjectName(QString::fromUtf8("eredetiLine"));
        eredetiLine->setEnabled(false);

        verticalLayout->addWidget(eredetiLine);

        nevLine = new QLineEdit(AtnevezDialog);
        nevLine->setObjectName(QString::fromUtf8("nevLine"));

        verticalLayout->addWidget(nevLine);

        buttonBox = new QDialogButtonBox(AtnevezDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(AtnevezDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), AtnevezDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AtnevezDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(AtnevezDialog);
    } // setupUi

    void retranslateUi(QDialog *AtnevezDialog)
    {
        AtnevezDialog->setWindowTitle(QApplication::translate("AtnevezDialog", "\303\201tnevez\303\251s", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(AtnevezDialog);
    } // retranslateUi

};

namespace Ui {
    class AtnevezDialog: public Ui_AtnevezDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ATNEVEZDIALOG_H
