#pragma once
#include "MovingObject.h"

class Mouse :public MovingObject {
public:
	//using MovingObject::MovingObject;

	Mouse(const sf::Vector2f& tileSize, const sf::Vector2f& position, const sf::Texture* texture);
	void addPoints(int toAdd) {m_score += toAdd; }

private:
	int m_score;
};