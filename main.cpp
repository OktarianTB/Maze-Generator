/*
 * main.cpp
 *
 *  Author: Oktarian
 */

#include "maze.h"
#include <time.h>


int main(){

	srand(clock());

	int sizeX, sizeY;
	cout << "Enter the dimensions of the maze (width & height): ";
	cin >> sizeX >> sizeY;
	cout << endl;

	Maze maze(sizeX, sizeY);
	maze.generateMaze();
	maze.printMaze(false);

	int entranceX, entranceY, exitX, exitY;
	cout << endl << "Enter the entrance coordinates (X: 0-" << sizeX-1
			<< " & Y: 0-" << sizeY-1 << "): ";
	cin >> entranceX >> entranceY;
	maze.setEntrance(entranceX, entranceY);

	cout << "Enter the exit coordinates (X: 0-" << sizeX-1
			<< " & Y: 0-" << sizeY-1 << "): ";
	cin >> exitX >> exitY;
	maze.setExit(exitX, exitY);

	cout << endl;

	maze.solveMaze();
	maze.printMaze(true);


	return 0;
}


