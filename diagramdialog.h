#ifndef DIAGRAMDIALOG_H
#define DIAGRAMDIALOG_H

#include <QtGui/QDialog>
#include <QTreeView>
#include <QTreeWidgetItem>
#include <map>

using namespace std;

namespace Ui {
    class DiagramDialog;
}

class DiagramDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(DiagramDialog)
public:
    explicit DiagramDialog(QWidget *parent = 0);
    virtual ~DiagramDialog();
    map<unsigned long, QTreeWidgetItem*> dirs;
    map<QTreeWidgetItem*, unsigned long> wPaths;
    void init();

    bool prevBlockCache;
    bool prevInodeCache;
protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::DiagramDialog *m_ui;

private slots:
    void on_dirTree_itemActivated(QTreeWidgetItem* item, int column);
    void on_dirTree_clicked(QModelIndex index);
};

#endif // DIAGRAMDIALOG_H
