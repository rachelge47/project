#include "GameObject.h"

GameObject::GameObject(const sf::Vector2f& tileSize, const sf::Vector2f& position, const sf::Texture *texture)
	:m_size(50), m_initPos(position)
{
	m_object.setTexture(texture);
	m_object.setPosition(position);
	m_object.setSize(tileSize);
	m_object.setOrigin(m_object.getSize());
}

	
void GameObject::draw(sf::RenderWindow& window) const
{
	window.draw(m_object);
}

sf::FloatRect GameObject::getGlobalBounds() const
{
	return m_object.getGlobalBounds();
}
