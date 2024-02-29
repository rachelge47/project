#pragma once
#include "MovingObject.h"
#include <iterator>

class Cat :public MovingObject {
public:

	Cat(const sf::Vector2f& tileSize, const sf::Vector2f& position, const sf::Texture * texture) : MovingObject(tileSize, position, texture, 120.f) {}

	sf::Vector2f catMovment(const sf::Vector2f& mouseLoc);
	static void catNeedToDie() { m_catDead = true; }
	static bool isCatDead() { return m_catDead; }
	static void setDead() { m_catDead = false; }
	static bool isFrozen()  { return m_cantMove; }
	static void needFreeze(bool toFreeze) { m_cantMove = toFreeze; }
	void makeBlue(bool stillFrozen);


private:
	double distance(const sf::Vector2f& v1, const sf::Vector2f& v2);
	static bool m_cantMove;
	static bool m_catDead;

};