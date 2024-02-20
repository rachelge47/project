#include "MovingObject.h"

void MovingObject::setDirection(const sf::Vector2f& direction)
{
	m_direction = direction;
}

void MovingObject::move(const sf::Time& deltaTime)
{
	const auto speedPerSecond =80.f;
	m_object.move(m_direction * speedPerSecond * deltaTime.asSeconds());
}
