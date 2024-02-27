#pragma once
#include "GameObject.h"

class MovingObject : public GameObject {
public:
	
	MovingObject(const sf::Vector2f& tileSize, const sf::Vector2f& position, const sf::Texture * texture, float speedPerSecond);
	void setDirection(const sf::Vector2f& direction);
	sf::Vector2f getDirection() { return m_direction; }
	void move(float time); 
	bool isMouseEaten() { return m_resetLoc; }
	void mouseGotEaten(bool toReset) { m_resetLoc = toReset; } //recive true if need to reset

private:
	float m_speedPerSecond;


protected:
	sf::Vector2f m_direction;
	bool m_resetLoc;
	
};