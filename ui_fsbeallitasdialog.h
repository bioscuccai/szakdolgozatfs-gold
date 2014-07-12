/********************************************************************************
** Form generated from reading ui file 'fsbeallitasdialog.ui'
**
** Created: Wed May 15 23:48:28 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_FSBEALLITASDIALOG_H
#define UI_FSBEALLITASDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFormLayout>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QStackedWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FsBeallitasDialog
{
public:
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QWidget *layoutWidget1;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *blockCacheLine;
    QFrame *line;
    QLabel *label_3;
    QCheckBox *inodeCacheBox;
    QLabel *label_4;
    QLineEdit *inodeCacheLine;
    QCheckBox *blockCacheBox;
    QGroupBox *groupBox_2;
    QLabel *label_7;
    QComboBox *helyCombo;
    QWidget *page_2;
    QWidget *layoutWidget2;
    QFormLayout *formLayout_2;
    QLabel *label_5;
    QCheckBox *egybenBox;
    QLabel *label_6;
    QLineEdit *buffLine;
    QListWidget *listWidget;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *FsBeallitasDialog)
    {
        if (FsBeallitasDialog->objectName().isEmpty())
            FsBeallitasDialog->setObjectName(QString::fromUtf8("FsBeallitasDialog"));
        FsBeallitasDialog->resize(474, 446);
        stackedWidget = new QStackedWidget(FsBeallitasDialog);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(180, 10, 281, 391));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        layoutWidget = new QWidget(page);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 20, 271, 371));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(layoutWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        layoutWidget1 = new QWidget(groupBox);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 30, 251, 143));
        formLayout = new QFormLayout(layoutWidget1);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget1);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        blockCacheLine = new QLineEdit(layoutWidget1);
        blockCacheLine->setObjectName(QString::fromUtf8("blockCacheLine"));

        formLayout->setWidget(1, QFormLayout::FieldRole, blockCacheLine);

        line = new QFrame(layoutWidget1);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        formLayout->setWidget(2, QFormLayout::LabelRole, line);

        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_3);

        inodeCacheBox = new QCheckBox(layoutWidget1);
        inodeCacheBox->setObjectName(QString::fromUtf8("inodeCacheBox"));

        formLayout->setWidget(5, QFormLayout::FieldRole, inodeCacheBox);

        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_4);

        inodeCacheLine = new QLineEdit(layoutWidget1);
        inodeCacheLine->setObjectName(QString::fromUtf8("inodeCacheLine"));

        formLayout->setWidget(6, QFormLayout::FieldRole, inodeCacheLine);

        blockCacheBox = new QCheckBox(layoutWidget1);
        blockCacheBox->setObjectName(QString::fromUtf8("blockCacheBox"));
        blockCacheBox->setLayoutDirection(Qt::LeftToRight);

        formLayout->setWidget(0, QFormLayout::FieldRole, blockCacheBox);

        layoutWidget->raise();

        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(layoutWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 30, 91, 16));
        helyCombo = new QComboBox(groupBox_2);
        helyCombo->setObjectName(QString::fromUtf8("helyCombo"));
        helyCombo->setGeometry(QRect(100, 20, 151, 26));

        verticalLayout->addWidget(groupBox_2);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        layoutWidget2 = new QWidget(page_2);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(20, 20, 218, 48));
        formLayout_2 = new QFormLayout(layoutWidget2);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(layoutWidget2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_5);

        egybenBox = new QCheckBox(layoutWidget2);
        egybenBox->setObjectName(QString::fromUtf8("egybenBox"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, egybenBox);

        label_6 = new QLabel(layoutWidget2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_6);

        buffLine = new QLineEdit(layoutWidget2);
        buffLine->setObjectName(QString::fromUtf8("buffLine"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, buffLine);

        stackedWidget->addWidget(page_2);
        listWidget = new QListWidget(FsBeallitasDialog);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(0, 10, 171, 391));
        buttonBox = new QDialogButtonBox(FsBeallitasDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(280, 410, 164, 29));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(FsBeallitasDialog);
        QObject::connect(listWidget, SIGNAL(currentRowChanged(int)), stackedWidget, SLOT(setCurrentIndex(int)));

        stackedWidget->setCurrentIndex(0);
        listWidget->setCurrentRow(0);


        QMetaObject::connectSlotsByName(FsBeallitasDialog);
    } // setupUi

    void retranslateUi(QDialog *FsBeallitasDialog)
    {
        FsBeallitasDialog->setWindowTitle(QApplication::translate("FsBeallitasDialog", "Be\303\241ll\303\255t\303\241sok", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("FsBeallitasDialog", "Cache", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FsBeallitasDialog", "Blokk cache:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("FsBeallitasDialog", "M\303\251ret:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("FsBeallitasDialog", "Inode cache:", 0, QApplication::UnicodeUTF8));
        inodeCacheBox->setText(QString());
        label_4->setText(QApplication::translate("FsBeallitasDialog", "M\303\251ret:", 0, QApplication::UnicodeUTF8));
        blockCacheBox->setText(QString());
        groupBox_2->setTitle(QApplication::translate("FsBeallitasDialog", "F\303\241jlrendszer", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("FsBeallitasDialog", "Helyfoglal\303\241s:", 0, QApplication::UnicodeUTF8));
        helyCombo->clear();
        helyCombo->insertItems(0, QStringList()
         << QApplication::translate("FsBeallitasDialog", "Legjobb illeszked\303\251s", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FsBeallitasDialog", "Els\305\221 tal\303\241lat", 0, QApplication::UnicodeUTF8)
        );
        label_5->setText(QApplication::translate("FsBeallitasDialog", "Egybe m\303\241sol\303\241s:", 0, QApplication::UnicodeUTF8));
        egybenBox->setText(QString());
        label_6->setText(QApplication::translate("FsBeallitasDialog", "Buffer m\303\251ret:", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("FsBeallitasDialog", "F\303\241jlrendszer", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem1 = listWidget->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("FsBeallitasDialog", "F\303\241jlkezel\305\221", 0, QApplication::UnicodeUTF8));
        listWidget->setSortingEnabled(__sortingEnabled);

        Q_UNUSED(FsBeallitasDialog);
    } // retranslateUi

};

namespace Ui {
    class FsBeallitasDialog: public Ui_FsBeallitasDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FSBEALLITASDIALOG_H
