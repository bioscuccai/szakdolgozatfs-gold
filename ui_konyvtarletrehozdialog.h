/********************************************************************************
** Form generated from reading ui file 'konyvtarletrehozdialog.ui'
**
** Created: Fri Mar 15 21:34:29 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_KONYVTARLETREHOZDIALOG_H
#define UI_KONYVTARLETREHOZDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_KonyvtarLetrehozDialog
{
public:
    QGridLayout *gridLayout;
    QLineEdit *utvonalLine;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *KonyvtarLetrehozDialog)
    {
        if (KonyvtarLetrehozDialog->objectName().isEmpty())
            KonyvtarLetrehozDialog->setObjectName(QString::fromUtf8("KonyvtarLetrehozDialog"));
        KonyvtarLetrehozDialog->resize(398, 80);
        gridLayout = new QGridLayout(KonyvtarLetrehozDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        utvonalLine = new QLineEdit(KonyvtarLetrehozDialog);
        utvonalLine->setObjectName(QString::fromUtf8("utvonalLine"));

        gridLayout->addWidget(utvonalLine, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(KonyvtarLetrehozDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(KonyvtarLetrehozDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), KonyvtarLetrehozDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), KonyvtarLetrehozDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(KonyvtarLetrehozDialog);
    } // setupUi

    void retranslateUi(QDialog *KonyvtarLetrehozDialog)
    {
        KonyvtarLetrehozDialog->setWindowTitle(QApplication::translate("KonyvtarLetrehozDialog", "K\303\266nvt\303\241r l\303\251trehoz\303\241s", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(KonyvtarLetrehozDialog);
    } // retranslateUi

};

namespace Ui {
    class KonyvtarLetrehozDialog: public Ui_KonyvtarLetrehozDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KONYVTARLETREHOZDIALOG_H
