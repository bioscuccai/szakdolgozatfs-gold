#ifndef FSBEALLITASDIALOG_H
#define FSBEALLITASDIALOG_H

#include <QtGui/QDialog>

#include "mainwindow.h"

namespace Ui {
    class FsBeallitasDialog;
}

class FsBeallitasDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(FsBeallitasDialog)
public:
    explicit FsBeallitasDialog(QWidget *parent = 0);
    virtual ~FsBeallitasDialog();
    void init(MainWindow *mw);
    MainWindow *mw;

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::FsBeallitasDialog *m_ui;

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
};

#endif // FSBEALLITASDIALOG_H
