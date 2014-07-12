/********************************************************************************
** Form generated from reading ui file 'scandiskdialog.ui'
**
** Created: Thu May 16 23:15:47 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_SCANDISKDIALOG_H
#define UI_SCANDISKDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ScandiskDialog
{
public:
    QVBoxLayout *verticalLayout;
    QPushButton *inditButton;
    QListWidget *problemList;

    void setupUi(QDialog *ScandiskDialog)
    {
        if (ScandiskDialog->objectName().isEmpty())
            ScandiskDialog->setObjectName(QString::fromUtf8("ScandiskDialog"));
        ScandiskDialog->resize(628, 637);
        verticalLayout = new QVBoxLayout(ScandiskDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        inditButton = new QPushButton(ScandiskDialog);
        inditButton->setObjectName(QString::fromUtf8("inditButton"));

        verticalLayout->addWidget(inditButton);

        problemList = new QListWidget(ScandiskDialog);
        problemList->setObjectName(QString::fromUtf8("problemList"));

        verticalLayout->addWidget(problemList);


        retranslateUi(ScandiskDialog);

        QMetaObject::connectSlotsByName(ScandiskDialog);
    } // setupUi

    void retranslateUi(QDialog *ScandiskDialog)
    {
        ScandiskDialog->setWindowTitle(QApplication::translate("ScandiskDialog", "Scandisk", 0, QApplication::UnicodeUTF8));
        inditButton->setText(QApplication::translate("ScandiskDialog", "Ind\303\255t", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(ScandiskDialog);
    } // retranslateUi

};

namespace Ui {
    class ScandiskDialog: public Ui_ScandiskDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCANDISKDIALOG_H
