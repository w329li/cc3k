#include <iostream>
#include <string>
#include "vampire.h"
#include "enemy.h"
using namespace std;

Vampire::Vampire()
  :Player(50,25,25,"Vampire") {}

void Vampire::sethp(int dis) {
  hp += dis;
}

void Vampire:: strike(Enemy &e) {
  string race = e.getrace();
  int success = 1;
  if(race == "Halfling") {
    success = rand() % 2;
    if(success) e.defend(*this);
  } else {
      e.defend(*this);
  }
  if (e.getrace()=="Dwarf"){
    sethp(-5);
  }else {
    sethp(5);
  }
}
