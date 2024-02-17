#pragma once
#include "GameObject.h"

class StillObject : public GameObject{
public:
	using GameObject::GameObject;

private:
};

class Wall : public StillObject {
public:
	using StillObject::StillObject;

};

class Door : public StillObject {
public:
	using StillObject::StillObject;

};

class Present : public StillObject {
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