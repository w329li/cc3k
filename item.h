#ifndef ITEM_H
#define ITEM_H
#include <iostream>
#include <string>
#include "observer.h"

class Item: public Observer {
    std::string symbol; // the corresponding symbol of item
    public:
    Item(std::string symbol);
    virtual void notify(Player *pc) = 0;// record the interaction message
    virtual void use(Player *p) = 0;// find out whether player used the potion
    virtual std::string getsymbol();// return the corresponding symbol
    virtual ~Item();

};








#endif
