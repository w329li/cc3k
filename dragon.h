#ifndef DRAGON_H
#define DRAGON_H

#include "character.h"
#include "enemy.h"

class Dragon : public Enemy{
public:
    Dragon();
    ~Dragon();
    virtual int dropgold() override; // return the amount of gold when dragon dies
};

#endif
