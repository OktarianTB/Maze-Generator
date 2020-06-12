/*
 * maze.h
 *
 *  Author: Oktarian
 */

#include <iostream>
using namespace std;

struct Cell
{
	int x;
	int y;
	int index;
	bool visited;

	bool north;
	bool south;
	bool east;
	bool west;

	Cell()
	{
		x = 0;
		y = 0;
		index = 0;
		visited = false;
		north = false;
		south = false;
		east = false;
		west = false;
	}
};

struct LinkedCell
{
	Cell* data;
	LinkedCell* next;

	LinkedCell(){
		data = nullptr;
		next = nullptr;
	};
};


class Stack
{
private:
	LinkedCell* top;

public:
	Stack();
	~Stack();

	void push(Cell* cell);
	void pop();
	Cell* getTop();
	bool isEmpty() const;
	Cell* getRandom();
	int getLength();
};


class Maze
{
private:
	int mazeWidth;
	int mazeHeight;

	Cell* maze;
	Stack* stack;
	int nbOfCellsVisited;

public:
	Maze(int width, int height);
	~Maze();

	bool generateMaze();
	void printMaze() const;



};
