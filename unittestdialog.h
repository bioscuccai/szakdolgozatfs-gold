#ifndef UNITTESTDIALOG_H
#define UNITTESTDIALOG_H

#include <QtGui/QDialog>

#include "fajlrendszersingleton.h"

#include "szakdolgozatfs_test.h"

namespace Ui {
    class UnitTestDialog;
}

class UnitTestDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(UnitTestDialog)
public:
    explicit UnitTestDialog(QWidget *parent = 0);
    virtual ~UnitTestDialog();

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::UnitTestDialog *m_ui;
    Test_Directory *td;
    Test_File *tf;

private slots:
    void on_csokkentButton_clicked();
    void on_kletrehozasButton_clicked();
    void on_kirasButton_clicked();
    void on_novelesButton_clicked();
    void on_torlesButton_clicked();
    void on_uresButton_clicked();
    void on_olvasasButton_clicked();
    void on_irasButton_clicked();
};

#endif // UNITTESTDIALOG_H
