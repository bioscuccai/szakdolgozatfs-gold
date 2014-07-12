/********************************************************************************
** Form generated from reading ui file 'unittestdialog.ui'
**
** Created: Fri Apr 26 16:07:52 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_UNITTESTDIALOG_H
#define UI_UNITTESTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UnitTestDialog
{
public:
    QGroupBox *groupBox;
    QWidget *widget;
    QGridLayout *gridLayout;
    QCheckBox *irasBox;
    QPushButton *irasButton;
    QCheckBox *olvasasBox;
    QPushButton *olvasasButton;
    QCheckBox *uresBox;
    QPushButton *uresButton;
    QCheckBox *torlesBox;
    QPushButton *torlesButton;
    QCheckBox *novelesBox;
    QPushButton *novelesButton;
    QCheckBox *csokkentBox;
    QPushButton *csokkentButton;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_2;
    QCheckBox *kirasBox;
    QPushButton *kirasButton;
    QCheckBox *kletrehozBox;
    QPushButton *kletrehozasButton;

    void setupUi(QDialog *UnitTestDialog)
    {
        if (UnitTestDialog->objectName().isEmpty())
            UnitTestDialog->setObjectName(QString::fromUtf8("UnitTestDialog"));
        UnitTestDialog->resize(396, 423);
        groupBox = new QGroupBox(UnitTestDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(0, 30, 371, 231));
        widget = new QWidget(groupBox);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(20, 21, 331, 206));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        irasBox = new QCheckBox(widget);
        irasBox->setObjectName(QString::fromUtf8("irasBox"));

        gridLayout->addWidget(irasBox, 0, 0, 1, 1);

        irasButton = new QPushButton(widget);
        irasButton->setObjectName(QString::fromUtf8("irasButton"));
        irasButton->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(irasButton, 0, 1, 1, 1);

        olvasasBox = new QCheckBox(widget);
        olvasasBox->setObjectName(QString::fromUtf8("olvasasBox"));

        gridLayout->addWidget(olvasasBox, 1, 0, 1, 1);

        olvasasButton = new QPushButton(widget);
        olvasasButton->setObjectName(QString::fromUtf8("olvasasButton"));
        olvasasButton->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(olvasasButton, 1, 1, 1, 1);

        uresBox = new QCheckBox(widget);
        uresBox->setObjectName(QString::fromUtf8("uresBox"));

        gridLayout->addWidget(uresBox, 2, 0, 1, 1);

        uresButton = new QPushButton(widget);
        uresButton->setObjectName(QString::fromUtf8("uresButton"));
        uresButton->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(uresButton, 2, 1, 1, 1);

        torlesBox = new QCheckBox(widget);
        torlesBox->setObjectName(QString::fromUtf8("torlesBox"));
        torlesBox->setEnabled(true);

        gridLayout->addWidget(torlesBox, 3, 0, 1, 1);

        torlesButton = new QPushButton(widget);
        torlesButton->setObjectName(QString::fromUtf8("torlesButton"));
        torlesButton->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(torlesButton, 3, 1, 1, 1);

        novelesBox = new QCheckBox(widget);
        novelesBox->setObjectName(QString::fromUtf8("novelesBox"));

        gridLayout->addWidget(novelesBox, 4, 0, 1, 1);

        novelesButton = new QPushButton(widget);
        novelesButton->setObjectName(QString::fromUtf8("novelesButton"));
        novelesButton->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(novelesButton, 4, 1, 1, 1);

        csokkentBox = new QCheckBox(widget);
        csokkentBox->setObjectName(QString::fromUtf8("csokkentBox"));

        gridLayout->addWidget(csokkentBox, 5, 0, 1, 1);

        csokkentButton = new QPushButton(widget);
        csokkentButton->setObjectName(QString::fromUtf8("csokkentButton"));

        gridLayout->addWidget(csokkentButton, 5, 1, 1, 1);

        groupBox_2 = new QGroupBox(UnitTestDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 270, 331, 101));
        layoutWidget = new QWidget(groupBox_2);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 20, 311, 66));
        gridLayout_2 = new QGridLayout(layoutWidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        kirasBox = new QCheckBox(layoutWidget);
        kirasBox->setObjectName(QString::fromUtf8("kirasBox"));

        gridLayout_2->addWidget(kirasBox, 0, 0, 1, 1);

        kirasButton = new QPushButton(layoutWidget);
        kirasButton->setObjectName(QString::fromUtf8("kirasButton"));
        kirasButton->setMaximumSize(QSize(100, 16777215));

        gridLayout_2->addWidget(kirasButton, 0, 1, 1, 1);

        kletrehozBox = new QCheckBox(layoutWidget);
        kletrehozBox->setObjectName(QString::fromUtf8("kletrehozBox"));

        gridLayout_2->addWidget(kletrehozBox, 1, 0, 1, 1);

        kletrehozasButton = new QPushButton(layoutWidget);
        kletrehozasButton->setObjectName(QString::fromUtf8("kletrehozasButton"));
        kletrehozasButton->setMaximumSize(QSize(100, 16777215));

        gridLayout_2->addWidget(kletrehozasButton, 1, 1, 1, 1);


        retranslateUi(UnitTestDialog);

        QMetaObject::connectSlotsByName(UnitTestDialog);
    } // setupUi

    void retranslateUi(QDialog *UnitTestDialog)
    {
        UnitTestDialog->setWindowTitle(QApplication::translate("UnitTestDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("UnitTestDialog", "F\303\241jl", 0, QApplication::UnicodeUTF8));
        irasBox->setText(QApplication::translate("UnitTestDialog", "\303\215r\303\241s", 0, QApplication::UnicodeUTF8));
        irasButton->setText(QApplication::translate("UnitTestDialog", "Teszt", 0, QApplication::UnicodeUTF8));
        olvasasBox->setText(QApplication::translate("UnitTestDialog", "Olvas\303\241s", 0, QApplication::UnicodeUTF8));
        olvasasButton->setText(QApplication::translate("UnitTestDialog", "Teszt", 0, QApplication::UnicodeUTF8));
        uresBox->setText(QApplication::translate("UnitTestDialog", "\303\234res l\303\251trehoz\303\241s", 0, QApplication::UnicodeUTF8));
        uresButton->setText(QApplication::translate("UnitTestDialog", "Teszt", 0, QApplication::UnicodeUTF8));
        torlesBox->setText(QApplication::translate("UnitTestDialog", "T\303\266rl\303\251s", 0, QApplication::UnicodeUTF8));
        torlesButton->setText(QApplication::translate("UnitTestDialog", "Teszt", 0, QApplication::UnicodeUTF8));
        novelesBox->setText(QApplication::translate("UnitTestDialog", "N\303\266vel\303\251s", 0, QApplication::UnicodeUTF8));
        novelesButton->setText(QApplication::translate("UnitTestDialog", "Teszt", 0, QApplication::UnicodeUTF8));
        csokkentBox->setText(QApplication::translate("UnitTestDialog", "Cs\303\266kkent\303\251s", 0, QApplication::UnicodeUTF8));
        csokkentButton->setText(QApplication::translate("UnitTestDialog", "Teszt", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("UnitTestDialog", "K\303\266nyvt\303\241r", 0, QApplication::UnicodeUTF8));
        kirasBox->setText(QApplication::translate("UnitTestDialog", "\303\215r\303\241s", 0, QApplication::UnicodeUTF8));
        kirasButton->setText(QApplication::translate("UnitTestDialog", "Teszt", 0, QApplication::UnicodeUTF8));
        kletrehozBox->setText(QApplication::translate("UnitTestDialog", "L\303\251trehoz\303\241s", 0, QApplication::UnicodeUTF8));
        kletrehozasButton->setText(QApplication::translate("UnitTestDialog", "Teszt", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(UnitTestDialog);
    } // retranslateUi

};

namespace Ui {
    class UnitTestDialog: public Ui_UnitTestDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UNITTESTDIALOG_H
