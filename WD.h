#ifndef WD_H
#define WD_H
#include <string>
#include "potion.h"


class WD: public Potion {

    public:
    WD();
    ~WD();
    virtual void notify(Player *p) override; // record the interaction message
    virtual bool used() override; // find out whether used the potion
    virtual void use(Player *p) override; // use potion
};




 #endif
