#ifndef BA_H
#define BA_H
#include <string>
#include "potion.h"


class BA: public Potion {

    public:
    BA(); // default ctor
    ~BA(); // dtor
    virtual void notify(Player *p) override;// record the interaction message
    virtual bool used() override; // find out whether used the potion
    virtual void use(Player *p) override; // use the potion
};




 #endif
