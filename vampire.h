#ifndef VAMPIRE_H
#define VAMPIRE_H
#include "player.h"

class Enemy;


class Vampire : public Player{
    public:
    Vampire(); // default ctor
    virtual void strike(Enemy &e) override;// strike process during combat
    virtual void sethp(int dis) override;// reset the value of hp
};
#endif
