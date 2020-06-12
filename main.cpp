/*
 * main.cpp
 *
 *  Author: Oktarian
 */

#include "maze.h"
#include <time.h>


int main(){

	srand(clock());

	Maze maze(4, 4);
	maze.printMaze();


	return 0;
}


