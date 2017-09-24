#ifndef DHOARD_H
#define DHOARD_H
#include <string>
#include "gold.h"
#include "dragon.h"
#include "player.h"


class Dhoard: public Gold {
    Dragon * d; // record the dragon that protect the gold
    public:
    Dhoard(); // default ctor
    Dhoard(Dragon *g); // default ctor with a dragon protector
    ~Dhoard(); // dtor
    void adddragon(Dragon *dra); // initialize a dragon to protect the gold
    bool havedragon(); // find out whether there is dragon around gold
    virtual void notify(Player *pc) override; // record the interaction message
    virtual void use(Player *pc) override; // player use the gold
};









#endif
