#include "Mouse.h"

Mouse::Mouse(const sf::Vector2f& tileSize, const sf::Vector2f& position, const sf::Texture* texture)
	: MovingObject(tileSize, position, texture, 100.f), m_score(0), m_life(3)
{}

void Mouse::printMouseData(sf::RenderWindow& window)
{
	sf::Text text;
	int down = 220;

	std::string str = std::to_string(m_score);
	text = make(str, Manage::getInstance()->getFont(), down);

	window.draw(text);

	str = std::to_string(m_life);
	down += 90;
	text = make(str, Manage::getInstance()->getFont(), down);
	window.draw(text);

}



sf::Text Mouse::make(const std::string& str, const sf::Font* font, int down)
{
	sf::Text text(str, *font);
	text.setPosition({ 1550, down * 1.f });
	text.setFillColor(sf::Color::Black);
	text.setCharacterSize(80);

	return text;
}