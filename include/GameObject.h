#pragma once
#include <SFML/Graphics.hpp>
#include "Manage.h"

class GameObject {
public:
	GameObject(const sf::Vector2f & position, const sf::Texture& texture);
	virtual void draw(sf::RenderWindow& window) const ;
	int getSize() {return m_size;}

private:
	sf::Vector2f m_position;
	int m_size;
	sf::Texture m_texture;

};

