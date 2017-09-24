#include "WD.h"
#include "player.h"
#include <string>

using namespace std;


WD::WD():Potion(){}
WD::~WD(){}

bool WD::used() {
    return Potion::ifdrink("WD");
}



void WD:: use(Player *p) {
  Potion::havedrink("WD");
  if (p->getrace()=="Drow"){
    p->setdef(-7);
  }else {
    p->setdef(-5);
  }
  p->addaction("PC uses WD. ");

}

void WD::notify(Player *p) {
  if(used()) {
    p->addaction("PC find WD.");
      } else {
    p->addaction("PC find unknown potion.");
  }
}
