#ifndef PLAYER_H
#define PLAYER_H
#include "character.h"
#include "observer.h"
#include "enemy.h"
#include "human.h"
#include "halfling.h"
#include "merchant.h"
#include "elf.h"
#include "dwarf.h"
#include "dragon.h"
#include "orc.h"
#include "info.h"

class Player: public Character, public Observer {
    // funcions below are the combat process between player and enemies
    virtual void strike(Enemy &e); // strike process during combat
    int basicatk; // the original value of attack
    int basicdef; // the original value of defend
    int gold; // the amount of gold player has
    std::string a = ""; // record the information related to player
    public:
    Player(int hp,int atk, int def, std::string race);
    void attack(Enemy* e); // attack the enemy
    virtual void defend(Enemy &e); // defend process during a combat
    int getdamage(Enemy &e); // return the damage from enemy
    void pickgold(int num); // get certain amount of gold
    void tobasic(); // reset all value to its original settting
    virtual std::string getsymbol() override; // return corresponding symbol
    virtual void notify(Player* pc) override; // record the interaction message
    void addaction(std::string s); // record the new action
    int getgold(); // return the value of gold
    void setgold(int dis); // update the amount of gold and record the message
    void display();
    void clear(); // clear the character from map
    void silentgold(int dis); // reset the value of gold
    std::string gets(); //
    ~Player(); // dtor
};

#endif
