#ifndef KONYVTARLETREHOZDIALOG_H
#define KONYVTARLETREHOZDIALOG_H

#include "mainwindow.h"

#include <QtGui/QDialog>

namespace Ui {
    class KonyvtarLetrehozDialog;
}

class KonyvtarLetrehozDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(KonyvtarLetrehozDialog)
public:
    explicit KonyvtarLetrehozDialog(QWidget *parent = 0);
    virtual ~KonyvtarLetrehozDialog();
    void init(QString utvonal_);
    MainWindow *mw;

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::KonyvtarLetrehozDialog *m_ui;
    QString utvonal;

private slots:
    void on_buttonBox_accepted();
};

#endif // KONYVTARLETREHOZDIALOG_H
