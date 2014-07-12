#ifndef ATNEVEZDIALOG_H
#define ATNEVEZDIALOG_H

#include "mainwindow.h"

#include <QtGui/QDialog>

namespace Ui {
    class AtnevezDialog;
}

class AtnevezDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(AtnevezDialog)
public:
    explicit AtnevezDialog(QWidget *parent = 0);
    virtual ~AtnevezDialog();
    void init(QString regiUtvonal_);
    MainWindow *mw;
protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::AtnevezDialog *m_ui;
    QString regiUtvonal;

private slots:
    void on_buttonBox_accepted();
};

#endif // ATNEVEZDIALOG_H
