#ifndef BLOCKTYPE_H
#define BLOCKTYPE_H

enum WidgetSquareType{WST_SUPER, WST_ALLOC, WST_INODE, WST_BL, WST_DATA, WST_UK};

class WidgetSquare{
    public:
        WidgetSquare(WidgetSquareType t, unsigned long f, bool u);
        WidgetSquareType type;
        unsigned long file;
        bool used;
};

#endif // BLOCKTYPE_H
