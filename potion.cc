#include <iostream>
#include <string>
#include <set>
#include <iterator>
#include "potion.h"

using namespace std;

set<string> Potion::drink = {};

Potion:: Potion()
  :Item("P"){}

Potion:: ~Potion() {}

void Potion::havedrink(string p) {
    drink.insert(p);
}

bool Potion::ifdrink(string p) {
    auto pos = drink.find(p);
    if(pos != drink.end()) {
        return true;
    } else {
        return false;
    }
}

void Potion::clearpotion() {
  drink.clear();
}



