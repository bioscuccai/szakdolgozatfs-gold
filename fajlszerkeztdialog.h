#ifndef FAJLSZERKEZTDIALOG_H
#define FAJLSZERKEZTDIALOG_H

#include "mainwindow.h"

#include <QtGui/QDialog>

namespace Ui {
    class FajlSzerkeztDialog;
}

class FajlSzerkeztDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(FajlSzerkeztDialog)
public:
    explicit FajlSzerkeztDialog(QWidget *parent = 0);
    virtual ~FajlSzerkeztDialog();
    void init(QString utvonal_);
    MainWindow *mw;

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::FajlSzerkeztDialog *m_ui;
    QString utvonal;

private slots:
    void on_buttonBox_accepted();
};

#endif // FAJLSZERKEZTDIALOG_H
