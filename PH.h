#ifndef PH_H
#define PH_H
#include <string>
#include "potion.h"

class PH: public Potion {

    public:
    PH();
    ~PH();
    virtual void notify(Player *p) override;// record the interaction message
    virtual bool used() override; // find out whether used the potion
    virtual void use(Player *p) override; // use the potion
};




 #endif
