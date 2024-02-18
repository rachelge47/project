#pragma once
#include "MovingObject.h"

class Mouse :public MovingObject {
public:
	Mouse(const sf::Vector2f& position, const sf::Texture& texture) : MovingObject(position, texture) {}


private:
};