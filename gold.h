#ifndef GOLD_H
#define GOLD_H
#include <iostream>
#include <string>
#include "item.h"

class Player;

class Gold: public Item {
    int value; // amount of gold
    std::string size; // the type of gold
    public:
    Gold(int value,std::string size); // default ctor
    ~Gold();
    int getvalue(); // return the amount of gold
    void pick(Player *p); // player picks the gold
    std::string getsize(); // return the type of gold
    virtual void notify(Player *pc) override;// record the interaction message
    virtual void use(Player *pc) override; // player uses the gold it has
};









#endif
