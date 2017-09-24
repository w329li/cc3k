CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -Werror=vla -MMD
EXEC = cc3k
OBJECTS = main.o character.o item.o player.o shade.o drow.o troll.o vampire.o goblin.o enemy.o human.o dwarf.o elf.o orc.o halfling.o merchant.o subject.o gold.o small.o normal.o potion.o cell.o tile.o pass.o wall.o floor.o game.o BA.o BD.o hhoard.o dhoard.o mhoard.o PH.o RH.o WA.o WD.o dragon.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -lncurses -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean


