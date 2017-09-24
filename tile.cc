#include <iostream>
#include "tile.h"

using namespace std;

Tile::Tile(int r, int c)
  :Cell(".", true, r, c) {}

Tile::~Tile() {}
