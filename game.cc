#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <cmath>
#include "player.h"
#include "game.h"
#include "floor.h"
#include "merchant.h"
#include "potion.h"
#include "shade.h"
#include "drow.h"
#include "vampire.h"
#include "troll.h"
#include "goblin.h"
#include <ncurses.h>

using namespace std;

Game::Game():dlc{false} {}
void Game::choose() {
    cout << "If add dlc ?     Y:yes    N:no" << endl;
    string answer;
    while(!(cin >> answer)) {
    }
    if(answer == "Y" || answer == "y") {
        dlc = true;
    }
    if(dlc) {
        initscr();
        cbreak();
        noecho();
        clear();
        mvprintw(0,0, "%s",  "choose one race");
        mvprintw(1,0, "%s",  "s: Shade" );
        mvprintw(2,0, "%s",  "d: Drow");
        mvprintw(3,0, "%s",  "v: Vampire");
        mvprintw(4,0, "%s",  "t: Troll");
        mvprintw(5,0, "%s",  "g: Goblin");

        int in;
        while(in = getch()) {
            if(in == 's') {
                pc = new Shade(); break;
            }
            if(in == 'd') {
                pc = new Drow(); break;
            }
            if(in == 'v') {
                pc = new Vampire(); break;
            }
            if(in == 't') {
                pc = new Troll(); break;
            }
            if(in == 'g') {
                pc = new Goblin(); break;
            }
        }
        endwin();
    } else {
        cout << "choose one race" << endl;
        cout << "s: Shade" << endl;
        cout << "d: Drow" << endl;
        cout << "v: Vampire" << endl;
        cout << "t: Troll" << endl;
        cout << "g: Goblin" << endl;
        string in = "";
        while(cin >> in) {
            if(in == "s") {
                pc = new Shade(); break;
            }
            if(in == "d") {
                pc = new Drow(); break;
            }
            if(in == "v") {
                pc = new Vampire(); break;
            }
            if(in == "t") {
                pc = new Troll(); break;
            }
            if(in == "g") {
                pc = new Goblin(); break;
            } else {
                cout << "wrong input. " << endl;
            }
        }
    }
}

int Game::calscor() {
    int score = pc->getgold();
    if(pc->getrace() == "Shade") return ceil(score * 1.5);
    return score;
}

void Game::startfloor(string file) {
    layout = file;
    f = new Floor();
    f->setpc(pc);
    f->init(file);
    pc->addaction("Player character has spawned. ");
    if(dlc) {
    } else {
    }
}

static void changecom(string& com, int& dc) {
    if(dc == 's') {
        com = "so";
    } else if(dc == 'a') {
        com = "we";
    } else if(dc == 'w') {
        com = "no";
    } else if(dc == 'd') {
        com = "ea";
    }
}

void Game::play() {
    if(dlc) {
        initscr();
        cbreak();
        noecho();
        clear();
        f->display();
        int dc;
        while(dc = getch()) {
            string com = "";
            if(dc == 'w' || dc == 's' || dc == 'a' || dc == 'd') {
                clear();
                changecom(com,dc);
                f->Playerwalk(com);
            } else if(dc == 'u') {
                int dir = getch();
                clear();
                changecom(com,dir);
                f->usePotion(com);
            } else if(dc == 'z') {
                int dir = getch();
                clear();
                changecom(com,dir);
                f->pcattack(com);
            } else if(dc == 'n') {
                dlc = false;
                endwin();
                pc->addaction("you stop the dlc");
                play();
            } else if(dc == 'b') {
                int dir = getch();
                clear();
                changecom(com,dir);
                f->buy(com);
            } else if(dc == 'f') {
               f->stopmove();
                 pc->addaction("You stop or resume the enemies. ");
            } else if(dc == 'r') {
                reset();    // break;
            } else if(dc == 'q') {
                clear();
                addstr("Player admit to defeat and exit the game\n");
                getch();
                return;
            } else {
                continue;
            }
            if(pc->getrace() == "Troll") {
                pc->sethp(5);
            }
            if(f->getsuccess()) {
                pc->tobasic();
                if(Floor::getfloor() == 5) {
                    addstr("your score is ");
                    printw("%d",calscor());
                    addstr("\nyou have success this game! restart the game ? (Y: yes) \n");
                    int t = getch();
                    if(t == 'Y' || t == 'y') {
                        reset();
                    } else {return;}
                } else {
                    // cout << "true " << endl;
                    nextfloor();
                }
            }
            if(f->fail()) {
                f->display();
                clear();
                addstr("your score is ");
                printw("%d",calscor());
                addstr("\nrestart the game ?  (Y: yes) \n");
                int y = getch();
                if(y == 'Y' || y == 'y') {
                    reset();
                }
                return;
            }
            f->display();
        }
    }else {
        cout << (*f);
        cout << endl;
        string com = "";
        while(cin >> com) {
            if(com == "no" || com == "so" || com == "ea" || com == "we" || com == "ne" ||
                    com == "nw" || com == "se" || com == "sw") {
                f->Playerwalk(com);
            } else if(com == "u") {
                string dir = "";
                cin >> dir;
                f->usePotion(dir);
            } else if(com == "a") {
                string dir = "";
                cin >> dir;
                f->pcattack(dir);
            } else if(com == "f") {
                f->stopmove();
                pc->addaction("You stop or resume the enemies. ");
            } else if(com == "n") {
                dlc = true;
                pc->addaction("You open the dlc. ");
                play();
            } else if(com == "r") {
                break;
            } else if(com == "q") {
                cout << "Player admit to defeat and exit the game" << endl;
                return;
            } else {
                continue;
            }
            if(pc->getrace() == "Troll") {
                pc->sethp(5);
            }
            if(f->getsuccess()) {
                pc->tobasic();
                if(Floor::getfloor() == 5) {
                    cout << "your score is " << calscor() << endl;
                    cout << "you have success this game! restart the game ? (Y: yes) " << endl;
                    string c;
                    cin >> c;
                    if(c == "Y" || c == "y") {
                        reset();
                    } else {return;}
                } else {
                    nextfloor();
                }
            }
            if(f->fail()) {
                cout << (*f) << endl;
                cout << "your score is " << calscor() << endl;
                cout << "restart the game ?  (Y: yes) " << endl;
                string c;
                cin >> c;
                if(c == "Y" || c == "y") {
                    reset();
                }
                return;
            }
            cout << (*f) << endl;
        }
        if(com == "r") reset();
    }
}




void Game::reset() {
    delete f;
    delete pc;
    endwin();
    Floor::setfloor();
    Merchant::tobefriend();
    Potion::clearpotion();
    choose();
    startfloor(layout);
    play();
}

void Game::nextfloor() {
    bool stop = f->getstop();
    delete f;
    startfloor(layout);
    if(stop) {
        f->stopmove();
    }
    pc->tobasic();
    play();
}


Game::~Game() {
    endwin();
    delete f;
    delete pc;
}


