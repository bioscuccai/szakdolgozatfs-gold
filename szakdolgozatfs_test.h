#include "szakdolgozatfs.h"

class SzakdolgozatFs_Test{
    public:
        SzakdolgozatFs* fs;
        SzakdolgozatFs_Test(SzakdolgozatFs* fs_);
};
class Test_Directory: SzakdolgozatFs_Test{
    public:
        Test_Directory(SzakdolgozatFs* fs);
        bool testDirectoryCreation(string loc);
        bool testDirectoryNewFile(string loc);
};

class Test_File: SzakdolgozatFs_Test{
    public:
        Test_File(SzakdolgozatFs* fs);
        bool testEmptyFileCreation(string loc);
        bool testIncreaseFile(string loc);
        bool testDecreaseFile(string loc);
        bool testFread(string loc);
        bool testFwrite(string loc);
        bool testDelete(string loc);

        bool testFread_size(string loc, long fileSize);
        bool testFwrite_size(string loc, long fileSize);

        bool testRandom();
};
