#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <iterator>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "floor.h"
#include "cell.h"
#include "wall.h"
#include "pass.h"
#include "tile.h"
#include "player.h"
#include "potion.h"
#include "gold.h"
#include "RH.h"
#include "BA.h"
#include "BD.h"
#include "PH.h"
#include "WA.h"
#include "WD.h"
#include "normal.h"
#include "hhoard.h"
#include "mhoard.h"
#include "dhoard.h"
#include "small.h"
#include "info.h"
#include <ncurses.h>

using namespace std;

int Floor::numfloor = 0;


typedef multimap<int,int>::iterator ITERATOR;

Floor::Floor()
    :row{25},col{79},monsternum{20},potionnum{10},goldnum{10},stop{false},pc{nullptr}{
        ++numfloor;
    }



Floor::~Floor() {
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            delete theGrid[i][j];
        }
    }
    while(monsters.size()) {
        Enemy *e = monsters.back();
        monsters.pop_back();
        delete e;
    }
    monsters.clear();
}

int Floor::getfloor() {
    return numfloor;
}

void Floor::setfloor() {
    numfloor = 0;
}

void Floor::setpc(Player *player) {
    pc = player;
}

void Floor::addCell(int i,int j, string symbol) {

    if(symbol == "|") {
        theGrid[i][j] = new Wall("|",i,j);
    } else if(symbol == "-") {
        theGrid[i][j] = new Wall("-",i,j);
    } else if(symbol == " ") {
        theGrid[i][j] = new Wall(" ",i,j);
    } else if(symbol == ".") {
        theGrid[i][j] = new Tile(i,j);
    } else if(symbol == "+") {
        theGrid[i][j] = new Pass("+",i,j);
    } else if(symbol == "#") {
        theGrid[i][j] = new Pass("#",i,j);
    } else {
        theGrid[i][j] = new Tile(i,j);
    }
}

void Floor::addstuff(int i, int j, string symbol) {
    if(symbol == "@") {
        pc->setpos(i,j);
        theGrid[i][j]->set(pc);
    }
    if(symbol == "\\") {
        theGrid[i][j]->setstair();
    }
    if(symbol == "H" || symbol == "W" || symbol == "E" || symbol == "O"
            || symbol == "M" || symbol == "D" || symbol == "L") {
        Enemy *p = nullptr;
        if(symbol == "H") {
            p = new Human();
        } else if(symbol == "M") {
            p = new Merchant();
        } else if(symbol == "E") {
            p = new Elf();
        } else if(symbol == "O") {
            p = new Orc();
        } else if(symbol == "W") {
            p = new Dwarf();
        } else if(symbol == "D") {
            p = new Dragon();
            dragonpos.insert(pair<int,int>(i,j));
        } else if(symbol == "L") {
            p = new Halfling();
        }
        monsters.emplace_back(p);
        theGrid[i][j]->set(p);
    }
    if(symbol == "0" || symbol == "1" || symbol == "2" || symbol == "3"
            || symbol == "4" || symbol == "5") {
        Potion *ptr = nullptr;
        if(symbol == "0") {
            ptr = new RH();
        } else if(symbol == "1") {
            ptr = new BA();
        } else if(symbol == "2") {
            ptr = new BD();
        } else if(symbol == "3") {
            ptr = new PH();
        } else if(symbol == "4") {
            ptr = new WA();
        } else if(symbol == "5") {
            ptr = new WD();
        }
        theGrid[i][j]->set(ptr);
    }
    if(symbol == "6" || symbol == "7" || symbol == "8" || symbol == "9") {
        Gold *ptr = nullptr;
        if(symbol == "6") {
            ptr = new Normal();
        } else if(symbol == "7") {
            ptr = new Small();
        } else if(symbol == "8") {
            ptr = new Mhoard();
        } else if(symbol == "9") {
            ptr = new Dhoard();
            hoardpos.insert(pair<int,int>(i,j));
        }
        theGrid[i][j]->set(ptr);
    }
}




