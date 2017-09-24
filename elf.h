#ifndef ELF_H
#define ELF_H

#include "character.h"
#include "enemy.h"
#include <string>

class Elf:public Enemy {
public:
    Elf();
    ~Elf();
    void attack(Player *p);// special ability of elf
};

#endif
