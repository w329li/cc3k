#include "WA.h"
#include "player.h"
#include <string>

using namespace std;

WA::WA(): Potion(){}
WA::~WA(){}

bool WA :: used() {
    return Potion::ifdrink("WA");
}



void WA::notify(Player *p) {
  if(used()) {
    p->addaction("PC find WA. ");
      } else {
    p->addaction("PC find unknown potion. ");
  }
}

void WA:: use(Player *p) {
  Potion::havedrink("WA");
  if (p->getrace()=="Drow"){
    p->setatk(-7);
  }else {
    p->setatk(-5);
  }
  p->addaction("PC uses WA. ");

}

