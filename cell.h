#ifndef __CELL_H__
#define __CELL_H__
#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include "subject.h"
#include "observer.h"
#include "player.h"


class Cell : public Subject, public Observer {
  std::string basic; // the basic setting of cell
  std::string symbol; // the corresponding symbol of current one
  bool moveable; // show whether the current can be removed
  int r, c; // the coor of the current one
 public:
  Cell(std::string symbol, bool moverable, int r, int c);  // Default constructor
  bool have(); //
  std::string getsymbol(); // return the symbol of current one
  bool ifmoveable(); // find out whether the current one can be removed
  bool monstermoveable(); // find out whether the monster should be removed
  void setstair(); // set up the stair
  void erase(Player *pc);
  int getr(); // return the row coor
  int getc(); // return the column coor
  void set(Observer *o); // update the observer
  void leave();
  void use(Player *player);
  Observer* getback(); // return the last element of observers

  virtual void notify(Player *player) override; // record the interaction message
    ~Cell(); // dtor
};


#endif
