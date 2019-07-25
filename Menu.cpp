#include "pch.h"
#include "Menu.h"


Menu::Menu()
{
}


Menu::Menu(float width, float height)
{
	this->width = width;
	this->height = height;
}

Menu::Menu(float width, float height, int n)
{
	this->width = width;
	this->height = height;
	this->maxTotalItems = n;
	this->menu.resize(n);
}

Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow & window, Board & board)
{
	for (auto i = 0; i < maxTotalItems; i++) {
		window.draw(menu[i]);
	}
	board.draw(window); // TO DO: multithreading
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0) {
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < maxTotalItems) {
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::setMainMenu()
{
	if (!font.loadFromFile("arial.ttf")) {

	}

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Load Pattern");
	menu[0].setPosition(width - 250, 25);
	menu[0].setCharacterSize(25);

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Start");
	menu[1].setPosition(width - 250, 75);
	menu[1].setCharacterSize(25);

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Pause");
	menu[2].setPosition(width - 250, 125);
	menu[2].setCharacterSize(25);

	menu[3].setFont(font);
	menu[3].setFillColor(sf::Color::White);
	menu[3].setString("Next Gen");
	menu[3].setPosition(width - 250, 175);
	menu[3].setCharacterSize(25);

	menu[4].setFont(font);
	menu[4].setFillColor(sf::Color::White);
	menu[4].setString("Prev Gen");
	menu[4].setPosition(width - 250, 225);
	menu[4].setCharacterSize(25);

	menu[5].setFont(font);
	menu[5].setFillColor(sf::Color::White);
	menu[5].setString("Clear Board");
	menu[5].setPosition(width - 250, 275);
	menu[5].setCharacterSize(25);

	menu[6].setFont(font);
	menu[6].setFillColor(sf::Color::White);
	menu[6].setString("Exit");
	menu[6].setPosition(width - 250, 325);
	menu[6].setCharacterSize(25);

	selectedItemIndex = 0;
}

void Menu::setPatternMenu()
{
	if (!font.loadFromFile("arial.ttf")) {

	}

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("back");
	menu[0].setPosition(width - 250, 25);
	menu[0].setCharacterSize(25);

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Glider");
	menu[1].setPosition(width - 250, 75);
	menu[1].setCharacterSize(25);

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Gosper glider gun");
	menu[2].setPosition(width - 250, 125);
	menu[2].setCharacterSize(25);

	menu[3].setFont(font);
	menu[3].setFillColor(sf::Color::White);
	menu[3].setString("Copperhead");
	menu[3].setPosition(width - 250, 175);
	menu[3].setCharacterSize(25);

	menu[4].setFont(font);
	menu[4].setFillColor(sf::Color::White);
	menu[4].setString("Queen bee shuttle");
	menu[4].setPosition(width - 250, 225);
	menu[4].setCharacterSize(25);

	selectedItemIndex = 0;
}
