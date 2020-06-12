/*
 * maze.cpp
 *
 *  Author: Oktarian
 */

#include "maze.h"

Stack::Stack()
{
	top = nullptr;
}

Stack::~Stack()
{
	while(!isEmpty()){
		pop();
	}
}

void Stack::push(Cell* cell)
{
	LinkedCell* newTop = new LinkedCell;
	newTop->test = 2;
	newTop->next = top;
	newTop->data = cell;
	top = newTop;
}

void Stack::pop()
{
	if(isEmpty()) return;

	LinkedCell* currentTop = top;
	top = top->next;

	delete currentTop;
	currentTop = nullptr;
}

bool Stack::isEmpty() const{
	return top == nullptr ? true : false;
}


Maze::Maze(int width, int height)
{
	mazeWidth = width;
	mazeHeight = height;
	maze = new Cell[mazeHeight*mazeWidth];

	for(int i = 0; i < mazeHeight; i++){
		for(int j = 0; j < mazeWidth; j++){
			maze[i*mazeWidth + j].visited = false;
			maze[i*mazeWidth + j].x = j;
			maze[i*mazeWidth + j].y = i;
		}
	}

	stack = new Stack;
	// Start of maze at (0, 0)

	stack->push(&maze[0]);
	maze[0].visited = true;
	nbOfCellsVisited = 1;
}

Maze::~Maze()
{
	delete stack;
	stack = nullptr;

	delete [] maze;
	delete maze;
	maze =  nullptr;
}


void printRow(int nb){
	for(int i = 0; i < nb; i++)
		cout << "#";
	cout << endl;
}


void Maze::printMaze() const
{
	for(int i = 0; i < mazeHeight; i++){
		printRow(2 * mazeWidth + 1);

		for(int j = 0; j < mazeWidth; j++){
			cout << "# ";
		}

		cout << "#" << endl;
	}
	printRow(2 * mazeWidth + 1);
}







