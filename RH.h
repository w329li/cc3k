#ifndef RH_H
#define RH_H
#include <string>
#include "potion.h"

class RH: public Potion {
    public:
    RH();
    ~RH();
    virtual void notify(Player *pc) override;// record the interaction message
    virtual bool used() override; // find out whether used the potion
    virtual void use(Player *p) override;// use the potion
};



#endif
