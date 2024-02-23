#include "GameObject.h"

GameObject::GameObject(const sf::Vector2f& tileSize, const sf::Vector2f& position, const sf::Texture *texture)
	:m_size(50)
{
	m_object.setTexture(texture);
	m_object.setPosition(position);
	m_object.setSize(tileSize);

	//m_object.setSize({ 50,50 });
	//Manage::getObjSize();

}


	
void GameObject::draw(sf::RenderWindow& window) 
{
	window.draw(m_object);
}

sf::FloatRect GameObject::getGlobalBounds() const
{
	return m_object.getGlobalBounds();
}
