#ifndef CACHEDIALOG_H
#define CACHEDIALOG_H

#include <QtGui/QDialog>
#include <map>

using namespace std;

namespace Ui {
    class CacheDialog;
}

class CacheDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(CacheDialog)
public:
    explicit CacheDialog(QWidget *parent = 0);
    virtual ~CacheDialog();

    map<unsigned int, string> nodeOwner;
    void fillNodeOwners();
    void checkFile(string p);
    QStringList inodeList;
    void createInodeModel();

    QStringList blockList;
    void createBlockModel();
    unsigned int *blockCacheCopy;
    unsigned int blockCacheSize;
    unsigned int *inodeCacheCopy;
    unsigned int inodeCacheSize;

    bool prevBlockCache;
    bool prevInodeCache;

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::CacheDialog *m_ui;
};

#endif // CACHEDIALOG_H
