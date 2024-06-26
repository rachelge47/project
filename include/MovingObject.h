#pragma once
#include "GameObject.h"

class MovingObject : public GameObject {
public:
	
	MovingObject(const sf::Vector2f& tileSize, const sf::Vector2f& position, const sf::Texture * texture, float speedPerSecond);
	void setDirection(const sf::Vector2f& direction);
	void setPos();
	sf::Vector2f getLoc() const;
	sf::Vector2f getDirection() const { return m_direction; }
	void setScale();
	void move(float time);
	bool isMouseEaten() const { return m_resetLoc; }
	void mouseGotEaten(bool toReset) { m_resetLoc = toReset; } //recive true if need to reset
	void isIntersects(bool isIn) { m_inter = isIn; }

private:
	float m_speedPerSecond;
	bool m_inter;

protected:
	sf::Vector2f m_direction;
	bool m_resetLoc;
	sf::Vector2f m_prevPos;
	
};