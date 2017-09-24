#ifndef HUMAN_H
#define HUMAN_H

#include "character.h"
#include "enemy.h"
#include <string>

class Human: public Enemy{
public:
    Human(); // default ctor
    ~Human(); // dtor
    // the one below return the amount of gold dropped  by human
    int dropgold() override;
};

#endif
