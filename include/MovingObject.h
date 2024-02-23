#pragma once
#include "GameObject.h"

class MovingObject : public GameObject {
public:
	using GameObject::GameObject;
	//MovingObject(const sf::Vector2f& position, const sf::Texture& texture) : GameObject(position, texture) {}
	void setDirection(const sf::Vector2f& direction);
	sf::Vector2f getDirection() { return m_direction; }
	virtual void move(const sf::Time& deltaTime);

private:

protected:
	sf::Vector2f m_direction;

};