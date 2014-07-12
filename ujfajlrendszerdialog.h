#ifndef UJFAJLRENDSZERDIALOG_H
#define UJFAJLRENDSZERDIALOG_H

#include <QtGui/QDialog>
#include "mainwindow.h"

namespace Ui {
    class UjFajlrendszerDialog;
}

class UjFajlrendszerDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(UjFajlrendszerDialog)
public:
    explicit UjFajlrendszerDialog(QWidget *parent = 0);
    virtual ~UjFajlrendszerDialog();
    MainWindow *mw;
protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::UjFajlrendszerDialog *m_ui;

private slots:
    void on_buttonBox_accepted();
    void on_tallozButton_clicked();
};

#endif // UJFAJLRENDSZERDIALOG_H
