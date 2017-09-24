#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include <utility>
#include <sstream>
#include <fstream>
#include "info.h"

class Character {
   protected:
    int hp; // value of hp
   private:
    int atk; // value of attack
    int def; // value of defend
    int gold; // the amount of gold that character has
    bool isdead; // life statue of character
    std::string race; // name of race
    std::string symbol; // symbol shown on the map
    int maxhp; // the value of original hp
    int r; // number of row coor
    int c; // number of column coor
    public:
    Character(int hp, int atk, int def, std::string race,std::string symbol);
    virtual int gethp(); // show the current hp of character
    virtual void sethp(int dis); // set the new hp
    virtual int getatk(); // show the current atk of character
    virtual void setatk(int dis); // set the new atk
    virtual  int getdef(); // show the current def of character
    virtual void setdef(int dis); // set the new def
 //   virtual int getgold(); // show the amount of gold character has
 //   virtual void setgold(int dis); // set the new amount of gold
    virtual void setpos(int row, int col);
    Info getInfo();
    std::string getrace(); // show the race
    virtual std::string getsymbol(); // show the symbol
    virtual void dead(); // when the characte dead,it disappears from screen
    virtual bool ifdead(); // find out whether the character is dead
    virtual ~Character(); // dtor
};

#endif
