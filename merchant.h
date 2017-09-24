#ifndef MERCHANT_H
#define MERCHANT_H

#include "character.h"
#include "enemy.h"
#include <string>

class Merchant: public Enemy{
    static bool hostile;
public:
    Merchant();  // default ctor
    ~Merchant(); // dtor
    // the one below return the amount of gold that merchant drops when he dies
    int dropgold() override;
    static bool ifhate(); // find out whether merchant is hostile
    static void tobefriend(); // change the hostility of merchant
    virtual void defend(Player &p) override; // defend process during a combat
    virtual void attack(Player *p) override; // attack process during a combat
};

#endif
