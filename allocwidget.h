#ifndef ALLOCWIDGET_H
#define ALLOCWIDGET_H

#include "fajlrendszersingleton.h"

#include <QWidget>
#include <QPainter>
#include <map>

#include "blocktype.h"

using namespace std;



class AllocWidget: public QWidget{
    Q_OBJECT
    public:
        map<unsigned long int, WidgetSquare*> squareMap;
        AllocWidget(QWidget *parent=0);
        void fillMap();
        void checkFile(string p);
        QColor blockColor(WidgetSquareType t);
        unsigned long highlightFile;
        vector<unsigned int> cacheMark;
        vector<unsigned int> inodeCacheMark;
        unsigned long nBlocks;

        bool prevBlockCache;
        bool prevInodeCache;
    protected:
        void paintEvent(QPaintEvent *e);
};

#endif // ALLOCWIDGET_H
