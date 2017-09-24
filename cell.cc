#include <utility>
#include <vector>
#include "subject.h"
#include "observer.h"
#include "cell.h"
#include "info.h"
#include "item.h"
#include "character.h"
#include "small.h"
#include "normal.h"
#include "hhoard.h"
#include "mhoard.h"
#include "dhoard.h"
#include "enemy.h"
#include "potion.h"

using namespace std;

Cell::Cell(string symbol,bool moveable,int r, int c)
    :basic{symbol},symbol{symbol},moveable{moveable},r{r},c{c} {}

bool Cell::have() {
    if(symbol != ".") return true;
    return false;
}

bool Cell::ifmoveable() {
    if(symbol == "\\") return true;
    if(basic == "+" || basic == "#") return true;
    return (moveable && (!have()));
}


bool Cell::monstermoveable() {
    return (moveable && (!have()));
}


void Cell::setstair() {
    symbol = "\\";
}


void Cell::erase(Player *pc) {
    if(!(observers.back()->getsymbol() == "P" ||
                observers.back()->getsymbol() == "G")) {
        Observer *e = observers.back();
        if(Enemy *d = dynamic_cast<Enemy *>(e)) {
            string race = d->getrace();
            Gold *g = nullptr;
            if(!(race == "Dragon" || race == "Human" || race == "Merchant")) {
                int type = rand() % 2;
                switch(type) {
                    case 0: pc->addaction("PC got a small pie of gold from slained enemy. ");
                            pc->silentgold(1);
                            break;
                    case 1: pc->addaction("PC got a normal pie of gold from slained enemy. ");
                            pc->silentgold(2);
                            break;
                }
                symbol = basic;
                observers.pop_back();
            } else {
                if(race == "Human") {
                    set(g = new Hhoard());
                } else if(race == "Merchant") {
                    set(g = new Mhoard());
                } else {
                    symbol = basic;
                    observers.pop_back();
                }
            }
        }
    } else {
            Observer *i = observers.back();
            symbol = basic;
            observers.pop_back();
            delete i;
    }
}




Cell::~Cell() {
    if(symbol == "P" || symbol == "G") {
        delete observers.back();
    }
}


void Cell::set(Observer *o) {
    attach(o);
    symbol = o->getsymbol();
    if(Enemy *d = dynamic_cast<Enemy *>(o)) {
        d->setpos(r,c);
    } else if(Player *p = dynamic_cast<Player *>(o)) {
         p->setpos(r,c);
    }
}

void Cell::leave() {
    observers.pop_back();

    symbol = basic;
}

void Cell::use(Player *player) {
    Observer *e = observers.back();
    if(Enemy *d = dynamic_cast<Enemy *>(e)) {
        d->use(player);
        if(d->ifdead()) {
            erase(player);
        }
    } else if(Potion *p = dynamic_cast<Potion *>(e)) {
        p->use(player);
        erase(player);
    }
}

static bool ifmonster(const string symbol) {
    return  (symbol == "H" || symbol == "W" || symbol == "E" || symbol == "O"
            || symbol == "M" || symbol == "D" || symbol == "L");
}

void Cell::notify(Player *player) {
    if(symbol == "G" || symbol == "P" || ifmonster(symbol)) {
        observers.back()->notify(player);
    }
}
Observer* Cell::getback() {
    return observers.back();
}

string Cell::getsymbol() {
    return symbol;
}

int Cell::getr() {
    return r;
}

int Cell::getc() {
    return c;
}
