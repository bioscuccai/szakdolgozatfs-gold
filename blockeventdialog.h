#ifndef BLOCKEVENTDIALOG_H
#define BLOCKEVENTDIALOG_H

#include <QtGui/QDialog>
#include <QStandardItemModel>

#include "szakdolgozatfs.h"
#include "mainwindow.h"

namespace Ui {
    class BlockEventDialog;
}

class MainWindow;
class BlockEventDialog : public QDialog,public BlockCallbackHandler {
    Q_OBJECT
    Q_DISABLE_COPY(BlockEventDialog)
public:
    explicit BlockEventDialog(QWidget *parent = 0);
    virtual ~BlockEventDialog();

    void blockEventHandler(BlockCallbackInfo* i);
    void init(MainWindow *mw_);
    void getNotice(QString mit, bool szf=true);

    virtual void doCallback(BlockCallbackInfo* i);
    virtual void doNotice(string msg);

    MainWindow *mw;
    QStandardItemModel *tableModel;

    void setupTable();
protected:
    virtual void changeEvent(QEvent *e);
    virtual void closeEvent(QCloseEvent *e);

private:
    Ui::BlockEventDialog *m_ui;

private slots:
    void on_commButton_clicked();
    void on_clearButton_clicked();
    void on_BlockEventDialog_rejected();
    void on_BlockEventDialog_destroyed();
};

#endif // BLOCKEVENTDIALOG_H
