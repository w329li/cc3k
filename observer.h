#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include <string>

class Player;

class Observer {
 public:
  virtual void notify(Player* pc) = 0;  // player pointer??
          // get information virtual
  virtual ~Observer() = default; // dtor
  virtual std::string getsymbol() = 0;// return the corresponding symbol
};
#endif
