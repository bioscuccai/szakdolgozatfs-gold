/********************************************************************************
** Form generated from reading ui file 'athelyezdialog.ui'
**
** Created: Fri Mar 15 21:34:29 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_ATHELYEZDIALOG_H
#define UI_ATHELYEZDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AthelyezDialog
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLineEdit *eztLine;
    QLabel *label;
    QLineEdit *ideLine;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *AthelyezDialog)
    {
        if (AthelyezDialog->objectName().isEmpty())
            AthelyezDialog->setObjectName(QString::fromUtf8("AthelyezDialog"));
        AthelyezDialog->resize(398, 117);
        gridLayout = new QGridLayout(AthelyezDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        eztLine = new QLineEdit(AthelyezDialog);
        eztLine->setObjectName(QString::fromUtf8("eztLine"));
        eztLine->setEnabled(false);

        verticalLayout->addWidget(eztLine);

        label = new QLabel(AthelyezDialog);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        ideLine = new QLineEdit(AthelyezDialog);
        ideLine->setObjectName(QString::fromUtf8("ideLine"));

        verticalLayout->addWidget(ideLine);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(AthelyezDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(AthelyezDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), AthelyezDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AthelyezDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(AthelyezDialog);
    } // setupUi

    void retranslateUi(QDialog *AthelyezDialog)
    {
        AthelyezDialog->setWindowTitle(QApplication::translate("AthelyezDialog", "\303\201thelyez\303\251s", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("AthelyezDialog", "\303\241thelyez\303\251se ide:", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(AthelyezDialog);
    } // retranslateUi

};

namespace Ui {
    class AthelyezDialog: public Ui_AthelyezDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ATHELYEZDIALOG_H
