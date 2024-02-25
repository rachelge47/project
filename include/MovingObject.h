#pragma once
#include "GameObject.h"

class MovingObject : public GameObject {
public:
	
	MovingObject(const sf::Vector2f& tileSize, const sf::Vector2f& position, const sf::Texture * texture);
	void setDirection(const sf::Vector2f& direction);
	sf::Vector2f getDirection() { return m_direction; }
	virtual void move(const sf::Time& deltaTime);
	bool isMouseEaten() { return m_resetLoc; }
	//void setInitPos(sf::Vector2f position) { m_initPos = position; }
	sf::Vector2f getInitPos() { return m_initPos; }
	void mouseGotEaten(bool toReset) { m_resetLoc = toReset; } //recive true if need to reset

private:

protected:
	sf::Vector2f m_direction;
	sf::Vector2f m_initPos;
	bool m_resetLoc;
	
};