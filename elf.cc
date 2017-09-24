#include "elf.h"
#include "player.h"
#include <cmath>
using namespace std;

Elf::Elf():Enemy(140,30,10,"Elf","E"){}

Elf::~Elf(){};

void Elf::attack(Player *p) {
    if(!ifturnover()) {
        changeturn();
        string race = p->getrace();
        if(race == "Drow") {
            int success;
            success = rand() % 2;
            if (success==1){
                p->defend(*this);
            } else {
                string c = getsymbol() + "'s attack missed. ";
                p->addaction(c);
            }
        } else {
            int success;
            success = rand() % 2;
            if (success==1){
                p->defend(*this);
            } else {
                string c = getsymbol() + "'s attack missed. ";
                p->addaction(c);
            }
            success = rand() % 2;
            if (success==1){
                p->defend(*this);
            } else {
                string c = getsymbol() + "'s attack missed. ";
                p->addaction(c);
            }

        }
    }
}
