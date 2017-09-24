#include <iostream>
#include <utility>
#include <string>
#include <cstdlib>
#include <ctime>
#include "game.h"
using namespace std;


int main(int argc, char *argv[]) {
    srand(time(NULL));
    Game game;
    game.choose();
 	  if(argc == 1) {
        game.startfloor("cc3kfloorempty.txt");
	  } else {
      string file = argv[1];
        game.startfloor(file);
    }
    game.play();
}


