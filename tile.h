#ifndef TILE_H
#define TILE_H
#include "cell.h"

class Tile: public Cell {
    public:
        Tile(int r, int c); // default ctor
        ~Tile(); // dtor
};

# endif
