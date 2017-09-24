#ifndef HALFLING_H
#define HALFLING_H

#include "character.h"
#include "enemy.h"

class Halfling : public Enemy{
public:
    Halfling(); // default ctor
    ~Halfling(); // dtor
};

#endif
