#include "MovingObject.h"


MovingObject::MovingObject(const sf::Vector2f& tileSize, const sf::Vector2f& position, const sf::Texture* texture)
	: GameObject(tileSize, position, texture) , m_initPos (position), m_resetLoc(false)
{}

void MovingObject::setDirection(const sf::Vector2f& direction)
{
	m_direction = direction;
}

void MovingObject::move(const sf::Time& deltaTime)
{
	float speedPerSecond;

	if (m_object.getTexture() == Manage::getTexture(O_MOUSE))
	{
		speedPerSecond = 200.f;
	}

	else
	{
		speedPerSecond = 90.f;
	}

	m_object.move(m_direction * speedPerSecond * deltaTime.asSeconds());
}
