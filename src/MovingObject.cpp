#include "MovingObject.h"


MovingObject::MovingObject(const sf::Vector2f& tileSize, const sf::Vector2f& position, const sf::Texture* texture, float speedPerSecond)
	: GameObject(tileSize, position, texture) , m_resetLoc(false), m_speedPerSecond(speedPerSecond)
{}

void MovingObject::setDirection(const sf::Vector2f& direction)
{
	m_direction = direction;
}


void MovingObject:: setScale()
{

	if (m_direction == LEFT)
	{
		m_object.setScale(-1, 1);
	}
	else if (m_direction == RIGHT)
	{
		m_object.setScale(1, 1);
	}
}

void MovingObject::move(float time)
{
	m_object.move(m_speedPerSecond * m_direction * time);  //speed*float
}
