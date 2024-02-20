#pragma once
#include "GameObject.h"

class StillObject : public GameObject{
public:
	using GameObject::GameObject;
	//StillObject(const sf::Vector2f& position, const sf::Texture& texture) : GameObject(position, texture) {}

private:
};

class Wall : public StillObject {
public:
	using StillObject::StillObject;
	//Wall(const sf::Vector2f& position, const sf::Texture& texture) : StillObject(position, texture) {};

};

class Door : public StillObject {
public:
	using StillObject::StillObject;
	//Door(const sf::Vector2f& position, const sf::Texture& texture) : StillObject(position, texture) {};

};

class Present : public StillObject {
public:
	using StillObject::StillObject;
	//Present(const sf::Vector2f& position, const sf::Texture& texture) : StillObject(position, texture) {};

};

class Key : public StillObject {
public:
	using StillObject::StillObject;
	//Key(const sf::Vector2f& position, const sf::Texture& texture) : StillObject(position, texture) {};

};

class Cheese : public StillObject {
public:
	using StillObject::StillObject;
	//Cheese(const sf::Vector2f& position, const sf::Texture& texture) : StillObject(position, texture) {};

};