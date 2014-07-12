/********************************************************************************
** Form generated from reading ui file 'fajlszerkeztdialog.ui'
**
** Created: Fri Mar 15 21:34:29 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_FAJLSZERKEZTDIALOG_H
#define UI_FAJLSZERKEZTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPlainTextEdit>

QT_BEGIN_NAMESPACE

class Ui_FajlSzerkeztDialog
{
public:
    QGridLayout *gridLayout;
    QLineEdit *nevLine;
    QPlainTextEdit *tartalomText;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *FajlSzerkeztDialog)
    {
        if (FajlSzerkeztDialog->objectName().isEmpty())
            FajlSzerkeztDialog->setObjectName(QString::fromUtf8("FajlSzerkeztDialog"));
        FajlSzerkeztDialog->resize(469, 455);
        gridLayout = new QGridLayout(FajlSzerkeztDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        nevLine = new QLineEdit(FajlSzerkeztDialog);
        nevLine->setObjectName(QString::fromUtf8("nevLine"));
        nevLine->setEnabled(false);

        gridLayout->addWidget(nevLine, 0, 0, 1, 1);

        tartalomText = new QPlainTextEdit(FajlSzerkeztDialog);
        tartalomText->setObjectName(QString::fromUtf8("tartalomText"));

        gridLayout->addWidget(tartalomText, 1, 0, 1, 1);

        buttonBox = new QDialogButtonBox(FajlSzerkeztDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 0, 1, 1);


        retranslateUi(FajlSzerkeztDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), FajlSzerkeztDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), FajlSzerkeztDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(FajlSzerkeztDialog);
    } // setupUi

    void retranslateUi(QDialog *FajlSzerkeztDialog)
    {
        FajlSzerkeztDialog->setWindowTitle(QApplication::translate("FajlSzerkeztDialog", "Szerkeszt\303\251s", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(FajlSzerkeztDialog);
    } // retranslateUi

};

namespace Ui {
    class FajlSzerkeztDialog: public Ui_FajlSzerkeztDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FAJLSZERKEZTDIALOG_H
