#ifndef FILELETREHOZDIALOG_H
#define FILELETREHOZDIALOG_H

#include "mainwindow.h"

#include <QtGui/QDialog>

namespace Ui {
    class FileLetrehozDialog;
}

class FileLetrehozDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(FileLetrehozDialog)
public:
    explicit FileLetrehozDialog(QWidget *parent = 0);
    virtual ~FileLetrehozDialog();
    void init(QString utvonal_);
    MainWindow *mw;

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::FileLetrehozDialog *m_ui;
    QString utvonal;

private slots:
    void on_buttonBox_accepted();
};

#endif // FILELETREHOZDIALOG_H
