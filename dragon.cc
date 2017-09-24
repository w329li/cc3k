#include "dragon.h"
using namespace std;


Dragon::Dragon():Enemy(150,20,20,"Dragon","D"){}

Dragon::~Dragon(){}

int Dragon::dropgold(){
    return 5;// just to tell main.cc it is a dragon
}
