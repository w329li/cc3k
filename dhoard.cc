#include <string>
#include "dhoard.h"
#include "dragon.h"

using namespace std;

Dhoard::Dhoard(): Gold(6,"dhoard") {}

Dhoard::Dhoard(Dragon *d): Gold(6, "dhoard"),d{d} {}

Dhoard:: ~Dhoard() {}

void Dhoard::adddragon(Dragon *dra) {
  d = dra;
}

void Dhoard::notify(Player *pc) {
  string c = "pc finds dragon hoard. ";
  pc->addaction(c);
  if(!d->ifdead()) {
    d->attack(pc);
  }
}

void Dhoard::use(Player *pc) {
  pc->setgold(getvalue());
  if(!d->ifdead()) {
    d->attack(pc);
  }
}

bool Dhoard::havedragon() {
    if(!d->ifdead()) {
        return true;
    } else {
        return false;
    }
}
