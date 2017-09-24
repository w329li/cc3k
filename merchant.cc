#include "merchant.h"
#include "enemy.h"
#include "player.h"
using namespace std;

bool Merchant::hostile = false;

Merchant::Merchant():Enemy(30,70,5,"Merchant","M"){}

Merchant::~Merchant(){}

int Merchant::dropgold(){
    return 4;
}

bool Merchant::ifhate() {
  return hostile;
}

void Merchant::tobefriend() {
  hostile = false;
}

void Merchant::attack(Player *p){
    if(!ifturnover()) {
        if(Merchant::hostile) {
    changeturn();
    int success;
    success = rand() % 2;
    if (success==1){
      p->defend(*this);
    } else {
      string c = "M's attack missed. ";
      p->addaction(c);
    }
    }
    } else {
        return;
    }
}

void Merchant::defend(Player &p) {
  hostile = true;
  int n = getdamage(p);
  stringstream ss;
  ss << n;
  string damage  = ss.str();
  sethp((-1) * n);
  if(Character::gethp() <= 0) {
    Character::dead();
  } else {
    string symbol= Character::getsymbol();
      int hp = gethp();
      stringstream dd;
      dd << hp;
      string h;
      dd >> h;
    string c = "PC deals " + damage + " damage to " + symbol + "("+ h + " HP).";
      p.addaction(c);
  }
}