void Floor::basic(const string file) {
    ifstream ss{file};
    string line = "";
    string temp[25];
    if(file != "cc3kfloorempty.txt") {
        for(int i = (getfloor() - 1) * row ; i < getfloor() * row; i++) {
            getline(ss,line);
            temp[i - (getfloor() - 1) * row] = line;
            for(int j = 0; j < col; j++) {
                string symbol;
                symbol = temp[i - (getfloor() - 1) * row][j];
                addCell(i - (getfloor() - 1) * row,j,symbol);
            }
        }
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                addNei(i,j, theGrid[i][j]);
            }
        }
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                string one;
                one = temp[i][j];
                addstuff(i,j, one);
            }
        }
        adddragon();
    } else {
        for(int i = 0; i < row; i++) {
            getline(ss,line);
            for(int j = 0; j < col; j++) {
                string symbol;
                symbol = line[j];
                addCell(i,j,symbol);
            }
        }
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                addNei(i,j, theGrid[i][j]);
            }
        }
    }
}

void Floor::adddragon() {
    ITERATOR pos;
    ITERATOR hpos;
    for(pos = dragonpos.begin(); pos != dragonpos.end(); pos++) {
        int hr = 0;
        int hc = 0;
        int r = pos->first;
        int c = pos->second;
        for(hpos = hoardpos.begin(); hpos != hoardpos.end(); hpos++) {
            int p = hpos->first;
            int q = hpos->second;
            if( ((p - r) * (p - r) + (q - c) * (q - c)) <= 2) {
                hr = p;
                hc = q;
            }
        }
        Observer * o1 = theGrid[hr][hc]->getback();
        Observer * o2 = theGrid[r][c]->getback();
        if( Dhoard * dm = dynamic_cast<Dhoard *>(o1)) {
            if( Dragon *mo = dynamic_cast<Dragon *>(o2)) {
                dm->adddragon(mo);
            }
        }
    }
}


void Floor::addNei(int r, int c, Cell *cell) {
    if(r >= 1) cell->attach(theGrid[r - 1][c]);
    if(r < 24) cell->attach(theGrid[r + 1][c]);
    if(c >= 1) cell->attach(theGrid[r][c - 1]);
    if(c < 78) cell->attach(theGrid[r][c + 1]);
    if(r >= 1 && c >= 1) cell->attach(theGrid[r - 1][c - 1]);
    if(r < 24 && c >= 1) cell->attach(theGrid[r + 1][c - 1]);
    if(r >= 1 && c < 78) cell->attach(theGrid[r - 1][c + 1]);
    if(r < 24 && c < 78) cell->attach(theGrid[r + 1][c + 1]);
}

void Floor::setChamber() {
    for(int i = 3; i <= 6; i++) {
        for(int j = 3; j <= 28; j++) {
            chambers[0].insert(pair<int,int>(i,j));
        }
    }
    for(int i = 15; i <= 21; i++) {
        for(int j = 4; j <= 24; j++) {
            chambers[1].insert(pair<int,int>(i,j));
        }
    }
    for(int i = 3; i <= 12; i++) {
        if(i == 3 || i == 4) {
            for(int j = 39; j <= 61; j++) {
                chambers[2].insert(pair<int,int>(i,j));
            }
        }
        if(i == 5) {
            for(int j = 39; j <= 69; j++) {
                chambers[2].insert(pair<int,int>(i,j));
            }
        }
        if(i == 6) {
            for(int j = 39; j <= 72; j++) {
                chambers[2].insert(pair<int,int>(i,j));
            }
        }
        if(i >= 7) {
            for(int j = 61; j <= 75; j++) {
                chambers[2].insert(pair<int,int>(i,j));
            }
        }
    }
    for(int i = 16; i <= 21; ++i) {
        if(i >= 16 && i <= 18) {
            for(int j = 65; j <= 75; j++) {
                chambers[3].insert(pair<int,int>(i,j));
            }
        } else {
            for(int j = 37; j <= 75; j++) {
                chambers[3].insert(pair<int,int>(i,j));
            }
        }
    }
    for(int i = 10; i <= 12; i++) {
        for(int j = 38; j <= 49; j++) {
            chambers[4].insert(pair<int,int>(i,j));
        }
    }
}

void Floor::placepc() {
    ITERATOR pos;
    int numcham = rand()%5;
    int size = chambers[numcham].size();
    int num = rand()%size;
    for(pos = chambers[numcham].begin(); pos != chambers[numcham].end(); pos++) {
        if(num == 0) {
            pc->setpos(pos->first, pos->second);
            theGrid[pos->first][pos->second]->set(pc);
        }
        num--;
    }
    placestair(numcham);
}

