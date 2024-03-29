#include "pch.h"
#include <iostream>
#include <SFMl/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Board.h"
#include "Menu.h"
#include "PatternEncoder.h"
#include <thread>

int main() {
	int windowWidth, windowHeight;
	Board board(windowWidth, windowHeight);
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "GameOfLife - Adrian Minnich", sf::Style::Titlebar | sf::Style::Close);
	//window.setFramerateLimit(0);
	window.setVerticalSyncEnabled(false);
	bool isPaused = false;
	int whichMenu = 0; // 0 - main, 1 - pattern
	
	Menu menu(window.getSize().x, window.getSize().y, 7);
	menu.setMainMenu();
	Menu menu2(window.getSize().x, window.getSize().y, 5);
	menu2.setPatternMenu();
	PatternEncoder encoder;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::KeyReleased:
					if (whichMenu == 0) {
						switch (event.key.code) {
						case sf::Keyboard::Up:
							menu.MoveUp();
							break;
						case sf::Keyboard::Down:
							menu.MoveDown();
							break;
						case sf::Keyboard::Enter:
							switch (menu.getPressedItem()) {
							case 0:
								std::cout << "Load Pattern" << std::endl;
								whichMenu = 1;
								break;
							case 1:
								std::cout << "Start" << std::endl;
								isPaused = false;
								break;
							case 2:
								std::cout << "Pause" << std::endl;
								isPaused = true;
								break;
							case 3:
								std::cout << "Next Gen" << std::endl;
								isPaused = true;
								board.letTheGameBegin();
								break;
							case 4:
								std::cout << "Prev Gen" << std::endl;
								isPaused = true;
								board.previousGeneration();
								break;
							case 5:
								std::cout << "Clear Board" << std::endl;
								board.clearBoard();
								break;
							case 6:
								std::cout << "Exit" << std::endl;
								window.close();
							default:
								break;
							}
							break;
						}
					}
					else if (whichMenu == 1) {
						switch (event.key.code) {
						case sf::Keyboard::Up:
							menu2.MoveUp();
							break;
						case sf::Keyboard::Down:
							menu2.MoveDown();
							break;
						case sf::Keyboard::Enter:
							switch (menu2.getPressedItem()) {
							case 0:
								std::cout << "back" << std::endl;
								whichMenu = 0;
								//menu2.setPressedItem(0);
								break;
							case 1:
								board.clearBoard();
								std::cout << "Glider" << std::endl;
								encoder.setFilePath("./patterns/glider.rle");
								board.loadPatternToTheBoard(encoder);
								break;
							case 2:
								board.clearBoard();
								std::cout << "Gosper Glider Gun" << std::endl;
								encoder.setFilePath("./patterns/gosperglidergun.rle");
								board.loadPatternToTheBoard(encoder);
								break;
							case 3:
								board.clearBoard();
								std::cout << "Copperhead" << std::endl;
								encoder.setFilePath("./patterns/copperhead.rle");
								board.loadPatternToTheBoard(encoder);
								break;
							case 4:
								board.clearBoard();
								std::cout << "Queen Bee Shuttle" << std::endl;
								encoder.setFilePath("./patterns/queenbeeshuttle.rle");
								board.loadPatternToTheBoard(encoder);
								break;
							default:
								break;
							}
							break;
						}
					}					
					break;
				case::sf::Event::Closed:
					window.close();
					break;
				default:
					break;
			}
		}
		if (isPaused == false)
			board.letTheGameBegin();

		window.clear();

		if(whichMenu == 0)
			menu.draw(window, board);
		else
			menu2.draw(window, board);

		window.display();
	}

	return 0;
}
