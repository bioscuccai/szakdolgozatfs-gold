/********************************************************************************
** Form generated from reading ui file 'blockeventdialog.ui'
**
** Created: Thu May 16 23:31:05 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_BLOCKEVENTDIALOG_H
#define UI_BLOCKEVENTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_BlockEventDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTableView *eventTable;
    QHBoxLayout *horizontalLayout;
    QPushButton *clearButton;
    QCheckBox *writeBox;
    QCheckBox *readBox;
    QLineEdit *commLine;
    QPushButton *commButton;

    void setupUi(QDialog *BlockEventDialog)
    {
        if (BlockEventDialog->objectName().isEmpty())
            BlockEventDialog->setObjectName(QString::fromUtf8("BlockEventDialog"));
        BlockEventDialog->resize(604, 564);
        verticalLayout = new QVBoxLayout(BlockEventDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        eventTable = new QTableView(BlockEventDialog);
        eventTable->setObjectName(QString::fromUtf8("eventTable"));

        verticalLayout->addWidget(eventTable);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        clearButton = new QPushButton(BlockEventDialog);
        clearButton->setObjectName(QString::fromUtf8("clearButton"));

        horizontalLayout->addWidget(clearButton);

        writeBox = new QCheckBox(BlockEventDialog);
        writeBox->setObjectName(QString::fromUtf8("writeBox"));
        writeBox->setChecked(true);

        horizontalLayout->addWidget(writeBox);

        readBox = new QCheckBox(BlockEventDialog);
        readBox->setObjectName(QString::fromUtf8("readBox"));
        readBox->setChecked(true);

        horizontalLayout->addWidget(readBox);

        commLine = new QLineEdit(BlockEventDialog);
        commLine->setObjectName(QString::fromUtf8("commLine"));

        horizontalLayout->addWidget(commLine);

        commButton = new QPushButton(BlockEventDialog);
        commButton->setObjectName(QString::fromUtf8("commButton"));

        horizontalLayout->addWidget(commButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(BlockEventDialog);

        QMetaObject::connectSlotsByName(BlockEventDialog);
    } // setupUi

    void retranslateUi(QDialog *BlockEventDialog)
    {
        BlockEventDialog->setWindowTitle(QApplication::translate("BlockEventDialog", "Blokk m\305\261veletek", 0, QApplication::UnicodeUTF8));
        clearButton->setText(QApplication::translate("BlockEventDialog", "T\303\266rl\303\251s", 0, QApplication::UnicodeUTF8));
        writeBox->setText(QApplication::translate("BlockEventDialog", "\303\215r\303\241s", 0, QApplication::UnicodeUTF8));
        readBox->setText(QApplication::translate("BlockEventDialog", "Olvas\303\241s", 0, QApplication::UnicodeUTF8));
        commButton->setText(QApplication::translate("BlockEventDialog", "Megjegyz\303\251s", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(BlockEventDialog);
    } // retranslateUi

};

namespace Ui {
    class BlockEventDialog: public Ui_BlockEventDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BLOCKEVENTDIALOG_H
