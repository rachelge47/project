#pragma once
#include "MovingObject.h"

class Cat :public MovingObject {
public:
	Cat(const sf::Vector2f& position, const sf::Texture& texture) : MovingObject(position, texture) {}


private:
};