void Floor::placestair(int playcham) {
    ITERATOR pos;
    int numcham = rand()%5;
    while(numcham == playcham) {
        numcham = rand()%5;
    }
    int size = chambers[numcham].size();
    int r = 0;
    int c = 0;
    int num = rand()%size;
    for(pos = chambers[numcham].begin(); pos != chambers[numcham].end(); pos++) {
        if(num == 0) {
            r = pos ->first;
            c = pos->second;
        }
        num--;
    }
    theGrid[r][c]->setstair();
    stair.first = r;
    stair.second = c;
}


void Floor::findrc(int &r, int &c, int numcham) {
    ITERATOR pos;
    int size = chambers[numcham].size();
    int num = rand()%size;
    for(pos = chambers[numcham].begin(); pos != chambers[numcham].end(); pos++) {
        if(num == 0) {
            r = pos->first;
            c = pos->second;
        }
        num--;
    }
}



void Floor::placepotion() {
    ITERATOR pos;
    int r = 0;
    int c = 0;
    for(int i = 0; i < potionnum; i++) {
        int numcham = rand()%5;
        do {
            findrc(r,c, numcham);
        } while(theGrid[r][c]->have());
        Potion* p = nullptr;
        int type = rand()%6;
        switch(type) {
            case 0: p = new RH(); break;
            case 1: p = new BA(); break;
            case 2: p = new BD(); break;
            case 3: p = new PH(); break;
            case 4: p = new WA(); break;
            case 5: p = new WD(); break;
        }
        theGrid[r][c]->set(p);
    }
}

void Floor::placegold() {
    ITERATOR pos;
    int r = 0;
    int c = 0;
    for(int i = 0; i < goldnum; i++) {
        int numcham = rand()%5;
        do{
            findrc(r,c,numcham);
        } while(theGrid[r][c]->have());
        Gold* g = nullptr;
        int type = rand()%8;
        if(type >=0 && type <= 4) {
            g = new Normal();
        }
        if(type >=5 && type <= 6) {
            g = new Small();
        }
        if(type == 7) {
            Dragon *p = new Dragon();
            g = new Dhoard(p);
            placedragon(r,c,p);
        }
        theGrid[r][c]->set(g);
    }
}

void Floor::placedragon(int oldr, int oldc,Dragon *p) {
    int newr = oldr;
    int newc = oldc;
    do{
        do{
            newr = oldr + (rand()%3 - 1);
            newc = oldc + (rand()%3 - 1);
        } while(((newr == oldr) && (newc == oldc)));
        if(!validrc(newr,newc)) continue;
        if(theGrid[newr][newc]->monstermoveable()) break;
    } while(true);
    theGrid[newr][newc]->set(p);
    monsters.emplace_back(p);
}



void Floor::placeenemy() {
    ITERATOR pos;
    int r = 0;
    int c = 0;
    for(int i = 0; i < monsternum; i++) {
        int numcham = rand()%5;
        do{
            findrc(r,c,numcham);
        } while(theGrid[r][c]->have());
        Enemy *e = nullptr;
        int type = rand()%18;  //18
        if(type >=0 && type <= 3) {
            e = new Human();
        }
        if(type >=4 && type <= 6) {
            e = new Dwarf();
        }
        if(type >= 7 && type <= 11) {
            e = new Halfling();
        }
        if(type >= 12 && type <= 13) {
            e = new Elf();
        }
        if(type >= 14 && type <= 15) {
            e = new Orc();
        }
        if(type >= 16 && type <= 17) {
            e = new Merchant();
        }
        theGrid[r][c]->set(e);
        monsters.emplace_back(e);
    }
}

void Floor::init(const string file) {
    if(file == "cc3kfloorempty.txt") {
        basic();
        setChamber();
        placepc();
        placepotion();
        placegold();
        placeenemy();
    } else {
        basic(file);
        setChamber();
    }
}


bool Floor::validrc(int r, int c) {
    if((r >= 0 && r <= row - 1) && (c >= 0 && c <= col - 1)) return true;
    return false;
}

