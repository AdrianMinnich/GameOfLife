#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <memory>
#include <functional>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "Cell.h"
#include "PatternEncoder.h"

#define SIZE_OF_CELL 8

class Board
{
public:
	int boardWidth;
	int boardHeight;
	int generationsSaved;
	std::vector<std::vector<Cell>> cellBoard;
	std::vector<PatternEncoder> patterns;
	std::vector<std::vector<sf::RectangleShape>> field;

	Board();
	Board(int &w, int &h);
	Board(std::string s);
	~Board();
	void init();
	void randomPattern();
	void clearBoard();
	void countNeighbours();
	void letTheGameBegin();
	void loadDimensions(int &w, int &h); // square only
	void loadPatternToTheBoard(PatternEncoder &pattern);
	void previousGeneration();
	void draw(sf::RenderWindow &window);
	void saveMemento();
};

