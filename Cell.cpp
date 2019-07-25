#include "pch.h"
#include "Cell.h"


void Cell::setState(bool s)
{
	this->currentState = s;
}

void Cell::setNextState(bool s)
{
	this->nextState = s;
}

bool Cell::isAlive()
{
	if (currentState)
		return true;
	else
		return false;
}

int Cell::getNumberOfNeighbours()
{
	return numberOfNeighbours;
}

void Cell::setNumberOfNeighbours(int n)
{
	numberOfNeighbours = n;
}

void Cell::addMemento()
{
	this->memento.push_front(this->currentState);
	if (this->memento.size() > MAX_MEMENTO_SIZE)
		this->memento.pop_back();
}

bool Cell::getMemento()
{
	bool state = this->memento.front();
	this->memento.pop_front();
	return state;
}

void Cell::updateState()
{
	currentState = nextState;
}

Cell::Cell()
{
}


Cell::~Cell()
{
}
