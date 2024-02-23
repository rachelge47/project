#pragma once
#include "Board.h"
#include "Menu.h"
#include "Cat.h"
#include "Mouse.h"
#include "Data.h"


const int NUMOFLEVELS = 3;

class GameControl {

public:

	void run();
	static GameControl* getInstance();
	void helpScreen();
	void exitGame();
	void newGame();
	void startGame();
	static int getLevel() { return m_level; }
	//void cover(const sf::RenderWindow& window);
	//void coverStart();
	//void helpcover( sf::RenderWindow& helpWindow);
	void saveMouse(const sf::Vector2f& tileSize,const sf::Vector2f &position);
	void addCat(const sf::Vector2f& tileSize,const sf::Vector2f& position);
	~GameControl() { delete m_instance; }

private:
	GameControl(); // single tone
	void levelRun();
	void makeWindow();
	void drawCats();
	void move(const sf::Keyboard::Key& key, const sf::Time& deltaTime);

	static GameControl* m_instance; //single tone
	Board m_board;
	Menu m_menu;
	std::unique_ptr<Mouse> m_mouse;
	sf::RenderWindow m_window;
	std::vector <std::unique_ptr <Cat>> m_cats;
	Data m_data;
	static int m_level;

};