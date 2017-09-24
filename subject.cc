#include "subject.h"
#include "observer.h"
#include <iostream>
#include <vector>
using namespace std;


void Subject::attach(Observer *o) {
    observers.emplace_back(o);
}

void Subject::remove() {
  observers.pop_back();
}

void Subject::notifyObservers(Player *t) {
  int size = observers.size();
  for(int i = 0; i < size; ++i) {
      observers[i]->notify(t);
  }
}


Subject::~Subject() {}

