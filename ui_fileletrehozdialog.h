/********************************************************************************
** Form generated from reading ui file 'fileletrehozdialog.ui'
**
** Created: Fri Mar 15 21:34:29 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_FILELETREHOZDIALOG_H
#define UI_FILELETREHOZDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_FileLetrehozDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *nevLine;

    void setupUi(QDialog *FileLetrehozDialog)
    {
        if (FileLetrehozDialog->objectName().isEmpty())
            FileLetrehozDialog->setObjectName(QString::fromUtf8("FileLetrehozDialog"));
        FileLetrehozDialog->resize(398, 76);
        buttonBox = new QDialogButtonBox(FileLetrehozDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(40, 40, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        nevLine = new QLineEdit(FileLetrehozDialog);
        nevLine->setObjectName(QString::fromUtf8("nevLine"));
        nevLine->setGeometry(QRect(10, 10, 381, 24));

        retranslateUi(FileLetrehozDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), FileLetrehozDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), FileLetrehozDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(FileLetrehozDialog);
    } // setupUi

    void retranslateUi(QDialog *FileLetrehozDialog)
    {
        FileLetrehozDialog->setWindowTitle(QApplication::translate("FileLetrehozDialog", "\303\232j F\303\241jl", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(FileLetrehozDialog);
    } // retranslateUi

};

namespace Ui {
    class FileLetrehozDialog: public Ui_FileLetrehozDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILELETREHOZDIALOG_H
