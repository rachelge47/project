#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <memory>
#include "StillObject.h"
#include <fstream>
#include <iostream>
#include "Mouse.h"
#include "Cat.h"
#include "Present.h"
#include "Manage.h"
#include "Data.h"

class collisions;

class GameControl;

class Board {
public:

	Board();

	void startOver(bool toDo);
	//int getm_numOfLevels();
	void loadFromFile(std::ifstream& boardFile);
	int getLevel() const;
	void setLevel(int toAdd) { m_level =toAdd; }
	void draw( sf::RenderWindow& window) const;
	void drawPresents(sf::RenderWindow& window) const;
	void checkCollisions(const std::unique_ptr<Mouse>& mouse, const std::vector<std::unique_ptr<Cat>>& cats);
	void setController( GameControl* controller) { m_controller = controller; }
	void fillPresents(const sf::Vector2f& tileSize, const sf::Vector2f& currentPosition);
	static int getInitKeyCount() { return m_initKeyCount; }
	static void setKeyCount(int toAdd) { m_keyCount += toAdd; }
	static int getKeyCount() { return m_keyCount; }
	static int getInitCheeseCount() { return m_initCheeseCount; }
	static void setCheeseCount(int toAdd) { m_cheeseCount += toAdd; }
	static int getCheeseCount() { return m_cheeseCount; }
	bool inBounds(sf::FloatRect rect) const;
	sf::FloatRect getGlobalBounds() const;
	void getStills(std::ifstream& boardFile);
	void clearBoard();
	void printBoardData(sf::RenderWindow& window);
	float getInitLevelTime() { return std::stof(m_initLevelTime); }

private:
	//-----functions----
	sf::Text make(const std::string& str, const sf::Font* font, float down);
	void resetFileAndContent(std::ifstream& boardFile, std::vector<std::string>& fileContent);
	void parseFileContent(std::ifstream& boardFile, std::vector<std::string>& fileContent);
	void calculateTileAndBoardSize(const std::vector<std::string>& fileContent);
	void createBoardObject(char symbol, const sf::Vector2f& tileSize, const sf::Vector2f& position);

	//-----members------
	std::streampos m_filePos;
	std::vector <std::unique_ptr <StillObject>> m_stills;
	std::vector <std::unique_ptr <Present>> m_presents;
	int m_level;
	bool m_startOver = false;
	sf::Vector2f m_tileSize;
	static int m_initCheeseCount;
	static int m_cheeseCount;
	static int m_keyCount;
	static int m_initKeyCount;
	sf::Vector2f m_boardSize;
	bool m_firstPresent;
	sf::Clock m_freezeTimer;
	GameControl * m_controller;
	std::string m_initLevelTime;
	Data m_data;
};

