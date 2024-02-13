#pragma once
#include "Board.h"
#include "Menu.h"


const int NUMOFLEVELS = 3;

class GameControl {

public:

	void run();

private:

	Board m_board;
	Menu m_menu;
	sf::RenderWindow m_window;

};