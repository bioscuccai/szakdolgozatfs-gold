/********************************************************************************
** Form generated from reading ui file 'ujfajlrendszerdialog.ui'
**
** Created: Fri Mar 15 21:34:29 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_UJFAJLRENDSZERDIALOG_H
#define UI_UJFAJLRENDSZERDIALOG_H

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
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UjFajlrendszerDialog
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *fajlLine;
    QPushButton *tallozButton;
    QLabel *label_2;
    QLineEdit *szektorLine;
    QLabel *label_3;
    QLineEdit *blokkLine;
    QLabel *label_4;
    QLineEdit *meretLine;

    void setupUi(QDialog *UjFajlrendszerDialog)
    {
        if (UjFajlrendszerDialog->objectName().isEmpty())
            UjFajlrendszerDialog->setObjectName(QString::fromUtf8("UjFajlrendszerDialog"));
        UjFajlrendszerDialog->resize(398, 226);
        buttonBox = new QDialogButtonBox(UjFajlrendszerDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 180, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        widget = new QWidget(UjFajlrendszerDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 10, 371, 161));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        fajlLine = new QLineEdit(widget);
        fajlLine->setObjectName(QString::fromUtf8("fajlLine"));

        gridLayout->addWidget(fajlLine, 0, 2, 1, 1);

        tallozButton = new QPushButton(widget);
        tallozButton->setObjectName(QString::fromUtf8("tallozButton"));
        tallozButton->setMaximumSize(QSize(25, 16777215));

        gridLayout->addWidget(tallozButton, 0, 3, 1, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 2);

        szektorLine = new QLineEdit(widget);
        szektorLine->setObjectName(QString::fromUtf8("szektorLine"));

        gridLayout->addWidget(szektorLine, 1, 2, 1, 2);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 2);

        blokkLine = new QLineEdit(widget);
        blokkLine->setObjectName(QString::fromUtf8("blokkLine"));

        gridLayout->addWidget(blokkLine, 2, 2, 1, 2);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        meretLine = new QLineEdit(widget);
        meretLine->setObjectName(QString::fromUtf8("meretLine"));

        gridLayout->addWidget(meretLine, 3, 2, 1, 2);


        retranslateUi(UjFajlrendszerDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), UjFajlrendszerDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), UjFajlrendszerDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(UjFajlrendszerDialog);
    } // setupUi

    void retranslateUi(QDialog *UjFajlrendszerDialog)
    {
        UjFajlrendszerDialog->setWindowTitle(QApplication::translate("UjFajlrendszerDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("UjFajlrendszerDialog", "F\303\241jl:", 0, QApplication::UnicodeUTF8));
        tallozButton->setText(QApplication::translate("UjFajlrendszerDialog", "...", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("UjFajlrendszerDialog", "Szektor m\303\251ret (b\303\241jt):", 0, QApplication::UnicodeUTF8));
        szektorLine->setText(QApplication::translate("UjFajlrendszerDialog", "512", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("UjFajlrendszerDialog", "Blokk m\303\251ret (szektor):", 0, QApplication::UnicodeUTF8));
        blokkLine->setText(QApplication::translate("UjFajlrendszerDialog", "1", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("UjFajlrendszerDialog", "M\303\251ret (kb):", 0, QApplication::UnicodeUTF8));
        meretLine->setText(QApplication::translate("UjFajlrendszerDialog", "4096", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(UjFajlrendszerDialog);
    } // retranslateUi

};

namespace Ui {
    class UjFajlrendszerDialog: public Ui_UjFajlrendszerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UJFAJLRENDSZERDIALOG_H
