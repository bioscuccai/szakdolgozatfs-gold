enum SzakdolgozatFs_JournalType{J_INCREASE_FILE=0, J_UPDATE_INODE};
class SzakdolgozatFs_JournalEntry{
    public:
        SzakdolgozatFs_JournalType type;
        bool committed;
        unsigned long size;
};

class SzakdolgozatFs_JornalInode:SzakdolgozatFs_JournalEntry{
    public:
        SzakdolgozatFs_Inode newNode;
}
