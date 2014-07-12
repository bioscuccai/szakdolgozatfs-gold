/********************************************************************************
** Form generated from reading ui file 'defragdialog.ui'
**
** Created: Mon Mar 25 05:09:45 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_DEFRAGDIALOG_H
#define UI_DEFRAGDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DefragDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *pathLine;
    QPushButton *tallozButton;
    QPushButton *inditButton;

    void setupUi(QDialog *DefragDialog)
    {
        if (DefragDialog->objectName().isEmpty())
            DefragDialog->setObjectName(QString::fromUtf8("DefragDialog"));
        DefragDialog->resize(396, 138);
        verticalLayout = new QVBoxLayout(DefragDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pathLine = new QLineEdit(DefragDialog);
        pathLine->setObjectName(QString::fromUtf8("pathLine"));

        horizontalLayout->addWidget(pathLine);

        tallozButton = new QPushButton(DefragDialog);
        tallozButton->setObjectName(QString::fromUtf8("tallozButton"));

        horizontalLayout->addWidget(tallozButton);


        verticalLayout->addLayout(horizontalLayout);

        inditButton = new QPushButton(DefragDialog);
        inditButton->setObjectName(QString::fromUtf8("inditButton"));

        verticalLayout->addWidget(inditButton);


        retranslateUi(DefragDialog);

        QMetaObject::connectSlotsByName(DefragDialog);
    } // setupUi

    void retranslateUi(QDialog *DefragDialog)
    {
        DefragDialog->setWindowTitle(QApplication::translate("DefragDialog", "T\303\266redezetts\303\251gmentes\303\255tett ment\303\251s", 0, QApplication::UnicodeUTF8));
        tallozButton->setText(QApplication::translate("DefragDialog", "...", 0, QApplication::UnicodeUTF8));
        inditButton->setText(QApplication::translate("DefragDialog", "Ind\303\255t", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(DefragDialog);
    } // retranslateUi

};

namespace Ui {
    class DefragDialog: public Ui_DefragDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEFRAGDIALOG_H
