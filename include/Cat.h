#pragma once
#include "MovingObject.h"
#include <iterator>

class Cat :public MovingObject {
public:
	using MovingObject::MovingObject;
	//Cat(const sf::Vector2f& position, const sf::Texture& texture) : MovingObject(position, texture) {}
	//virtual void move(const sf::Time& deltaTime) {}

	sf::Vector2f catMovment(const sf::Vector2f& mouseLoc);



private:
	double distance(const sf::Vector2f& v1, const sf::Vector2f& v2);

};