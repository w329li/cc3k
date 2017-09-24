#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <fstream>
#include <string>
#include "floor.h"
#include "player.h"

class Game {
    std::string layout; // record the layout of map
    Player *pc; // record the current player
    Floor *f; // record the current floor
    bool dlc; // statue of dlc
    public:
      Game(); // default ctor
      int calscor(); // calculate the current scorce
      void choose(); // choose the player character
      void startfloor(const std::string file = "cc3kfloorempty.txt");// display the current floor
      void play(); // it is in charge of all basic option and interaction during game period
      void reset(); // reset all setting to original settting
      void nextfloor(); // update the f to next floor
      ~Game();
};

#endif
