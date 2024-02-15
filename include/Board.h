#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "StillObject.h"
#include <fstream>
#include <iostream>
#include "Wall.h"
#include "Door.h"
#include "Key.h"
#include "Present.h"
#include "Cheese.h"
#include "GameControl.h"


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
	void draw(const sf::RenderWindow& window);


private:
	
	std::vector <std::unique_ptr <StillObject>> m_stills;
	int m_level;

};
