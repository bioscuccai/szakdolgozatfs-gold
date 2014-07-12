#ifndef MASOLDIALOG_H
#define MASOLDIALOG_H

#include "mainwindow.h"

#include <QtGui/QDialog>
#include <string>
using namespace std;

namespace Ui {
    class MasolDialog;
}

class MasolDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(MasolDialog)
public:
    explicit MasolDialog(QWidget *parent = 0);
    virtual ~MasolDialog();

    void init(QString eFajl, QString uUtvonal);
    MainWindow *mw;


protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::MasolDialog *m_ui;

    QString eredetiFajl;
    QString ujUtvonal;
    QString ujNev;

private slots:
    void on_buttonBox_accepted();
};

#endif // MASOLDIALOG_H
