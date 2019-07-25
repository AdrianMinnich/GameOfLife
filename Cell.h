#pragma once
#include <deque>

#define MAX_MEMENTO_SIZE 50

class Cell
{
private:
	bool currentState;
	bool nextState;
	int numberOfNeighbours;
	std::deque<bool> memento;
public:
	void setState(bool s);
	void setNextState(bool s);
	bool getCurrentState() { return this->currentState; }
	bool isAlive();
	int getNumberOfNeighbours();
	void setNumberOfNeighbours(int n);
	void addMemento();
	bool getMemento();
	void updateState();
	Cell();
	~Cell();
};

