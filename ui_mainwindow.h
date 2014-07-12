/********************************************************************************
** Form generated from reading ui file 'mainwindow.ui'
**
** Created: Wed May 15 00:19:38 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTableView>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QAction *actionImageMegnyit;
    QAction *actionKilep;
    QAction *actionImageMasolat;
    QAction *actionLemezMuvelet;
    QAction *actionHelyfoglalas;
    QAction *actionNaploAllapot;
    QAction *actionFilerendszer;
    QAction *actionUnitTest;
    QAction *actionUjImage;
    QAction *actionDiagram;
    QAction *actionCache;
    QAction *actionKonzisztencia;
    QAction *actionToredezettseg;
    QAction *actionBlokkMuvelet;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *balCimsor;
    QLabel *leftPathLabel;
    QPushButton *frissitBalButton;
    QPushButton *leftUpButton;
    QHBoxLayout *jobbCimsor;
    QPushButton *rightUpButton;
    QPushButton *frissitJobbButton;
    QLabel *rightPathLabel;
    QHBoxLayout *horizontalLayout;
    QTableView *leftTable;
    QTableView *rightTable;
    QHBoxLayout *gombSor;
    QPushButton *infoButton;
    QPushButton *szerkeztButton;
    QPushButton *masolButton;
    QPushButton *athelyezButton;
    QPushButton *atnevezButton;
    QPushButton *torolButton;
    QPushButton *importButton;
    QPushButton *exportButton;
    QPushButton *ujKonyvtarButton;
    QPushButton *ujFileButton;
    QMenuBar *menuBar;
    QMenu *menuF_jl;
    QMenu *menuN_zet;
    QMenu *menuBe_ll_t_sok;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QString::fromUtf8("MainWindowClass"));
        MainWindowClass->resize(1030, 672);
        actionImageMegnyit = new QAction(MainWindowClass);
        actionImageMegnyit->setObjectName(QString::fromUtf8("actionImageMegnyit"));
        actionKilep = new QAction(MainWindowClass);
        actionKilep->setObjectName(QString::fromUtf8("actionKilep"));
        actionImageMasolat = new QAction(MainWindowClass);
        actionImageMasolat->setObjectName(QString::fromUtf8("actionImageMasolat"));
        actionLemezMuvelet = new QAction(MainWindowClass);
        actionLemezMuvelet->setObjectName(QString::fromUtf8("actionLemezMuvelet"));
        actionHelyfoglalas = new QAction(MainWindowClass);
        actionHelyfoglalas->setObjectName(QString::fromUtf8("actionHelyfoglalas"));
        actionNaploAllapot = new QAction(MainWindowClass);
        actionNaploAllapot->setObjectName(QString::fromUtf8("actionNaploAllapot"));
        actionFilerendszer = new QAction(MainWindowClass);
        actionFilerendszer->setObjectName(QString::fromUtf8("actionFilerendszer"));
        actionUnitTest = new QAction(MainWindowClass);
        actionUnitTest->setObjectName(QString::fromUtf8("actionUnitTest"));
        actionUjImage = new QAction(MainWindowClass);
        actionUjImage->setObjectName(QString::fromUtf8("actionUjImage"));
        actionDiagram = new QAction(MainWindowClass);
        actionDiagram->setObjectName(QString::fromUtf8("actionDiagram"));
        actionCache = new QAction(MainWindowClass);
        actionCache->setObjectName(QString::fromUtf8("actionCache"));
        actionKonzisztencia = new QAction(MainWindowClass);
        actionKonzisztencia->setObjectName(QString::fromUtf8("actionKonzisztencia"));
        actionToredezettseg = new QAction(MainWindowClass);
        actionToredezettseg->setObjectName(QString::fromUtf8("actionToredezettseg"));
        actionBlokkMuvelet = new QAction(MainWindowClass);
        actionBlokkMuvelet->setObjectName(QString::fromUtf8("actionBlokkMuvelet"));
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setMargin(11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        balCimsor = new QHBoxLayout();
        balCimsor->setSpacing(6);
        balCimsor->setObjectName(QString::fromUtf8("balCimsor"));
        leftPathLabel = new QLabel(centralWidget);
        leftPathLabel->setObjectName(QString::fromUtf8("leftPathLabel"));

        balCimsor->addWidget(leftPathLabel);

        frissitBalButton = new QPushButton(centralWidget);
        frissitBalButton->setObjectName(QString::fromUtf8("frissitBalButton"));
        frissitBalButton->setMaximumSize(QSize(25, 16777215));

        balCimsor->addWidget(frissitBalButton);

        leftUpButton = new QPushButton(centralWidget);
        leftUpButton->setObjectName(QString::fromUtf8("leftUpButton"));
        leftUpButton->setMaximumSize(QSize(30, 16777215));

        balCimsor->addWidget(leftUpButton);


        horizontalLayout_2->addLayout(balCimsor);

        jobbCimsor = new QHBoxLayout();
        jobbCimsor->setSpacing(6);
        jobbCimsor->setObjectName(QString::fromUtf8("jobbCimsor"));
        rightUpButton = new QPushButton(centralWidget);
        rightUpButton->setObjectName(QString::fromUtf8("rightUpButton"));
        rightUpButton->setMaximumSize(QSize(30, 16777215));

        jobbCimsor->addWidget(rightUpButton);

        frissitJobbButton = new QPushButton(centralWidget);
        frissitJobbButton->setObjectName(QString::fromUtf8("frissitJobbButton"));
        frissitJobbButton->setMaximumSize(QSize(25, 16777215));

        jobbCimsor->addWidget(frissitJobbButton);

        rightPathLabel = new QLabel(centralWidget);
        rightPathLabel->setObjectName(QString::fromUtf8("rightPathLabel"));

        jobbCimsor->addWidget(rightPathLabel);


        horizontalLayout_2->addLayout(jobbCimsor);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        leftTable = new QTableView(centralWidget);
        leftTable->setObjectName(QString::fromUtf8("leftTable"));
        leftTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        leftTable->setSelectionMode(QAbstractItemView::SingleSelection);
        leftTable->setSelectionBehavior(QAbstractItemView::SelectRows);

        horizontalLayout->addWidget(leftTable);

        rightTable = new QTableView(centralWidget);
        rightTable->setObjectName(QString::fromUtf8("rightTable"));
        rightTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        rightTable->setSelectionMode(QAbstractItemView::SingleSelection);
        rightTable->setSelectionBehavior(QAbstractItemView::SelectRows);

        horizontalLayout->addWidget(rightTable);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        gombSor = new QHBoxLayout();
        gombSor->setSpacing(6);
        gombSor->setObjectName(QString::fromUtf8("gombSor"));
        infoButton = new QPushButton(centralWidget);
        infoButton->setObjectName(QString::fromUtf8("infoButton"));

        gombSor->addWidget(infoButton);

        szerkeztButton = new QPushButton(centralWidget);
        szerkeztButton->setObjectName(QString::fromUtf8("szerkeztButton"));

        gombSor->addWidget(szerkeztButton);

        masolButton = new QPushButton(centralWidget);
        masolButton->setObjectName(QString::fromUtf8("masolButton"));

        gombSor->addWidget(masolButton);

        athelyezButton = new QPushButton(centralWidget);
        athelyezButton->setObjectName(QString::fromUtf8("athelyezButton"));

        gombSor->addWidget(athelyezButton);

        atnevezButton = new QPushButton(centralWidget);
        atnevezButton->setObjectName(QString::fromUtf8("atnevezButton"));

        gombSor->addWidget(atnevezButton);

        torolButton = new QPushButton(centralWidget);
        torolButton->setObjectName(QString::fromUtf8("torolButton"));

        gombSor->addWidget(torolButton);

        importButton = new QPushButton(centralWidget);
        importButton->setObjectName(QString::fromUtf8("importButton"));

        gombSor->addWidget(importButton);

        exportButton = new QPushButton(centralWidget);
        exportButton->setObjectName(QString::fromUtf8("exportButton"));

        gombSor->addWidget(exportButton);

        ujKonyvtarButton = new QPushButton(centralWidget);
        ujKonyvtarButton->setObjectName(QString::fromUtf8("ujKonyvtarButton"));

        gombSor->addWidget(ujKonyvtarButton);

        ujFileButton = new QPushButton(centralWidget);
        ujFileButton->setObjectName(QString::fromUtf8("ujFileButton"));

        gombSor->addWidget(ujFileButton);


        gridLayout->addLayout(gombSor, 2, 0, 1, 1);

        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1030, 23));
        menuF_jl = new QMenu(menuBar);
        menuF_jl->setObjectName(QString::fromUtf8("menuF_jl"));
        menuN_zet = new QMenu(menuBar);
        menuN_zet->setObjectName(QString::fromUtf8("menuN_zet"));
        menuBe_ll_t_sok = new QMenu(menuBar);
        menuBe_ll_t_sok->setObjectName(QString::fromUtf8("menuBe_ll_t_sok"));
        MainWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindowClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindowClass->setStatusBar(statusBar);

        menuBar->addAction(menuF_jl->menuAction());
        menuBar->addAction(menuN_zet->menuAction());
        menuBar->addAction(menuBe_ll_t_sok->menuAction());
        menuF_jl->addAction(actionUjImage);
        menuF_jl->addAction(actionImageMegnyit);
        menuF_jl->addAction(actionImageMasolat);
        menuF_jl->addSeparator();
        menuF_jl->addAction(actionKilep);
        menuN_zet->addAction(actionLemezMuvelet);
        menuN_zet->addAction(actionHelyfoglalas);
        menuN_zet->addAction(actionDiagram);
        menuN_zet->addAction(actionCache);
        menuN_zet->addAction(actionKonzisztencia);
        menuBe_ll_t_sok->addAction(actionFilerendszer);
        menuBe_ll_t_sok->addAction(actionUnitTest);
        menuBe_ll_t_sok->addAction(actionToredezettseg);
        menuBe_ll_t_sok->addAction(actionBlokkMuvelet);

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "SzakdolgozatFs Commander", 0, QApplication::UnicodeUTF8));
        actionImageMegnyit->setText(QApplication::translate("MainWindowClass", "Image megnyit\303\241sa", 0, QApplication::UnicodeUTF8));
        actionKilep->setText(QApplication::translate("MainWindowClass", "Kil\303\251p\303\251s", 0, QApplication::UnicodeUTF8));
        actionImageMasolat->setText(QApplication::translate("MainWindowClass", "Image m\303\241solat ment\303\251se", 0, QApplication::UnicodeUTF8));
        actionLemezMuvelet->setText(QApplication::translate("MainWindowClass", "Lemez m\305\261veletek", 0, QApplication::UnicodeUTF8));
        actionHelyfoglalas->setText(QApplication::translate("MainWindowClass", "Helyfoglal\303\241s", 0, QApplication::UnicodeUTF8));
        actionNaploAllapot->setText(QApplication::translate("MainWindowClass", "Napl\303\263 \303\241llapot", 0, QApplication::UnicodeUTF8));
        actionFilerendszer->setText(QApplication::translate("MainWindowClass", "Filerendszer", 0, QApplication::UnicodeUTF8));
        actionUnitTest->setText(QApplication::translate("MainWindowClass", "Unit Test", 0, QApplication::UnicodeUTF8));
        actionUjImage->setText(QApplication::translate("MainWindowClass", "\303\232j Image", 0, QApplication::UnicodeUTF8));
        actionDiagram->setText(QApplication::translate("MainWindowClass", "Diagram", 0, QApplication::UnicodeUTF8));
        actionCache->setText(QApplication::translate("MainWindowClass", "Cache", 0, QApplication::UnicodeUTF8));
        actionKonzisztencia->setText(QApplication::translate("MainWindowClass", "Konzisztencia", 0, QApplication::UnicodeUTF8));
        actionToredezettseg->setText(QApplication::translate("MainWindowClass", "T\303\266redezetts\303\251gmentes\303\255t\303\251s", 0, QApplication::UnicodeUTF8));
        actionBlokkMuvelet->setText(QApplication::translate("MainWindowClass", "Blokk m\305\261veletek", 0, QApplication::UnicodeUTF8));
        leftPathLabel->setText(QApplication::translate("MainWindowClass", "<b>sdsdsadsad</b>", 0, QApplication::UnicodeUTF8));
        frissitBalButton->setText(QApplication::translate("MainWindowClass", "F", 0, QApplication::UnicodeUTF8));
        leftUpButton->setText(QApplication::translate("MainWindowClass", "^", 0, QApplication::UnicodeUTF8));
        rightUpButton->setText(QApplication::translate("MainWindowClass", "^", 0, QApplication::UnicodeUTF8));
        frissitJobbButton->setText(QApplication::translate("MainWindowClass", "F", 0, QApplication::UnicodeUTF8));
        rightPathLabel->setText(QApplication::translate("MainWindowClass", "TextLabel", 0, QApplication::UnicodeUTF8));
        infoButton->setText(QApplication::translate("MainWindowClass", "Inf\303\263", 0, QApplication::UnicodeUTF8));
        szerkeztButton->setText(QApplication::translate("MainWindowClass", "Szerkeszt", 0, QApplication::UnicodeUTF8));
        masolButton->setText(QApplication::translate("MainWindowClass", "M\303\241sol", 0, QApplication::UnicodeUTF8));
        athelyezButton->setText(QApplication::translate("MainWindowClass", "\303\201thelyez", 0, QApplication::UnicodeUTF8));
        atnevezButton->setText(QApplication::translate("MainWindowClass", "\303\201tnevez", 0, QApplication::UnicodeUTF8));
        torolButton->setText(QApplication::translate("MainWindowClass", "T\303\266r\303\266l", 0, QApplication::UnicodeUTF8));
        importButton->setText(QApplication::translate("MainWindowClass", "Import", 0, QApplication::UnicodeUTF8));
        exportButton->setText(QApplication::translate("MainWindowClass", "Export", 0, QApplication::UnicodeUTF8));
        ujKonyvtarButton->setText(QApplication::translate("MainWindowClass", "\303\232j k\303\266nyvt\303\241r", 0, QApplication::UnicodeUTF8));
        ujFileButton->setText(QApplication::translate("MainWindowClass", "\303\232j File", 0, QApplication::UnicodeUTF8));
        menuF_jl->setTitle(QApplication::translate("MainWindowClass", "F\303\241jl", 0, QApplication::UnicodeUTF8));
        menuN_zet->setTitle(QApplication::translate("MainWindowClass", "N\303\251zet", 0, QApplication::UnicodeUTF8));
        menuBe_ll_t_sok->setTitle(QApplication::translate("MainWindowClass", "Be\303\241ll\303\255t\303\241sok", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
