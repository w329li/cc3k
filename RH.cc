#include "RH.h"
#include "potion.h"
#include "player.h"
#include <string>

using namespace std;

RH::RH():Potion(){}
RH::~RH(){}

bool RH:: used() {
  return Potion::ifdrink("RH");
}


void RH:: use(Player *p) {
    Potion::havedrink("RH");
    if (p->getrace()=="Drow"){
    p->sethp(15);
  }else {
    p->sethp(10);
  }
    p->addaction("PC uses RH. ");
}


void RH::notify(Player *p) {
  if(used()) {
      p->addaction("PC find RH. ");
      } else {
          p->addaction("PC find unknown potion. ");
  }
}

