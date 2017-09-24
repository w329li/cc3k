#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include "character.h"
#include "player.h"
#include "enemy.h"
#include "human.h"
#include "halfling.h"
#include "merchant.h"
#include "elf.h"
#include "dwarf.h"
#include "dragon.h"
#include "orc.h"


using namespace std;

Player:: Player(int hp,int atk,int def,string race)
  :Character(hp,atk,def,race,"@"),gold{0},a{""}{
  basicatk = atk;
  basicdef = def;
}

int Player:: getgold() {
return gold;
}

void Player:: setgold(int dis) {
gold += dis;
if(gold < 0) gold = 0;
stringstream ss;
ss << dis;
string g  = ss.str();
string c = "PC gets " + g + " more gold.";
  addaction(c);
}

void Player::silentgold(int dis) {
    gold += dis;
    if(gold < 0) gold = 0;
}

void Player:: attack(Enemy* e) {
    strike(*e);
}

int Player:: getdamage(Enemy &e) {
  int damage = ceil((100 / (double)(100 + getdef())) * e.getatk());
  return damage;
}

void Player:: strike(Enemy &e) {
  string race = e.getrace();
  if(race == "Halfling") {
    int success = rand() % 2;
    if(success) {
        e.defend(*this);
        if(getrace() == "Goblin" && e.ifdead()) {
            silentgold(5);
            addaction("PC steals 5 gold from slained enemy. ");
        }
    } else {
        addaction("PC missed the attack. ");
    }
  } else {
      e.defend(*this);
      if(getrace() == "Goblin" && e.ifdead()) {
          silentgold(5);
          addaction("PC steals 5 gold from slained enemy. ");
      }
  }
}


void Player::pickgold(int num) {
  setgold(num);
}



void Player:: defend(Enemy &h) {
    int n = getdamage(h);
  stringstream ss;
  ss << n;
  string damage  = ss.str();
  sethp((-1) * n);
  if(Character::gethp() <= 0) {
    Character::dead();
  } else {
    string q = h.Character::getsymbol();
    string c = q + " deals " + damage + " damage to PC. ";
    addaction(c);
  }
}

void Player::tobasic() {
  setatk(basicatk-getatk());
  setdef(basicdef-getdef());
}

void Player::notify(Player *pc) {
}

string Player::getsymbol() {
  return Character::getsymbol();
}

Player::~Player() {}

void Player::addaction(string s) {
    a += s;
}

void Player::display() {
    cout << a;
}

string Player::gets() {
    return a;
}

void Player::clear() {
    a = "";
}

