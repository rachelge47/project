#pragma once
#include <SFML/Graphics.hpp>


class GameObject {
public:
	GameObject(const sf::Vector2f & position);
	void fillTexturVector();
	virtual void draw(sf::RenderWindow& window,  sf:: Texture& texture) const ;
	int getSize() {return m_size;}

private:
	sf::Vector2f m_position;
	int m_size;
	std::vector <sf::Texture> m_textures;
	std::string m_names[7] = { "Wall", "Door", "Key", "Present", "Cheese", "Mouse","Cat" };
};

