/*
 * main.cpp
 *
 *  Author: Oktarian
 */

#include "maze.h"
#include <time.h>


int main(){

	srand(clock());

	Maze maze(20, 8);
	cout << endl;
	cout << boolalpha << maze.generateMaze() << endl;
	maze.printMaze();


	return 0;
}


