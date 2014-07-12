#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QtGui/QDialog>
#include <string>

using namespace std;
namespace Ui {
    class infoDialog;
}

class infoDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(infoDialog)
public:
    explicit infoDialog(QWidget *parent = 0);
    virtual ~infoDialog();

    void init(QString utvonal_);
    QString utvonal;

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::infoDialog *m_ui;
};

#endif // INFODIALOG_H
