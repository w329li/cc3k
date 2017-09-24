#include <iostream>
#include "wall.h"
#include "cell.h"

using namespace std;

Wall::Wall(string symbol, int r, int c)
  :Cell(symbol, false, r, c) {}

Wall::~Wall() {}
