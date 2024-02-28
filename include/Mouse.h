#pragma once
#include "MovingObject.h"

class Mouse :public MovingObject {
public:

	Mouse(const sf::Vector2f& tileSize, const sf::Vector2f& position, const sf::Texture* texture);
	void printMouseData(sf::RenderWindow& window);
	void addPoints(int toAdd) {m_score += toAdd; }
	void addLife(int toAdd) {m_life += toAdd; }
	int getLife() { return m_life; }

private:
	//------functions------
	sf::Text make(const std::string& str, const sf::Font* font, float down);

	//------members------
	int m_score;
	int m_life;
};