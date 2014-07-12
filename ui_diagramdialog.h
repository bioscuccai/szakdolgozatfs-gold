/********************************************************************************
** Form generated from reading ui file 'diagramdialog.ui'
**
** Created: Tue May 21 02:55:26 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_DIAGRAMDIALOG_H
#define UI_DIAGRAMDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QScrollArea>
#include <QtGui/QSplitter>
#include <QtGui/QTreeWidget>
#include <QtGui/QWidget>
#include "allocwidget.h"

QT_BEGIN_NAMESPACE

class Ui_DiagramDialog
{
public:
    QHBoxLayout *horizontalLayout_2;
    QSplitter *splitter;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout;
    AllocWidget *widget;
    QTreeWidget *dirTree;

    void setupUi(QDialog *DiagramDialog)
    {
        if (DiagramDialog->objectName().isEmpty())
            DiagramDialog->setObjectName(QString::fromUtf8("DiagramDialog"));
        DiagramDialog->resize(496, 290);
        horizontalLayout_2 = new QHBoxLayout(DiagramDialog);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        splitter = new QSplitter(DiagramDialog);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        scrollArea = new QScrollArea(splitter);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 612, 257));
        horizontalLayout = new QHBoxLayout(scrollAreaWidgetContents);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget = new AllocWidget(scrollAreaWidgetContents);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(600, 0));

        horizontalLayout->addWidget(widget);

        scrollArea->setWidget(scrollAreaWidgetContents);
        splitter->addWidget(scrollArea);
        dirTree = new QTreeWidget(splitter);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        dirTree->setHeaderItem(__qtreewidgetitem);
        dirTree->setObjectName(QString::fromUtf8("dirTree"));
        dirTree->setMaximumSize(QSize(300, 16777215));
        splitter->addWidget(dirTree);
        dirTree->header()->setVisible(false);

        horizontalLayout_2->addWidget(splitter);


        retranslateUi(DiagramDialog);

        QMetaObject::connectSlotsByName(DiagramDialog);
    } // setupUi

    void retranslateUi(QDialog *DiagramDialog)
    {
        DiagramDialog->setWindowTitle(QApplication::translate("DiagramDialog", "Helyfoglal\303\241s", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(DiagramDialog);
    } // retranslateUi

};

namespace Ui {
    class DiagramDialog: public Ui_DiagramDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIAGRAMDIALOG_H
