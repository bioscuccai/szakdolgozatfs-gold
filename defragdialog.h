#ifndef DEFRAGDIALOG_H
#define DEFRAGDIALOG_H

#include <QtGui/QDialog>

#include "szakdolgozatfs.h"
#include "fajlrendszersingleton.h"

namespace Ui {
    class DefragDialog;
}

class DefragDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(DefragDialog)
public:
    explicit DefragDialog(QWidget *parent = 0);
    virtual ~DefragDialog();
    void doDefrag();
    string defFile;
    SzakdolgozatFs *copyFs;
    QString saveHere;

protected:
    virtual void changeEvent(QEvent *e);
    virtual void closeEvent(QCloseEvent *e);

private:
    Ui::DefragDialog *m_ui;

private slots:
    void on_tallozButton_clicked();
    void on_inditButton_clicked();
};

#endif // DEFRAGDIALOG_H
