#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <vector>

class Player;
class Observer;

class Subject {
 protected:
  std::vector<Observer*> observers; // record the interaction during the game period
 public:
  void attach(Observer *o); // add new record to observers
  void notifyObservers(Player *p);// record the interaction message
  void remove(); // record the last element of observers
  virtual ~Subject() = 0; // dtor
};

#endif
