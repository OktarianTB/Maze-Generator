/*
 * maze.cpp
 *
 *  Author: Oktarian
 */

#include "maze.h"

const char fence = 'x';

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

bool Stack::isEmpty() const
{
	return top == nullptr ? true : false;
}

Cell* Stack::getTop()
{
	return top->data;
}

int Stack::getLength()
{
	if(top == nullptr) return 0;

	int length = 0;
	LinkedCell* current = top;

	while(current != nullptr){
		current = current->next;
		length++;
	}

	return length;
}

Cell* Stack::getRandom()
{
	int length = getLength();
	int index = rand() % length;
	LinkedCell* current = top;

	while(index != 0){
		current = current->next;
		index--;
	}

	return current->data;
}


Maze::Maze(int width, int height)
{
	mazeWidth = width;
	mazeHeight = height;
	maze = new Cell[mazeHeight*mazeWidth];

	for(int i = 0; i < mazeHeight; i++){
		for(int j = 0; j < mazeWidth; j++){
			maze[i*mazeWidth + j].x = j;
			maze[i*mazeWidth + j].y = i;
			maze[i*mazeWidth + j].index = i*mazeWidth + j;
		}
	}

	stack = new Stack;

	// Start of maze at (0, 0)
	stack->push(&maze[0]);
	nbOfCellsVisited = 1;
	maze[0].visited = true;

}

Maze::~Maze()
{
	delete stack;
	stack = nullptr;

	delete [] maze;
	delete maze;
	maze =  nullptr;
}


bool Maze::generateMaze()
{
	if(nbOfCellsVisited == mazeHeight*mazeWidth) return true;

	Stack neighbors;

	// Check for WEST neighbor
	if(stack->getTop()->x > 0)
	{
		int index = stack->getTop()->index -1;
		if(maze[index].visited == false)
			neighbors.push(&maze[index]);
	}

	// Check for EAST neighbor
	if(stack->getTop()->x < mazeWidth-1)
	{
		int index = stack->getTop()->index + 1;
		if(maze[index].visited == false)
			neighbors.push(&maze[index]);
	}

	// Check for NORTH neighbor
	if(stack->getTop()->y > 0)
	{
		int index = stack->getTop()->index - mazeWidth;
		if(maze[index].visited == false)
			neighbors.push(&maze[index]);
	}

	// Check for SOUTH neighbor
	if(stack->getTop()->y < mazeHeight-1)
	{
		int index = stack->getTop()->index + mazeWidth;
		if(maze[index].visited == false)
			neighbors.push(&maze[index]);
	}

	if(!neighbors.isEmpty())
	{
		Cell* selectedNeighbor = neighbors.getRandom();
		maze[selectedNeighbor->index].visited = true;

		// Relation: neighbor is EAST of current top
		if(stack->getTop()->x < selectedNeighbor->x)
		{
			stack->getTop()->east = true;
			maze[selectedNeighbor->index].west = true;
		}

		// Relation: neighbor is WEST of current top
		if(stack->getTop()->x > selectedNeighbor->x)
		{
			stack->getTop()->west = true;
			maze[selectedNeighbor->index].east = true;
		}

		// Relation: neighbor is SOUTH of current top
		if(stack->getTop()->y > selectedNeighbor->y)
		{
			stack->getTop()->north = true;
			maze[selectedNeighbor->index].south = true;
		}

		// Relation: neighbor is SOUTH of current top
		if(stack->getTop()->y < selectedNeighbor->y)
		{
			stack->getTop()->south = true;
			maze[selectedNeighbor->index].north = true;
		}


		stack->push(&maze[selectedNeighbor->index]);
		nbOfCellsVisited++;
	}
	else
	{
		stack->pop();

		if(stack->isEmpty()) return false;
	}

	return generateMaze();
}


void printRow(int nb){
	for(int i = 0; i < nb; i++)
		cout << fence;
	cout << endl;
}


void Maze::printMaze() const
{
	printRow(2 * mazeWidth + 1);
	for(int i = 0; i < mazeHeight; i++){
		cout << fence;

		for(int j = 0; j < mazeWidth; j++){
			if(maze[i*mazeWidth + j].east)
				cout << "  ";
			else
				cout << " " << fence;
		}
		cout << endl;
		cout << fence;
		for(int j = 0; j < mazeWidth; j++){
			if(maze[i*mazeWidth + j].south)
				cout << " " << fence;
			else
				cout << fence << fence;
		}
		cout << endl;

	}
}







