#include "GameObject.h"

GameObject::GameObject(const sf::Vector2f& position)
	:m_position(position), m_size(60)
{
	fillTexturVector();
}

void GameObject::fillTexturVector()
{
	for (int i=0; i<m_names->size(); i++)
	{
		sf::Texture texture;
		texture.loadFromFile(m_names[i] + ".png");
		m_textures.push_back(texture);
	}
}
	
void GameObject::draw(sf::RenderWindow& window,  sf::Texture& texture) const
{
		sf::RectangleShape shape;
		shape.setTexture(&texture);
		window.draw(shape);
}
