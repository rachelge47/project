#pragma once
#include "Board.h"
#include "Menu.h"
#include "Cat.h"
#include "Mouse.h"
#include "Data.h"
#include "Macros.h"
#include <iostream>
#include <string>



class GameControl {

public:
	GameControl(); 
	void run();
	void removeCat();
	void saveMouse(const sf::Vector2f& tileSize,const sf::Vector2f &position);
	void addCat(const sf::Vector2f& tileSize,const sf::Vector2f& position);
	void resetMovingPos();
	void makeCatBlue(bool stillFrozen);

private:
	//------functions-----

	void mainMenu();
	void startGame();
	bool shouldContinueGame();
	bool shouldEndGame();
	void setupNextLevel(std::ifstream& boardFile);
	void handleEndGame();
	void displayEndScreen( int textureKey);
	void helpScreen();
	void exitGame();
	void drawGame();
	int levelRun(std::ifstream& boardFile);
	void resetBoardAfterTimeOut(std::ifstream& boardFile);
	void catsTurn(bool mouseMoved,const sf::Time& deltaTime);
	void drawCats();
	void setDirection(const sf::Keyboard::Key& key);

	//------members-----
	Board m_board;
	Menu m_menu;
	std::unique_ptr<Mouse> m_mouse;
	sf::RenderWindow m_window;
	std::vector <std::unique_ptr <Cat>> m_cats;
	Data m_data;
	int m_numOfLevels;

};