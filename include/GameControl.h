#pragma once
#include "Board.h"
#include "Menu.h"
#include "Cat.h"
#include "Mouse.h"

const int NUMOFLEVELS = 3;
//const int WIDTH = 1300;
//const int LENGTH = 800;

class GameControl {

public:

	void run();
	void levelRun();
	void makeWindow();
	static GameControl* getInstance();
	void helpScreen();
	void exitGame();
	void newGame();
	void cover();
	void saveMouse(const sf::Vector2f position);
	~GameControl() { delete m_instance; }

private:
	GameControl(); // single tone
	static GameControl* m_instance; //single tone
	Board m_board;
	Menu m_menu;
	Mouse m_mouse;
	sf::RenderWindow m_window;
//	std::vector <Cat> m_cats;

};