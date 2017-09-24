#ifndef PASS_H
#define PASS_H
#include "cell.h"

class Pass: public Cell {
    public:
        Pass(std::string symbol,int r, int c);// default ctor
        ~Pass(); // dtor

};

# endif
