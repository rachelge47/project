#pragma once
#include "MovingObject.h"
#include <iterator>

class Cat :public MovingObject {
public:
	using MovingObject::MovingObject;
	//Cat(const sf::Vector2f& position, const sf::Texture& texture) : MovingObject(position, texture) {}
	//virtual void move(const sf::Time& deltaTime) {}

	sf::Vector2f catMovment(const sf::Vector2f& mouseLoc);
	static void catNeedToDie() { m_catDead = true; }
	static bool isCatDead() { return m_catDead; }
	static void setDead() { m_catDead = false; }
	bool isFrozen() const { return m_isFrozen; }



private:
	double distance(const sf::Vector2f& v1, const sf::Vector2f& v2);
	bool m_canMove = false;
	static bool m_catDead;
	sf::Clock freezeTimer;
	bool m_isFrozen;

};