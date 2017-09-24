#include "PH.h"
#include "player.h"
#include <string>

using namespace std;


PH::PH(): Potion(){}
PH::~PH(){}

bool PH :: used() {
    return Potion::ifdrink("PH");
}



void PH:: use(Player *p) {
  Potion::havedrink("PH");
  if (p->getrace()=="Drow"){
    p->sethp(-15);
  }else {
    p->sethp(-10);
  }
  p->addaction("PC uses PH. ");
}

void PH::notify(Player *p) {
  if(used()) {
    p->addaction("PC find PH. ");
      } else {
    p->addaction("PC find unknown potion. ");
  }
}
