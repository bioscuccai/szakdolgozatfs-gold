#ifndef ATHELYEZDIALOG_H
#define ATHELYEZDIALOG_H

#include "mainwindow.h"

#include <QtGui/QDialog>

namespace Ui {
    class AthelyezDialog;
}

class AthelyezDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(AthelyezDialog)
public:
    explicit AthelyezDialog(QWidget *parent = 0);
    virtual ~AthelyezDialog();
    void init(QString ezt_, QString ide_);
    MainWindow *mw;

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::AthelyezDialog *m_ui;
    QString ezt;
    QString ide;

private slots:
    void on_buttonBox_accepted();
};

#endif // ATHELYEZDIALOG_H
