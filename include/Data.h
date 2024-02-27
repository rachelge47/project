#pragma once
#include <SFML/Graphics.hpp>

//#include "Board.h"

class GameControl;

class Data {
public:

	void printData(sf::RenderWindow& window);

	void updateTime(float time);
	bool timeOut() const { return m_isTimeEnd; }
	void restartTime() { m_timer.restart(); }
	void draw(sf::RenderWindow& window);
	sf::Text make(const std::string& str, const sf::Font* font);
	void setTime();
	void setTimeOut() { m_isTimeEnd = false; }
	//
	static void needAddTime() { m_toAddTime = true; }



private:
	sf::Clock m_timer;
	sf::Time m_LevelTime;
	sf::RectangleShape m_info;
	sf::Text m_timeText;
	float m_timeAsSec;
	bool m_isTimeEnd = false;
	static bool m_toAddTime;



};