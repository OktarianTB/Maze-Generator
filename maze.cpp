/*
 * maze.cpp
 *
 *  Author: Oktarian
 */

#include "maze.h"

const char wall = '#';
const char space = ' ';
const char solution = 'o';

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

Cell* Stack::getTop() const
{
	if(top == nullptr){
		return nullptr;
	}
	return top->data;
}

int Stack::getLength() const
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

Cell* Stack::getRandom() const
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
	path = new Stack;

	// Start of maze at (0, 0)
	stack->push(&maze[0]);
	nbOfCellsVisited = 1;
	maze[0].visited = true;
	maze[0].explored = true;
	maze[0].isOnPath = true;
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
	if(nbOfCellsVisited == mazeHeight*mazeWidth)
		return true;

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
		selectedNeighbor->visited = true;

		// Relation: neighbor is EAST of current top
		if(stack->getTop()->x < selectedNeighbor->x)
		{
			stack->getTop()->east = true;
			selectedNeighbor->west = true;
		}

		// Relation: neighbor is WEST of current top
		if(stack->getTop()->x > selectedNeighbor->x)
		{
			stack->getTop()->west = true;
			selectedNeighbor->east = true;
		}

		// Relation: neighbor is SOUTH of current top
		if(stack->getTop()->y > selectedNeighbor->y)
		{
			stack->getTop()->north = true;
			selectedNeighbor->south = true;
		}

		// Relation: neighbor is SOUTH of current top
		if(stack->getTop()->y < selectedNeighbor->y)
		{
			stack->getTop()->south = true;
			selectedNeighbor->north = true;
		}


		stack->push(selectedNeighbor);
		nbOfCellsVisited++;
	}
	else
	{
		stack->pop();

		if(stack->isEmpty()) return false;
	}

	return generateMaze();
}


bool Maze::solveMaze()
{
	if(path->getTop() == nullptr)
		path->push(&maze[0]);

	if(path->getTop()->x == mazeWidth-1 && path->getTop()->y == mazeHeight-1)
		return true;

	// Finding whether there is a free neighbor to explore
	Stack neighbors;
	if(path->getTop()->east){
		int index = path->getTop()->index + 1;
		if(!maze[index].explored)
			neighbors.push(&maze[index]);
	}
	if(path->getTop()->west){
		int index = path->getTop()->index - 1;
		if(!maze[index].explored)
			neighbors.push(&maze[index]);
	}

	if(path->getTop()->north){
		int index = path->getTop()->index - mazeWidth;
		if(!maze[index].explored)
			neighbors.push(&maze[index]);
	}

	if(path->getTop()->south){
		int index = path->getTop()->index + mazeWidth;
		if(!maze[index].explored)
			neighbors.push(&maze[index]);
	}

	if(!neighbors.isEmpty())
	{
		Cell* selectedNeighbor = neighbors.getRandom();
		selectedNeighbor->isOnPath = true;
		selectedNeighbor->explored = true;
		path->push(selectedNeighbor);
	}
	else
	{
		path->getTop()->isOnPath = false;
		path->pop();

		if(path->isEmpty()) return false;
	}

	return solveMaze();
}


void printRow(int nb)
{
	for(int i = 0; i < nb; i++)
		cout << wall;
	cout << endl;
}


void Maze::printMaze(bool displayPath) const
{
	printRow(4 * mazeWidth);
	for(int i = 0; i < mazeHeight; i++){
		cout << wall;

		for(int j = 0; j < mazeWidth; j++){
			if(maze[i*mazeWidth + j].east){
				if(maze[i*mazeWidth + j].isOnPath && displayPath)
					cout << solution << solution << solution << solution;
				else
					cout << space << space << space << space;
			}
			else{
				if(j == mazeWidth-1){
					if(maze[i*mazeWidth + j].isOnPath && displayPath)
						cout << solution << solution << wall;
					else
						cout << space << space << wall;
				}
				else{
					if(maze[i*mazeWidth + j].isOnPath && displayPath)
						cout << solution << solution << wall << wall;
					else
						cout << space << space << wall << wall;
				}

			}

		}
		cout << endl;
		cout << wall;

		for(int j = 0; j < mazeWidth; j++){
			if(maze[i*mazeWidth + j].south){
				if(j == mazeWidth-1){
					if(maze[i*mazeWidth + j].isOnPath && displayPath)
						cout << solution << solution << wall;
					else
						cout << space << space << wall;
				}
				else{
					if(maze[i*mazeWidth + j].isOnPath && displayPath)
						cout << solution << solution << wall << wall;
					else
						cout << space << space << wall << wall;
				}
			}
			else{
				if(j == mazeWidth-1)
					cout << wall << wall << wall;
				else
					cout << wall << wall << wall << wall;
			}
		}
		cout << endl;

	}
}







