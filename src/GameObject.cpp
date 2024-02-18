#include "GameObject.h"

GameObject::GameObject(const sf::Vector2f& position, const sf::Texture& texture)
	:m_position(position), m_size(50), m_texture(texture)
{
}


	
void GameObject::draw(sf::RenderWindow& window) const
{
	sf::RectangleShape shape;
	shape.setTexture(&m_texture);
	shape.setPosition(m_position);
	shape.setSize({50,50});
	window.draw(shape);
	//window.display();
}
