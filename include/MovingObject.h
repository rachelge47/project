#pragma once
#include "GameObject.h"

class MovingObject : public GameObject {
public:
	//using GameObject::GameObject;
	MovingObject(const sf::Vector2f& position, const sf::Texture& texture) : GameObject(position, texture) {}

private:
};