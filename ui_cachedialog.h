/********************************************************************************
** Form generated from reading ui file 'cachedialog.ui'
**
** Created: Mon Mar 18 00:32:54 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_CACHEDIALOG_H
#define UI_CACHEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListView>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CacheDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QListView *inodeListWidget;
    QLabel *label_2;
    QListView *blockListWidget;

    void setupUi(QDialog *CacheDialog)
    {
        if (CacheDialog->objectName().isEmpty())
            CacheDialog->setObjectName(QString::fromUtf8("CacheDialog"));
        CacheDialog->resize(794, 668);
        verticalLayout = new QVBoxLayout(CacheDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(CacheDialog);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        inodeListWidget = new QListView(CacheDialog);
        inodeListWidget->setObjectName(QString::fromUtf8("inodeListWidget"));
        inodeListWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout->addWidget(inodeListWidget);

        label_2 = new QLabel(CacheDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        blockListWidget = new QListView(CacheDialog);
        blockListWidget->setObjectName(QString::fromUtf8("blockListWidget"));
        blockListWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout->addWidget(blockListWidget);


        retranslateUi(CacheDialog);

        QMetaObject::connectSlotsByName(CacheDialog);
    } // setupUi

    void retranslateUi(QDialog *CacheDialog)
    {
        CacheDialog->setWindowTitle(QApplication::translate("CacheDialog", "Cache \303\241llapot", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("CacheDialog", "Inode cache:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("CacheDialog", "Blokk cache:", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(CacheDialog);
    } // retranslateUi

};

namespace Ui {
    class CacheDialog: public Ui_CacheDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CACHEDIALOG_H
