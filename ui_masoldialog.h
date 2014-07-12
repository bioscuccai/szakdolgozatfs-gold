/********************************************************************************
** Form generated from reading ui file 'masoldialog.ui'
**
** Created: Thu May 16 02:09:48 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MASOLDIALOG_H
#define UI_MASOLDIALOG_H

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

class Ui_MasolDialog
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLineEdit *eredetiLine;
    QLabel *label;
    QLineEdit *ujLine;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *MasolDialog)
    {
        if (MasolDialog->objectName().isEmpty())
            MasolDialog->setObjectName(QString::fromUtf8("MasolDialog"));
        MasolDialog->resize(396, 131);
        gridLayout = new QGridLayout(MasolDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        eredetiLine = new QLineEdit(MasolDialog);
        eredetiLine->setObjectName(QString::fromUtf8("eredetiLine"));
        eredetiLine->setEnabled(false);

        verticalLayout->addWidget(eredetiLine);

        label = new QLabel(MasolDialog);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        ujLine = new QLineEdit(MasolDialog);
        ujLine->setObjectName(QString::fromUtf8("ujLine"));

        verticalLayout->addWidget(ujLine);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(MasolDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(MasolDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), MasolDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), MasolDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(MasolDialog);
    } // setupUi

    void retranslateUi(QDialog *MasolDialog)
    {
        MasolDialog->setWindowTitle(QApplication::translate("MasolDialog", "M\303\241sol\303\241s", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MasolDialog", "m\303\241sol\303\241sa mint:", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(MasolDialog);
    } // retranslateUi

};

namespace Ui {
    class MasolDialog: public Ui_MasolDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MASOLDIALOG_H
