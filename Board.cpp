#include "pch.h"
#include "Board.h"


Board::Board()
{
	this->boardWidth = 500 / SIZE_OF_CELL;
	this->boardHeight = 500 / SIZE_OF_CELL;
	init();
	generationsSaved = 0;
}

Board::Board(int &w, int &h)
{
	loadDimensions(w, h);
	init();
	//randomPattern();
	generationsSaved = 0;
}

Board::Board(std::string s)
{
}


Board::~Board()
{
}

void Board::init()
{
	cellBoard.resize(this->boardWidth);
	for (auto i = 0; i < this->boardWidth; i++) {
		cellBoard[i].resize(this->boardHeight);
	}

	for (auto x = 0; x < boardWidth; x++) {
		for (auto y = 0; y < boardHeight; y++) {			
				cellBoard[x][y].setNextState(false);	
				cellBoard[x][y].setState(false);
		}
	}

	field.resize(this->boardWidth);
	for (auto i = 0; i < this->boardWidth; i++) {
		field[i].resize(this->boardHeight);
	}
}

void Board::randomPattern()
{
	auto gen = std::bind(std::uniform_int_distribution<>(0, 1), std::default_random_engine());
	for (auto x = 0; x < boardWidth; x++) {
		for (auto y = 0; y < boardHeight; y++) {
			if (gen() == 1)
				cellBoard[x][y].setState(true);
			else
				cellBoard[x][y].setState(false);
		}
	}
}

void Board::clearBoard()
{
	for (auto x = 0; x < boardWidth; x++) {
		for (auto y = 0; y < boardHeight; y++) {
			cellBoard[x][y].setNextState(false);
			cellBoard[x][y].setState(false);
		}
	}
}

void Board::countNeighbours()
{
	int counter;
	int top, bottom, left, right;

	for (auto x = 0; x < boardWidth; x++) {
		for (auto y = 0; y < boardHeight; y++) {
			counter = 0;

			if (x == 0) left = boardWidth - 1;
			else left = x - 1;

			if (y == 0) top = boardHeight - 1;
			else top = y - 1;

			if (x == boardWidth - 1) right = 0;
			else right = x + 1;

			if (y == boardHeight - 1) bottom = 0;
			else bottom = y + 1;

			if (cellBoard[left][top].isAlive()) counter++;
			if (cellBoard[x][top].isAlive()) counter++;
			if (cellBoard[right][top].isAlive()) counter++;
			if (cellBoard[left][y].isAlive()) counter++;
			if (cellBoard[right][y].isAlive()) counter++;
			if (cellBoard[left][bottom].isAlive()) counter++;
			if (cellBoard[x][bottom].isAlive()) counter++;
			if (cellBoard[right][bottom].isAlive()) counter++;

			cellBoard[x][y].setNumberOfNeighbours(counter);
		}
	}
}

void Board::letTheGameBegin()
{
	countNeighbours();

	for (auto x = 0; x < boardWidth; x++) {
		for (auto y = 0; y < boardHeight; y++) {

			if (cellBoard[x][y].getCurrentState() == false && cellBoard[x][y].getNumberOfNeighbours() == 3)
				cellBoard[x][y].setState(true);

			else if (cellBoard[x][y].getCurrentState() == true && (cellBoard[x][y].getNumberOfNeighbours() < 2 || cellBoard[x][y].getNumberOfNeighbours() > 3))
				cellBoard[x][y].setState(false);
		}
	}

	//saveMemento();
}

void Board::loadDimensions(int &w, int &h)
{
	std::string line;
	std::fstream file;
	file.open("dim1.txt");
	while (!file.eof()) {
		file >> line;
		w = std::stoi(line);
		file >> line;
		h = std::stoi(line);
	}
	this->boardWidth = w / SIZE_OF_CELL;
	this->boardHeight = h / SIZE_OF_CELL;
	w += 300;
}

void Board::loadPatternToTheBoard(PatternEncoder &pattern)
{
	clearBoard();
	for (auto x = 0; x < pattern.width; x++) {
		for (auto y = 0; y < pattern.height; y++) { 
			cellBoard[x + 10][y + 10].setState(pattern.cellPattern[x][y]);
		}
	}
}

void Board::previousGeneration()
{
	if (generationsSaved > 0) {

		for (auto x = 0; x < this->boardWidth; x++) {
			for (auto y = 0; y < this->boardHeight; y++) {
				cellBoard[x][y].setState(cellBoard[x][y].getMemento());
				cellBoard[x][y].updateState();
			}
		}
		generationsSaved--;
	}
}

void Board::draw(sf::RenderWindow & window)
{
	for (auto x = 0; x < this->boardWidth; x++) {
		for (auto y = 0; y < this->boardHeight; y++) {
			if (this->cellBoard[x][y].isAlive() == true) {
				field[x][y].setFillColor(sf::Color::White);
				field[x][y].setPosition(sf::Vector2f(x * SIZE_OF_CELL, y * SIZE_OF_CELL));
				field[x][y].setSize(sf::Vector2f(SIZE_OF_CELL, SIZE_OF_CELL));
			}
			else {
				field[x][y].setFillColor(sf::Color::Black);
				field[x][y].setPosition(sf::Vector2f(x * SIZE_OF_CELL, y * SIZE_OF_CELL));
				field[x][y].setSize(sf::Vector2f(SIZE_OF_CELL, SIZE_OF_CELL));
			}
			window.draw(field[x][y]);
		}
	}
}

void Board::saveMemento() // for the next generation
{
	for (auto x = 0; x < this->boardWidth; x++) {
		for (auto y = 0; y < this->boardHeight; y++) {
			cellBoard[x][y].addMemento();

			//if (cellBoard[x][y].currentState != cellBoard[x][y].nextState)
				cellBoard[x][y].updateState();
		}
	}
	generationsSaved++;
}

