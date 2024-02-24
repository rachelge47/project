#include "Mouse.h"

Mouse::Mouse(const sf::Vector2f& tileSize, const sf::Vector2f& position, const sf::Texture* texture)
	: MovingObject(tileSize, position, texture), m_score(0), m_life(0)
{}

