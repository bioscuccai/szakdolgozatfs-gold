/********************************************************************************
** Form generated from reading ui file 'infodialog.ui'
**
** Created: Wed May 15 20:47:17 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_INFODIALOG_H
#define UI_INFODIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFormLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QRadioButton>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_infoDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *nevLine;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout;
    QRadioButton *fajlRadio;
    QRadioButton *konyvtarRadio;
    QLabel *label_6;
    QLineEdit *meretLine;
    QLabel *label_3;
    QLineEdit *inodeText;
    QLabel *label_5;
    QLineEdit *blokkKezdLine;
    QLabel *label_10;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_8;
    QLineEdit *uidLine;
    QLabel *label_9;
    QLineEdit *gidLine;
    QLabel *label_11;
    QLineEdit *modeLine;
    QLabel *label_4;
    QTextEdit *blokkListaText;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *infoDialog)
    {
        if (infoDialog->objectName().isEmpty())
            infoDialog->setObjectName(QString::fromUtf8("infoDialog"));
        infoDialog->setEnabled(true);
        infoDialog->resize(463, 509);
        verticalLayout = new QVBoxLayout(infoDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        label = new QLabel(infoDialog);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        nevLine = new QLineEdit(infoDialog);
        nevLine->setObjectName(QString::fromUtf8("nevLine"));
        nevLine->setEnabled(true);
        nevLine->setReadOnly(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, nevLine);

        label_7 = new QLabel(infoDialog);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_7);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        fajlRadio = new QRadioButton(infoDialog);
        fajlRadio->setObjectName(QString::fromUtf8("fajlRadio"));
        fajlRadio->setEnabled(true);
        fajlRadio->setCheckable(true);

        horizontalLayout->addWidget(fajlRadio);

        konyvtarRadio = new QRadioButton(infoDialog);
        konyvtarRadio->setObjectName(QString::fromUtf8("konyvtarRadio"));
        konyvtarRadio->setEnabled(true);
        konyvtarRadio->setCheckable(true);

        horizontalLayout->addWidget(konyvtarRadio);


        formLayout->setLayout(1, QFormLayout::FieldRole, horizontalLayout);

        label_6 = new QLabel(infoDialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_6);

        meretLine = new QLineEdit(infoDialog);
        meretLine->setObjectName(QString::fromUtf8("meretLine"));
        meretLine->setEnabled(true);
        meretLine->setReadOnly(true);

        formLayout->setWidget(2, QFormLayout::FieldRole, meretLine);

        label_3 = new QLabel(infoDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_3);

        inodeText = new QLineEdit(infoDialog);
        inodeText->setObjectName(QString::fromUtf8("inodeText"));
        inodeText->setEnabled(true);
        inodeText->setReadOnly(true);

        formLayout->setWidget(3, QFormLayout::FieldRole, inodeText);

        label_5 = new QLabel(infoDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        blokkKezdLine = new QLineEdit(infoDialog);
        blokkKezdLine->setObjectName(QString::fromUtf8("blokkKezdLine"));
        blokkKezdLine->setEnabled(true);
        blokkKezdLine->setReadOnly(true);

        formLayout->setWidget(4, QFormLayout::FieldRole, blokkKezdLine);

        label_10 = new QLabel(infoDialog);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_10);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_8 = new QLabel(infoDialog);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_2->addWidget(label_8);

        uidLine = new QLineEdit(infoDialog);
        uidLine->setObjectName(QString::fromUtf8("uidLine"));

        horizontalLayout_2->addWidget(uidLine);

        label_9 = new QLabel(infoDialog);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_2->addWidget(label_9);

        gidLine = new QLineEdit(infoDialog);
        gidLine->setObjectName(QString::fromUtf8("gidLine"));

        horizontalLayout_2->addWidget(gidLine);


        formLayout->setLayout(5, QFormLayout::FieldRole, horizontalLayout_2);

        label_11 = new QLabel(infoDialog);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_11);

        modeLine = new QLineEdit(infoDialog);
        modeLine->setObjectName(QString::fromUtf8("modeLine"));

        formLayout->setWidget(6, QFormLayout::FieldRole, modeLine);

        label_4 = new QLabel(infoDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        formLayout->setWidget(7, QFormLayout::LabelRole, label_4);

        blokkListaText = new QTextEdit(infoDialog);
        blokkListaText->setObjectName(QString::fromUtf8("blokkListaText"));
        blokkListaText->setEnabled(true);
        blokkListaText->setReadOnly(true);

        formLayout->setWidget(7, QFormLayout::FieldRole, blokkListaText);


        verticalLayout->addLayout(formLayout);

        buttonBox = new QDialogButtonBox(infoDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);

#ifndef QT_NO_SHORTCUT
        label->setBuddy(nevLine);
#endif // QT_NO_SHORTCUT

        retranslateUi(infoDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), infoDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), infoDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(infoDialog);
    } // setupUi

    void retranslateUi(QDialog *infoDialog)
    {
        infoDialog->setWindowTitle(QApplication::translate("infoDialog", "Inform\303\241ci\303\263", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("infoDialog", "N\303\251v:", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("infoDialog", "T\303\255pus:", 0, QApplication::UnicodeUTF8));
        fajlRadio->setText(QApplication::translate("infoDialog", "F\303\241jl", 0, QApplication::UnicodeUTF8));
        konyvtarRadio->setText(QApplication::translate("infoDialog", "K\303\266nyvt\303\241r", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("infoDialog", "M\303\251ret:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("infoDialog", "i-node azonos\303\255t\303\263:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("infoDialog", "Blokk lista kezdete:", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("infoDialog", "Tulajdonos:", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("infoDialog", "UID:", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("infoDialog", "GID:", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("infoDialog", "M\303\263d:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("infoDialog", "Elfoglalt blokkok:", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(infoDialog);
    } // retranslateUi

};

namespace Ui {
    class infoDialog: public Ui_infoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFODIALOG_H
