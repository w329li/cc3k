#ifndef WALL_H
#define WALL_H
#include "cell.h"

class Wall: public Cell {
    public:
        Wall(std::string symbol,int r, int c);// default ctor
        ~Wall();



};

# endif
