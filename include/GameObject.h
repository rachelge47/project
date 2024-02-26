#pragma once
#include <SFML/Graphics.hpp>
#include "Manage.h"

class GameObject {
public:
	GameObject(const sf::Vector2f& tileSize, const sf::Vector2f & position, const sf::Texture *texture);
	void draw(sf::RenderWindow& window);
	int getSize() {return m_size;}  //change
	sf::Vector2f getPosition() const { return m_object.getPosition(); }
	void setPosition(const sf::Vector2f& position) { m_object.setPosition(position); }
	void setSize(const sf::Vector2f& size) { m_object.setSize(size); }
	sf::FloatRect getGlobalBounds() const;
	virtual ~GameObject()= default;

private:
	//sf::Vector2f m_position;
	int m_size;
	//sf::Texture m_texture;

protected:
	sf::RectangleShape m_object;

};

