#include "fajlrendszersingleton.h"

SzakdolgozatFs* FajlrendszerSingleton::instance=NULL;

SzakdolgozatFs* FajlrendszerSingleton::getInstance(){
    if(FajlrendszerSingleton::instance==NULL) FajlrendszerSingleton::instance=new SzakdolgozatFs();
    return FajlrendszerSingleton::instance;
}
void FajlrendszerSingleton::reset(){
    if(instance!=NULL){
        delete instance;
        instance=NULL;
    }
}
