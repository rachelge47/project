#include "MovingObject.h"


MovingObject::MovingObject(const sf::Vector2f& tileSize, const sf::Vector2f& position, const sf::Texture* texture, float speedPerSecond)
	: GameObject(tileSize, position, texture) , m_initPos (position), m_resetLoc(false), m_speedPerSecond(speedPerSecond)
{}

void MovingObject::setDirection(const sf::Vector2f& direction)
{
	m_direction = direction;
}

//void MovingObject::move(const sf::Time& deltaTime)
//{
//	m_object.move(m_direction * m_speedPerSecond * deltaTime.asSeconds());  //speed*float
//}


void MovingObject::move(float time)
{
	m_object.move(m_direction * m_speedPerSecond * time);  //speed*float
}
