/*
 * main.cpp
 *
 *  Author: Oktarian
 */

#include "maze.h"
#include <time.h>


int main(){

	srand(clock());

	Maze maze(15, 15);
	cout << endl;
	cout << boolalpha << maze.generateMaze() << endl;
	maze.printMaze(false);

	cout << boolalpha << maze.solveMaze() << endl;
	maze.printMaze(true);


	return 0;
}


