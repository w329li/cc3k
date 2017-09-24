#ifndef GOBLIN_H
#define GOBLIN_H
#include <iostream>
#include <string>
#include "player.h"

class Goblin : public Player {
    std::string race;
    public:
    Goblin(); // default ctor
    virtual void defend(Enemy &o) override;// defend process during combat
    ~Goblin(); // dtor
};



#endif


