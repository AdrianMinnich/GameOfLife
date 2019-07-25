#pragma once
#include "SFML/Graphics.hpp"
#include "Board.h"
#include "SFML/System.hpp"
#include <thread>
#include <vector>

class Menu
{
private:
	int selectedItemIndex;
	sf::Font font;
	std::vector<sf::Text> menu;
	int maxTotalItems;
	float width, height;
public:
	Menu();
	Menu(float width, float height);
	Menu(float width, float height, int n);
	~Menu();
	void draw(sf::RenderWindow &window, Board &board);
	void MoveUp();
	void MoveDown();
	int getPressedItem() { return selectedItemIndex; }
	void setPressedItem(int n) { selectedItemIndex = n; }
	void setMainMenu();
	void setPatternMenu();
};

