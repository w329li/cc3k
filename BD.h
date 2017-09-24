#ifndef BD_H
#define BD_H
#include <string>
#include "potion.h"


class BD: public Potion {

    public:
    BD(); // default ctor
    ~BD(); // dtor
    virtual void notify(Player *p) override;// record the interaction message
    virtual bool used() override; // find out whether used the potion
    virtual void use(Player *p) override; // use the potion
};







#endif
