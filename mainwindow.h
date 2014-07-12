#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QStandardItemModel>
#include <string>
#include <map>
#include <QLabel>

#include "blockeventdialog.h"
#include "szakdolgozatfs.h"
using namespace std;

namespace Ui
{
    class MainWindowClass;
}

//class BlockEventDialog;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setupPanelModel(QStandardItemModel* model);
    void setupPanels();
    void setActivePanel(bool left);
    QString getSelectedPath(bool left);
    QString getSelectedFile(bool left);
    void loadPanel(bool left);
    void switchDirectory(bool left, unsigned int index);
    void gotoParent(bool left);
    void setStatusbarInfo();

    vector<string> leftRowPath;
    vector<string> rightRowPath;
    QLabel *statusSpaceLabel;
    QLabel *statusCacheLabel;

    vector<int> leftPanelWidths;
    vector<int> rightPanelWidths;

    void setDefaultActionStates();
    void setUsableActionStates();

    //beallitasok dialog alapjan
    bool bBlockCache;
    bool bInodeCache;
    unsigned int opBuffSize;
    unsigned int blockCacheSize;
    unsigned int inodeCacheSize;
    bool bEgyben;
    SpaceAlg spaceAlg;

    void initSettings();
    void applySettings();
/*
    BlockEventDialog *bed;
    void blockNotice(QString mit);
    void setupBlockEvents();
*/
private:
    Ui::MainWindowClass *ui;


    QStandardItemModel *leftModel;
    QStandardItemModel *rightModel;

    string leftPath;
    string rightPath;

    bool leftPanelActive;
    virtual void closeEvent(QCloseEvent *e);

 private slots:
    void on_actionBlokkMuvelet_triggered();
    void on_actionToredezettseg_triggered();
    void on_actionImageMasolat_triggered();
    void on_actionKonzisztencia_triggered();
    void on_actionCache_triggered();
    void on_actionImageMegnyit_triggered();
    void on_actionDiagram_triggered();
    void on_torolButton_clicked();
    void on_actionUnitTest_triggered();
    void on_actionKilep_triggered();
    void on_rightUpButton_clicked();
    void on_leftUpButton_clicked();
    void on_actionUjImage_triggered();
    void on_szerkeztButton_clicked();
    void on_rightTable_activated(QModelIndex index);
    void on_leftTable_activated(QModelIndex index);
    void on_rightTable_doubleClicked(QModelIndex index);
    void on_leftTable_doubleClicked(QModelIndex index);
    void on_frissitJobbButton_clicked();
    void on_ujKonyvtarButton_clicked();
    void on_frissitBalButton_clicked();
    void on_ujFileButton_clicked();
    void on_exportButton_clicked();
    void on_masolButton_clicked();
    void on_importButton_clicked();
    void on_actionFilerendszer_triggered();
    void on_rightTable_clicked(QModelIndex index);
    void on_leftTable_clicked(QModelIndex index);
    void on_infoButton_clicked();
    void on_atnevezButton_clicked();
    void on_athelyezButton_clicked();
    /*
    void infoButtonClicked();
    void atnevezButtonClicked();*/
};


/*
class CallbackWorkaroundImpl:public CallbackWorkaround{
    public:
        MainWindow *mw;
        void doCallback(BlockCallbackInfo i);
};
*/
#endif // MAINWINDOW_H
