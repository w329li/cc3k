#include <iostream>
#include <string>
#include "gold.h"
#include "player.h"
#include "item.h"
using namespace std;


Gold::Gold(int value,string type)
  :Item("G"),value{value},size{type} {}

Gold::~Gold() {}

void Gold::pick(Player *p) {
        p->setgold(value);
}

int Gold::getvalue() {
    return value;
}

string Gold::getsize() {
    return size;
}

void Gold::notify(Player *pc) {
  string c = "pc finds gold (" + size + "). ";
  pc->addaction(c);
}

void Gold::use(Player *pc) {
  pc->setgold(value);
}










