#pragma once
#include "GameObject.h"

class StillObject : public GameObject{
public:
	using GameObject::GameObject;
	//StillObject(const sf::Vector2f& position, const sf::Texture& texture) : GameObject(position, texture) {}
	void gotEaten() { m_beenEaten = true; }
	bool beenEaten() { return m_beenEaten; }

	//int getInitKeyCount() { return m_initKeyCount; }
	//void setInitKeyCount(int count) { m_initKeyCount = count; }
	//void setKeyCount(int toAdd) { m_keyCount += toAdd; }
	//int getKeyCount() { return m_keyCount; }

	//int getInitCheeseCount() { return m_initCheeseCount; }
	//void setInitCheeseCount(int count) { m_initCheeseCount = count; }
	//void setCheeseCount(int toAdd) { m_cheeseCount += toAdd; }
	//int getCheeseCount() { return m_cheeseCount; }


private:
	bool m_beenEaten=false;
	/*int m_initKeyCount=0;
	int m_keyCount=0;
	int m_initCheeseCount=0;
	int m_cheeseCount=0;*/

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