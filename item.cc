#include <iostream>
#include <string>
#include "item.h"

using namespace std;

Item::Item(string symbol)
  :symbol{symbol} {}

string Item::getsymbol() {
  return symbol;
}

Item::~Item(){
}






