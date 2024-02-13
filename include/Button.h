#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Button {
public:

	Button();

	void drawButton( sf::RenderWindow& window) const;
	void setText();
	void setPosition(const sf::Vector2f& position);
	void fillText();

private:

	void getFont();


	sf::RectangleShape m_button;
	std::vector <sf::Text> m_titles;
	sf::Font m_font;
};