#ifndef FLOOR_H
#define FLOOR_H
#include <iostream>
#include <vector>
#include <map>
#include "cell.h"
#include "player.h"
#include "enemy.h"
#include "item.h"


class Floor {
  static int numfloor; // total number of floor
//  Cell *theGrid[25][79];  // The actual grid.
  std::vector<Enemy *>monsters;  // record all monsters on map
  std::pair<int, int> stair; // record the stair
  int row; // row number of floor
  int col; // column number of floor
  int monsternum; // total number of monster
  int potionnum; // total number of potion
  int goldnum; // total number of gold
  bool stop;
  bool dlc; // statue of dlc
  std::multimap<int,int> chambers[5];
    // the one below used to record the dragon and corresponding
    //  protected gold
  std::multimap<int,int> dragonpos;
  // the one below used to record the human and corresponding
    //  protected gold
  std::multimap<int,int> hoardpos;
  Player *pc; // record current player
  bool success = false;
  void adddragon(); // initialize a new dragon
  void placestair(int numcham); // randomly put stair on map
  void findrc();
  void placepotion(); // randomly put potion on map
  void placegold(); // randomly put gold on map
  void placedragon(int oldr, int oldc,Dragon *p); // randomly put dragon on map
  void placeenemy();  // randomly put enemy on map
  bool validrc(int r, int c); // find out whether character is moving in a legal way
  // the one below  is uesd to find out whether the position of character changed
  bool ifchange(int newr, int newc, int oldr, int oldc);
  void getnew(const std::string dir,int &newr, int &newc);// get new coor of character
 public:
  Floor(); // default ctor
  ~Floor(); // dtor
  Cell *theGrid[25][79]; // initialize the map
  static int getfloor(); // return the number of floor
  static void setfloor(); // reset the floor to original settting
  void setpc(Player *player); // initialize the player
  void addCell(int i,int j, std::string symbol); // add a new cell
  //the one below used to set up the floor to it original staue
  void basic(const std::string file = "cc3kfloorempty.txt");
  void addNei(int r, int c, Cell *cell);// add element in internal part of map
  void setChamber(); // set up the chamber
  void placepc(); // randomly put the player on the map
  void findrc(int &r, int &c, int numcham);
  void init(const std::string file); // initialize all the setting
  void Playerwalk(const std::string dir);// change the coor of player
  void monsterswalk(); // change the coor of monsters
  void usePotion(const std::string dir); // player use the potion
  void pcattack(const std::string dir);
  void stopmove();
  bool getstop();
  bool getsuccess(); // get the success statue
  bool fail();
  void display(bool read = true);
  void buy(const std::string dir); // make player update its equipment
  void addstuff(int i, int j, std::string symbol); // add new element into the map
  friend std::ostream &operator<<(std::ostream &out, const Floor &f);
};

#endif
