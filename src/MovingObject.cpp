#include "MovingObject.h"


MovingObject::MovingObject(const sf::Vector2f& tileSize, const sf::Vector2f& position, const sf::Texture* texture, float speedPerSecond)
	: GameObject(tileSize, position, texture) , m_resetLoc(false), m_speedPerSecond(speedPerSecond), m_inter(false)
{
	m_object.setOrigin(m_object.getSize() / 2.f);
}

void MovingObject::setDirection(const sf::Vector2f& direction)
{
	
	m_direction = direction;
}

sf::Vector2f MovingObject::getLoc()
{
	return m_object.getPosition();
}

void MovingObject::setPos()
{
	
	m_object.setPosition(m_prevPos);
	
}



void MovingObject:: setScale()
{
	
	if (m_direction == LEFT)
	{
		m_object.setScale(-1, 1);
	}
	if (m_direction == RIGHT)
	{
		m_object.setScale(1, 1);
	}
	
}


void MovingObject::move(float time)
{
	
	m_prevPos = getLoc();

	m_object.move(m_speedPerSecond * m_direction * time);  //speed*float
	
	
}