bool Floor::ifchange(int newr, int newc, int oldr, int oldc) {
    if(!validrc(newr, newc)) return false;
    if(theGrid[newr][newc]->ifmoveable()) {
        pc->setpos(newr,newc);
        return true;
    } else {
        if(theGrid[newr][newc]->getsymbol() == "G") {
            Observer * o1 = theGrid[newr][newc]->getback();
            if(Gold *g = dynamic_cast<Gold *>(o1)) {
                if(g->getvalue() == 6) {
                    if(Dhoard *dh = dynamic_cast<Dhoard *>(g)) {
                        if(dh->havedragon()) {
                            return false;
                        } else {
                            pc->pickgold(g->getvalue());
                            theGrid[newr][newc]->erase(pc);
                            return true;

                        }
                    }
                } else {
                    pc->pickgold(g->getvalue());
                    theGrid[newr][newc]->erase(pc);
                    return true;
                }
            }
        }
    }
    return false;
}

void Floor::getnew(const string dir,int &newr, int &newc) {
    if(dir == "no") {
        newr -= 1;
    } else if(dir == "so") {
        newr += 1;
    } else if(dir == "ea") {
        newc += 1;
    } else if(dir == "we") {
        newc -= 1;
    } else if(dir == "ne") {
        newr -= 1;
        newc += 1;
    } else if(dir == "nw") {
        newr -= 1;
        newc -= 1;
    } else if(dir == "se") {
        newr += 1;
        newc += 1;
    } else if(dir == "sw") {
        newr += 1;
        newc -= 1;
    }
}




void Floor::Playerwalk(const string dir) {
    Info info = pc->getInfo();
    int r = info.row;
    int c = info.col;
    int newr = r;
    int newc = c;
    getnew(dir,newr,newc);
    bool t = ifchange(newr,newc,r,c);
    if(t) {
        if(theGrid[newr][newc]->getsymbol() == "\\") {
            success = true;
        }
        theGrid[r][c]->leave();
        theGrid[newr][newc]->set(pc);
        theGrid[newr][newc]->notifyObservers(pc);
        monsterswalk();
        if(dir == "no") {
            pc->addaction("PC moves North. ");
        } else if(dir == "so") {
            pc->addaction("PC moves South. ");
        } else if(dir == "ea") {
            pc->addaction("PC moves East. ");
        } else if(dir == "we") {
            pc->addaction("PC moves West. ");
        } else if(dir == "ne") {
            pc->addaction("PC moves NorthEast. ");
        } else if(dir == "nw") {
            pc->addaction("PC moves NorthWest. ");
        } else if(dir == "se") {
            pc->addaction("PC moves SouthEast. ");
        } else if(dir == "sw") {
            pc->addaction("PC moves SouthWest. ");
        }
    } else {
        pc->addaction("you are in wrong direction. ");
        theGrid[r][c]->notifyObservers(pc);
        monsterswalk();
    }
}
static bool ifmonster(const string symbol) {
    return  (symbol == "H" || symbol == "W" || symbol == "E" || symbol == "O"
            || symbol == "M" || symbol == "D" || symbol == "L");
}

void Floor::monsterswalk()  {
    if(!stop) {
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                if(ifmonster(theGrid[i][j]->getsymbol())) {
                    Observer *o = theGrid[i][j]->getback();
                    if(Enemy *mo = dynamic_cast<Enemy *>(o)) {
                        if(!mo->ifturnover()) {
                            if(mo->getrace() == "Dragon") {
                            } else {
                                Info info = mo->getInfo();
                                int oldr = info.row;
                                int oldc = info.col;
                                int newr = 0;
                                int newc = 0;
                                do{
                                    do{
                                        newr = oldr + (rand()%3 - 1);
                                        newc = oldc + (rand()%3 - 1);
                                    } while((newr == oldr) && (newc == oldc));
                                    if(!validrc(newr,newc)) continue;
                                    if(theGrid[newr][newc]->monstermoveable()) break;
                                } while(true);
                                theGrid[oldr][oldc]->leave();
                                theGrid[newr][newc]->set(mo);
                                mo->changeturn();
                            }
                        }

                    }
                }
            }
        }
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                if(ifmonster(theGrid[i][j]->getsymbol())) {
                    Observer *o = theGrid[i][j]->getback();
                    if(Enemy *mo = dynamic_cast<Enemy *>(o)) {
                        if(mo->getrace() == "Dragon") {
                            if(!mo->ifturnover()) mo->changeturn();
                        }
                        mo->changeturn();
                    }
                }
            }
        }
    } else {
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                if(ifmonster(theGrid[i][j]->getsymbol())) {
                    Observer *o = theGrid[i][j]->getback();
                    if(Enemy *mo = dynamic_cast<Enemy *>(o)) {
                            if(mo->ifturnover()) mo->changeturn();
                    }
                }
            }
        }
    }
}





