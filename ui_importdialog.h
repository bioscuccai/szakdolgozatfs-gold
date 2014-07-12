/********************************************************************************
** Form generated from reading ui file 'importdialog.ui'
**
** Created: Fri Mar 15 21:34:29 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_IMPORTDIALOG_H
#define UI_IMPORTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ImportDialog
{
public:
    QGridLayout *gridLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QLineEdit *kulsoLine;
    QPushButton *pushButton;
    QLabel *label_2;
    QLineEdit *belsoLine;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ImportDialog)
    {
        if (ImportDialog->objectName().isEmpty())
            ImportDialog->setObjectName(QString::fromUtf8("ImportDialog"));
        ImportDialog->resize(398, 121);
        gridLayout = new QGridLayout(ImportDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(ImportDialog);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        kulsoLine = new QLineEdit(ImportDialog);
        kulsoLine->setObjectName(QString::fromUtf8("kulsoLine"));

        horizontalLayout->addWidget(kulsoLine);

        pushButton = new QPushButton(ImportDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMaximumSize(QSize(30, 16777215));

        horizontalLayout->addWidget(pushButton);


        formLayout->setLayout(0, QFormLayout::FieldRole, horizontalLayout);

        label_2 = new QLabel(ImportDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        belsoLine = new QLineEdit(ImportDialog);
        belsoLine->setObjectName(QString::fromUtf8("belsoLine"));

        formLayout->setWidget(1, QFormLayout::FieldRole, belsoLine);


        gridLayout->addLayout(formLayout, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(ImportDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(ImportDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ImportDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ImportDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ImportDialog);
    } // setupUi

    void retranslateUi(QDialog *ImportDialog)
    {
        ImportDialog->setWindowTitle(QApplication::translate("ImportDialog", "F\303\241jl import\303\241l\303\241sa", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ImportDialog", "K\303\274ls\305\221 f\303\241jl:", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("ImportDialog", "...", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ImportDialog", "Bels\305\221 n\303\251v:", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(ImportDialog);
    } // retranslateUi

};

namespace Ui {
    class ImportDialog: public Ui_ImportDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMPORTDIALOG_H
