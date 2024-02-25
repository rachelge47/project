#pragma once
#include "Board.h"

class GameControl;

class Data {
public:

	void printData(sf::RenderWindow& window);


private:
	sf::Clock m_timer;
	sf::Time m_stageTime;
	sf::RectangleShape m_info;


};