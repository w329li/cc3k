#include <iostream>
#include <string>
#include "goblin.h"
#include <cmath>
#include "enemy.h"

using namespace std;

Goblin:: Goblin()
    :Player(110,15,20,"Goblin") {}



void Goblin:: defend(Enemy &o) {
    int n = getdamage(o);
    stringstream ss;
    if(o.getrace() == "Orcs") {
        n = trunc(n * 1.5);
        sethp((-1) * n);
    } else {
        sethp((-1) * n);
    }
    if(Character::gethp() <= 0) {
        Character::dead();
    } else {
        ss << n;
        string damage  = ss.str();
        string q = o.Character::getsymbol();
        string c = q + " deals " + damage + " damage to PC.";
        addaction(c);
    }
    // extra injury from orcs
}

Goblin::~Goblin() {}


