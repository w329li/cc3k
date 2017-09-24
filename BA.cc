#include "BA.h"
#include "player.h"
#include <string>

using namespace std;



bool BA :: used() {
    return Potion::ifdrink("BA");
}

BA::BA()
  :Potion() {}

BA::~BA(){}

void BA::notify(Player *p) {
  if(used()) {
    p->addaction("PC find BA. ");
      } else {
    p->addaction("PC find unknown potion. ");
  }
}


void BA:: use(Player *p) {
  Potion::havedrink("BA");
  if (p->getrace()=="Drow"){
    p->setatk(7);
  }else {
    p->setatk(5);
  }
  p->addaction("PC uses BA. ");
}