void Floor::usePotion(const string dir) {
    Info info = pc->getInfo();
    int r = info.row;
    int c = info.col;
    int newr = r;
    int newc = c;
    getnew(dir,newr,newc);
    if(theGrid[newr][newc]->getsymbol() == "P") {
        theGrid[newr][newc]->use(pc);
        theGrid[newr][newc]->erase(pc);
        theGrid[r][c]->notifyObservers(pc);
        monsterswalk();
        return;
    }
    theGrid[newr][newc]->notifyObservers(pc);
    monsterswalk();
}




void Floor::pcattack(const string dir) {
    Info info = pc->getInfo();
    int r = info.row;
    int c = info.col;
    int newr = r;
    int newc = c;
    getnew(dir,newr,newc);
    if(newr != r || newc != c) {
        if(ifmonster(theGrid[newr][newc]->getsymbol())) {
            Observer *o1 = theGrid[newr][newc]->getback();
            if(Enemy *e = dynamic_cast<Enemy *>(o1)) {
                pc->attack(e);
            }
            theGrid[newr][newc]->use(pc);
        }
    }
    theGrid[r][c]->notifyObservers(pc);
    monsterswalk();
}

void Floor::stopmove() {
    if(!stop) {
        stop = true; return;
    } else {
        stop = false; return;
    }
}

bool Floor::getstop() {
    return stop;
}
bool Floor::getsuccess() {
    return success;
}

bool Floor::fail() {
    if(pc->ifdead()) {
        cout << "Game fail" << endl;
        return true;
    }
    return false;
}

ostream &operator<<(ostream &out, const Floor &f) {
    for(int i = 0; i < f.row; i++) {
        for(int j = 0; j < f.col; j++) {
            out << f.theGrid[i][j]->getsymbol();
        }
        out << endl;
    }
    out << endl;
    out << "Race: " << f.pc->getrace() << " Gold: " << f.pc->getgold();
    out << "                                               Floor " << Floor::numfloor << endl;
    out << "HP: " << f.pc->gethp() << endl;
    out << "Atk: " << f.pc->getatk() << endl;
    out << "Def: " << f.pc->getdef() << endl;
    out << "Action: ";
    f.pc->display();
    f.pc->clear();
    return out;
}

void Floor::display(bool read) {
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            mvprintw(i,j,"%s",theGrid[i][j]->getsymbol().c_str());
        }
    }
    string c = "Race: " + pc->getrace();
    int l = c.length();
    mvprintw(25,0,"%s",c.c_str());
    mvprintw(25,l,"%s"," Gold: ");
    mvprintw(25,l+7,"%d",pc->getgold());
    mvprintw(25,70, "%s","Floor ");
    mvprintw(25,76,"%d",Floor::numfloor);
    mvprintw(26,0,"%s","HP: ");
    mvprintw(26,4,"%d",pc->gethp());
    mvprintw(27,0,"%s","Atk: ");
    mvprintw(27,5,"%d",pc->getatk());
    mvprintw(28,0,"%s","Def: ");
    mvprintw(28,5,"%d",pc->getdef());
    mvprintw(29,0,"%s","Action: ");
    mvprintw(29,8,"%s",pc->gets().c_str());
    if(read) pc->clear();
    refresh();
}

