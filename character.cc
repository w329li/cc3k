#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "character.h"

using namespace std;

Character::Character(int hp, int atk, int def,string race,string symbol)
  :hp{hp},atk{atk},def{def},isdead{false},race{race},symbol{symbol},maxhp{hp}{}

int Character:: gethp() {
    return hp;
}

void Character:: sethp(int dis) {
    hp = hp + dis;
    if(hp > maxhp) {
      hp = maxhp;
    }
    if(hp < 0) {
        hp = 0;
    }
}

int Character:: getatk() {
    return atk;
}

void Character:: setatk(int dis) {
    atk += dis;
    if(atk < 0 ) atk = 0;
}

int Character:: getdef() {
    return def;
}

void Character:: setdef(int dis) {
    def += dis;
    if(def < 0) def = 0;
}


string Character:: getrace() {
    return race;
}

string Character::getsymbol(){
    return this->symbol;
}

void Character::setpos(int row, int col) {
  r = row;
  c = col;
}

Character:: ~Character() {}


void Character:: dead() {
  isdead = true;
}

bool Character::ifdead() {
  return isdead;
}

Info Character::getInfo() {
  Info info = {r,c};
  return info;
}


