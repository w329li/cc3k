#ifndef POTION_H
#define POTION_H
#include <iostream>
#include <string>
#include <set>
#include "item.h"

class Potion : public Item {
    static std::set<std::string> drink;// the message of drink
    public:
    Potion();  // default ctor
    ~Potion(); // ctor
    static void havedrink(std::string p); // add new message into drink
    static bool ifdrink(std::string p); // find out whether drunk before
    static void clearpotion(); // clear the potion from the map
    virtual void notify(Player *p) = 0;// record the interaction message
    virtual bool used() = 0; // find out whether player used potion before
    virtual void use(Player *p) = 0; // use the potion
};



#endif
