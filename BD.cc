#include "BD.h"
#include "player.h"
#include <string>

using namespace std;



BD::BD():Potion() {}
BD::~BD(){}

bool BD::used() {
    return Potion::ifdrink("BD");
}


void BD:: use(Player *p) {
  Potion::havedrink("BD");
  if (p->getrace()=="Drow"){
      p->setdef(7);
  }else {
    p->setdef(5);
  }
  p->addaction("PC uses BD. ");
}

void BD::notify(Player *pc) {
  if(used()) {
      pc->addaction("PC find BD. ");
  } else {
    pc->addaction("PC find unknown potion. ");
  }
}
