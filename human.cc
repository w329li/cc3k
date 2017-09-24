#include "human.h"
using namespace std;
Human::Human():Enemy(140,20,20,"Human","H"){}

Human::~Human(){}

int Human::dropgold(){
  return 3;
}