void Floor::buy(const string dir) {
    Info info = pc->getInfo();
    int r = info.row;
    int c = info.col;
    int newr = r;
    int newc = c;
    getnew(dir,newr,newc);
    if(newr != r || newc != c) {
        if(theGrid[newr][newc]->getsymbol() == "M") {
            Observer *o1 = theGrid[newr][newc]->getback();
            addstr("do you want to buy some weapon? \n");
            addstr("1: programmer sword(+20 attack) (20 gold) \n");
            addstr("2: pencil case(+2 attack) (30 gold) \n");
            addstr("3: cs246 note(+50 attck) (40 gold) \n");
            addstr("4: smelly shoes(+60 attack) (50 gold) \n");
            addstr("5: waterloo goose(+80 attack)  (100 gold) \n");
            int d = getch();
            switch(d) {
                case '1':if(pc->getgold() < 20) {
                             clear();
                             addstr("Sorry, you don't have enough money. \n");
                             addstr("Don't waste my time. \n");
                             addstr("Agree to leave. (Y:yes) (N:no (you rob the merchant, merchant will hate you))\n");
                             int r = getch();
                             if(r == 'N') {
                                 pc->setatk(20);
                                 if(Enemy *e = dynamic_cast<Enemy *>(o1)) {
                                     pc->addaction("PC stolen programmer sword. ");
                                     pc->attack(e);
                                 }
                             }
                             clear();
                             refresh();
                             if(r != 'N') pc->addaction("you waste one turn. ");
                         } else {
                             pc->setatk(20);
                             pc->setgold(-20);
                         }
                         break;
                case '2':if(pc->getgold() < 30) {
                             clear();
                             //  refresh();
                             addstr("Sorry, you don't have enough money. \n");
                             //  mvprintw(6,0,"%s","sorry");
                             addstr("Don't waste my time. \n");
                             addstr("Agree to leave. (Y:yes) (N:no (you rob the merchant, merchant wil hate you))\n");
                             int r = getch();
                             if(r == 'N') {
                                 pc->setatk(2);
                                 if(Enemy *e = dynamic_cast<Enemy *>(o1)) {
                                     pc->addaction("PC stolen pencil case. ");
                                     pc->attack(e);
                                 }
                             }
                             clear();
                             refresh();
                             if(r != 'N') pc->addaction("you waste one turn. ");
                         } else {
                             pc->setatk(2);
                             pc->setgold(-30);
                         }
                         break;
                case '3':if(pc->getgold() < 40) {
                             clear();
                             addstr("Sorry, you don't have enough money. \n");
                             addstr("Don't waste my time. \n");
                             addstr("Agree to leave. (Y:yes) (N:no (you rob the merchant, merchant wil hate you))\n");
                             int r = getch();
                             if(r == 'N') {
                                 pc->setatk(50);
                                 if(Enemy *e = dynamic_cast<Enemy *>(o1)) {
                                     pc->addaction("PC stolen cs246 course note. ");
                                     pc->attack(e);
                                 }
                             }
                             clear();
                             refresh();
                             if(r != 'N') pc->addaction("you waste one turn. ");
                         } else {
                             pc->setatk(50);
                             pc->setgold(-40);
                         }
                         break;
                case '4':if(pc->getgold() < 50) {
                             clear();
                             //  refresh();
                             addstr("Sorry, you don't have enough money. \n");
                             addstr("Don't waste my time. \n");
                             addstr("Agree to leave. (Y:yes) (N:no (you rob the merchant, merchant wil hate you))\n");
                             int r = getch();
                             if(r == 'N') {
                                 pc->setatk(60);
                                 if(Enemy *e = dynamic_cast<Enemy *>(o1)) {
                                     pc->addaction("PC stolen smelly shoes. ");
                                     pc->attack(e);
                                 }
                             }
                             clear();
                             refresh();
                             if(r != 'N') pc->addaction("you waste one turn. ");
                         } else {
                             pc->setatk(60);
                             pc->setgold(-50);
                         }
                         break;
                case '5':if(pc->getgold() < 100) {
                             clear();
                             addstr("Sorry, you don't have enough money. \n");
                             addstr("Don't waste my time. \n");
                             addstr("Agree to leave. (Y:yes) (N:no (you rob the merchant, merchant wil hate you))\n");
                             int r = getch();
                             if(r == 'N') {
                                 pc->setatk(80);
                                 if(Enemy *e = dynamic_cast<Enemy *>(o1)) {
                                     pc->addaction("PC stolen waterloo goose. ");
                                     pc->attack(e);
                                 }
                             }
                             clear();
                             refresh();
                             if(r != 'N') pc->addaction("you waste one turn. ");
                         } else {
                             pc->setatk(80);
                             pc->setgold(-100);
                         }
                         break;
            }
        }
    }
    theGrid[r][c]->notifyObservers(pc);
    monsterswalk();
}
