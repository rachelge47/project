#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Board {
public:

	Board();

	void loadFromFile();
	int getLevel() const;
	void draw(const sf::RenderWindow& windon);


private:
	
	std::vector <sf::RectangleShape> m_board;
	int m_level;
};
