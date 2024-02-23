#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "StillObject.h"
#include <fstream>
#include <iostream>
#include "Mouse.h"
#include "Cat.h"
#include "collisions.h"


class GameControl;

const char MOUSE = '%';
const char CAT = '^';
const char KEY = 'F';
const char PRESENT = '$';
const char DOOR = 'D';
const char CHEESE = '*';
const char WALL = '#';
const char EMPTY = ' ';


class Board {
public:

	Board();

	void loadFromFile();
	int getLevel() const;
	void draw( sf::RenderWindow& window) const;
	static int getCheeseCount() { return m_cheeseCount; }
	static int getKeyCount() { return m_keyCount; }
	static int getPresentCount() { return m_presentCount; }
	void printData();
	void checkCollisions(const std::unique_ptr<Mouse>& mouse, const std::vector<std::unique_ptr<Cat>>& cats, const sf::Time& deltaTime);



private:
	void getStills(std::ifstream& boardFile);


	

	std::vector <std::unique_ptr <StillObject>> m_stills;
	int m_level;
	static int m_cheeseCount;
	static int m_presentCount;
	static int m_keyCount;

};
