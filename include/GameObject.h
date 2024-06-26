#pragma once
#include <SFML/Graphics.hpp>
#include "Manage.h"

class GameObject {
public:
	GameObject(const sf::Vector2f& tileSize, const sf::Vector2f & position, const sf::Texture *texture);
	void draw(sf::RenderWindow& window) const;
	int getSize() const {return m_size;}
	sf::Vector2f getPosition() const { return m_object.getPosition(); }
	void setPosition(const sf::Vector2f& position) { m_object.setPosition(position); }
	sf::Vector2f getInitPos() const { return m_initPos; }
	void setInitPos(const sf::Vector2f& position) { m_initPos = position; }
	void setSize(const sf::Vector2f& size) { m_object.setSize(size); }
	sf::FloatRect getGlobalBounds() const;
	virtual ~GameObject()= default;

private:
	int m_size;

protected:
	sf::RectangleShape m_object;
	sf::Vector2f m_initPos;

};

