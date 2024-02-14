#pragma once
#include "Board.h"
#include "Menu.h"
#include "Cat.h"


const int NUMOFLEVELS = 3;
const int WIDTH = 1300;
const int LENGTH = 800;

class GameControl {

public:

	GameControl();
	void run();
	void levelRun();

	void makeWindow();

private:

	Board m_board;
	Menu m_menu;
	sf::RenderWindow m_window;
//	std::vector <Cat> m_cats;

};