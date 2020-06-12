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
	bool visited;
};

struct LinkedCell
{
	int test;
	Cell* data;
	LinkedCell* next;

	LinkedCell(){
		test = 0;
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
	bool isEmpty() const;
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

	void printMaze() const;



};
