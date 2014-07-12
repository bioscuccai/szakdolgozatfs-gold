#ifndef FAJLRENDSZERSINGLETON_H
#define FAJLRENDSZERSINGLETON_H

#include "szakdolgozatfs.h"

class FajlrendszerSingleton{
    public:
        static SzakdolgozatFs* getInstance();
        static SzakdolgozatFs* instance;
        static void reset();
};


#endif // FAJLRENDSZERSINGLETON_H
