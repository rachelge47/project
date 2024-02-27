#pragma once
#include "Board.h"
#include "Menu.h"
#include "Cat.h"
#include "Mouse.h"
#include "Data.h"
#include <iostream>


class GameControl {

public:
	GameControl(); 
	void run();
	
	
	void removeCat();
	void freezeCat();
	void saveMouse(const sf::Vector2f& tileSize,const sf::Vector2f &position);
	void addCat(const sf::Vector2f& tileSize,const sf::Vector2f& position);
	void resetMovingPos();


private:
	
	void mainMenu();
	void startGame();
	void helpScreen();
	void exitGame();
	void drawGame();
	int levelRun(std::ifstream& boardFile);
	void makeWindow(bool gameStarted);
	void catsTurn(bool mouseMoved,const sf::Time& deltaTime);
	void drawCats();
	void move(const sf::Keyboard::Key& key, const sf::Time& deltaTime);

	Board m_board;
	Menu m_menu;
	std::unique_ptr<Mouse> m_mouse;
	sf::RenderWindow m_window;
	std::vector <std::unique_ptr <Cat>> m_cats;
	Data m_data;

};