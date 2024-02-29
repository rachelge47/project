#pragma once
#include "GameObject.h"

class StillObject : public GameObject{
public:
	using GameObject::GameObject;

	void gotEaten() { m_beenEaten = true; }
	bool beenEaten() const { return m_beenEaten; }

private:
	bool m_beenEaten=false;
};

class Wall : public StillObject {
public:
	using StillObject::StillObject;

};

class Door : public StillObject {
public:
	using StillObject::StillObject;
	
};


class Key : public StillObject {
public:
	using StillObject::StillObject;

};

class Cheese : public StillObject {
public:
	using StillObject::StillObject;

};