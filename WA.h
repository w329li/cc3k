#ifndef WA_H
#define WA_H
#include <string>
#include "potion.h"

class WA: public Potion {

    public:
    WA();
    ~WA();
    virtual void notify(Player *p) override;// record the interaction message
    virtual bool used() override; // find out whether used the potion
    virtual void use(Player *p) override; // use potion
};




 #endif
