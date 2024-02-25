#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "StillObject.h"
#include <fstream>
#include <iostream>
#include "Mouse.h"
#include "Cat.h"
#include "Present.h"

class collisions;

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
	void drawPresents(sf::RenderWindow& window) const;
	void printData();
	void checkCollisions(const std::unique_ptr<Mouse>& mouse, const std::vector<std::unique_ptr<Cat>>& cats, const sf::Time& deltaTime);

	void fillPresents(const sf::Vector2f& tileSize, const sf::Vector2f& currentPosition);
	
	static int getInitKeyCount() { return m_initKeyCount; }
	//static void setInitKeyCount(int count) { m_initKeyCount = count; }
	static void setKeyCount(int toAdd) { m_keyCount += toAdd; }
	static int getKeyCount() { return m_keyCount; }

	static int getInitCheeseCount() { return m_initCheeseCount; }
	//static void setInitCheeseCount(int count) { m_initCheeseCount = count; }
	static void setCheeseCount(int toAdd) { m_cheeseCount += toAdd; }
	static int getCheeseCount() { return m_cheeseCount; }
	bool inBounds(sf::FloatRect rect) const;
	sf::FloatRect getGlobalBounds() const;


private:
	void getStills(std::ifstream& boardFile);

	void findInitCount();

	std::vector <std::unique_ptr <StillObject>> m_stills;
	std::vector <std::unique_ptr <Present>> m_presents;
	int m_level;
	static int m_initCheeseCount;
	static int m_cheeseCount;
	static int m_presentCount;
	static int m_keyCount;
	static int m_initKeyCount;
	sf::Vector2f m_boardSize;
	bool m_firstPresent;



};
