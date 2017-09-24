#ifndef ENERMY_H
#define ENERMY_H

#include <string>
#include "observer.h"
#include "character.h"
class Player;
class Enemy: public Character, public Observer{

    bool turnover; // record whether current action is finished
public:
    Enemy(int hp, int atk, int def,std::string name, std::string n);// ctor
    virtual ~Enemy(); // dtor
    virtual void notify(Player *pc) override;// record the interaction message
    virtual int dropgold(); //human::dropgold,dragon::dropgold will override it.
    virtual void attack(Player *p); // attack process during a combat
    virtual void defend(Player &p);  // defend process during a combat
    virtual std::string getsymbol() override; // return corrresponding enemy's symbol
    int getdamage(Player &p); // return damage from player
    bool ifturnover(); // find out whether current action is finished
    void changeturn(); // change the statue of turnover
    void use(Player *pc);
    void dead(); // set character to the dead mode
};

#endif
