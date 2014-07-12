#ifndef SCANDISKDIALOG_H
#define SCANDISKDIALOG_H

#include <QtGui/QDialog>
#include <QListWidgetItem>

#include <map>
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

#include "blocktype.h"
#include "szakdolgozatfs.h"

namespace Ui {
    class ScandiskDialog;
}

enum ProblemType{FSP_SHARED_BLOCK, FSP_UNUSED_BLOCK, FSP_NOT_ALLOCATED_DATA, FSP_NOT_ALLOCATED_INODE, FSP_NOT_ALLOCATED_BLOCKLIST,
             FSP_INVALID_LOC_INODE, FSP_INVALID_LOC_BLOCKLIST, FSP_INVALID_LOC_DATA};

class FsProblem{
    public:
        ProblemType problem;
        vector<string> paths;
        vector<unsigned long> blocks;
        bool solved;
        blockAddr dir;
        blockAddr node;
        FsProblem(ProblemType pt, vector<string> ps, vector<unsigned long> bl);
        FsProblem(ProblemType pt, vector<string> ps, vector<unsigned long> bl, blockAddr d, blockAddr n);
};

class ScandiskDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(ScandiskDialog)
public:
    explicit ScandiskDialog(QWidget *parent = 0);
    virtual ~ScandiskDialog();

    void addProblem(ProblemType pt, vector<string> ps, vector<unsigned long> bl);
    void addProblem(ProblemType pt, vector<string> ps, vector<unsigned long> bl, blockAddr dir, blockAddr node);


    vector<FsProblem*> problems;

    void fillMap();
    void checkFile(string p, blockAddr dir, blockAddr node);
    void checkForUnusedBlocks();
    void fillProblemList();

    map<unsigned long, WidgetSquare*> blockMap;

    void setBlocks(vector<blockAddr> bl, bool to);

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::ScandiskDialog *m_ui;

private slots:
    void on_inditButton_clicked();
    void on_problemList_itemActivated(QListWidgetItem* item);
};

#endif // SCANDISKDIALOG_H
