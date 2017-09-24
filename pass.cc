#include <iostream>
#include "pass.h"

using namespace std;

Pass::Pass(string symbol, int r, int c)
  :Cell(symbol, true, r, c) {}

Pass::~Pass() {}
