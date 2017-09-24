#include "enemy.h"
#include "player.h"
#include <cmath>
#include <sstream>
#include <iostream>
#include "shade.h"
#include "drow.h"
#include "vampire.h"
#include "troll.h"
#include "goblin.h"
#include "character.h"
using namespace std;

Enemy::Enemy(int hp, int atk, int def, string name, string n):Character(hp,atk,def,name,n){}
Enemy::~Enemy(){}

int Enemy::dropgold(){
    int chance;
    chance = rand() % 2;
    if (chance==1){
        return 2;
    }
    else{
        return 1;
    }
}



int Enemy::getdamage(Player &e) {
    int damage = ceil((100 / (double)(100 + getdef())) * e.getatk());
    return damage;
}


void Enemy::attack(Player *p){
    if(!turnover) {
        turnover = true;
        int success;
        success = rand() % 2;
        if (success==1){
            p->defend(*this);
        } else {
            string c = getsymbol() + "'s attack missed. ";
            p->addaction(c);
        }
    }
}

void Enemy::notify(Player *pc) {
    if(turnover == false) {
        attack(pc);
    }
}

void Enemy::use(Player *pc) {
    attack(pc);
}

bool Enemy::ifturnover() {
    return turnover;
}

void Enemy::changeturn() {
    if(turnover) {
        turnover = false;
    } else {
        turnover = true;
    }

}

void Enemy::dead() {
    Character::dead();
    string s = Character::getsymbol();
}


void Enemy::defend(Player &p) {
    int n = getdamage(p);
    stringstream ss;
    ss << n;
    string damage  = ss.str();
    sethp((-1) * n);
    int whp = Character::gethp();
    if(Character::gethp() <= 0) {
        Character::dead();
    } else {
        string symbol = Character::getsymbol();
        ss.str("");
        ss << whp;
        string hp = "";
        ss >> hp;

        string c = "PC deals " + damage + " damage to " + symbol + "(" + hp + " HP). ";
        p.addaction(c);
    }
}


string Enemy::getsymbol() {
    return Character::getsymbol();
}
