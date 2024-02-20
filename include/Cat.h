#pragma once
#include "MovingObject.h"

class Cat :public MovingObject {
public:
	using MovingObject::MovingObject;
	//Cat(const sf::Vector2f& position, const sf::Texture& texture) : MovingObject(position, texture) {}
	virtual void move(const sf::Time& deltaTime) {}


private:
};