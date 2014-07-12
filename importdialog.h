#ifndef IMPORTDIALOG_H
#define IMPORTDIALOG_H

#include "mainwindow.h"

#include <QtGui/QDialog>
#include <string>
using namespace std;

namespace Ui {
    class ImportDialog;
}

class ImportDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(ImportDialog)
public:
    explicit ImportDialog(QWidget *parent = 0);
    virtual ~ImportDialog();
    void init(string utvonal_);
    MainWindow *mw;

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::ImportDialog *m_ui;
    QString utvonal;
    QString kulsoFajl;
    QString belsoFajl;

private slots:
    void on_buttonBox_accepted();
    void on_pushButton_clicked();
};

#endif // IMPORTDIALOG_H
